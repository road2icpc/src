from dataclasses import dataclass
import os
import subprocess
import hashlib
from collections import OrderedDict
import sys

@dataclass
class Source_sections:
	title: str
	description: str
	usage: str
	complexity: str
	source_code: str
	hash_str: str

def get_hash(content: str) -> str:
	process = subprocess.Popen(
		["cpp", "-dD", "-P", "-fpreprocessed"],
		stdin=subprocess.PIPE,
		stdout=subprocess.PIPE,
		stderr=subprocess.PIPE
	)
	preprocessed_content, _ = process.communicate(input=content.encode("utf-8"))
	cleaned_content = "".join(preprocessed_content.decode("utf-8").split())
	md5_hash = hashlib.md5(cleaned_content.encode("utf-8")).hexdigest()
	return md5_hash[:6]

def read_file(path: str) -> str:
	try:
		with open(path, "r", encoding="utf-8") as f:
			return f.read()
	except FileNotFoundError: print(f"File not found: '{path}'")
	except PermissionError: print(f"Permission error: '{path}'")
	except IsADirectoryError: print(f"Is a directory: '{path}'")
	except UnicodeDecodeError: print(f"Unicode decode error: '{path}'")
	return ""

def parse_source_code(path: str) -> Source_sections:
	source_code = read_file(path)
	if source_code == "":
		raise Exception(f"Failed to read file: '{path}'")
	lines = source_code.split("\n")
	sections = {
		"title": "",
		"description": "",
		"usage": "",
		"complexity": "",
		"hash": "",
	}
	current_section = None
	for line in lines:
		if line.strip().lower().startswith("//#"):
			parts = line.strip()[3:].split(":")
			section_name = parts[0].strip().lower()
			section_content = parts[1].strip() if len(parts) > 1 else ""
			if section_name in sections:
				is_first_line = len(sections[section_name]) == 0
				current_section = section_name
				if is_first_line:
					sections[section_name] = section_content
				else:
					sections[current_section] += " " + section_content
			elif current_section:
				sections[current_section] += " " + line.strip()[3:].strip()
	code_lines = [line for line in lines if not line.strip().startswith(("//#", "//@"))]
	while len(code_lines) > 0 and not code_lines[0].strip():
		code_lines.pop(0)
	while len(code_lines) > 0 and not code_lines[-1].strip():
		code_lines.pop()
	source_code = "\n".join(code_lines)
	return Source_sections(
		title = sections["title"],
		description = sections["description"],
		usage = sections["usage"],
		complexity = sections["complexity"],
		source_code = source_code,
		hash_str = get_hash(source_code)
	)

def find_files(root: str) -> dict[str, list[str]]:
	files = {}
	for dirpath, dirnames, filenames in os.walk(root):
		for filename in sorted(filenames):
			if filename.endswith(".h"):
				full_path = os.path.join(dirpath, filename)
				relative_path = os.path.relpath(full_path, root)
				path_parts = relative_path.split(os.path.sep)
				if len(path_parts) == 2:
					directory, file_name = path_parts
					files.setdefault(directory, []).append(file_name)
	sorted_files = OrderedDict(sorted(files.items()))
	return sorted_files

def get_tex_template() -> str:
	return read_file("tex_template.tex")

def source_to_tex(source: Source_sections):
	result = "\\subsection{" + (source.title if len(source.title) > 0 else "\\[missing title\\]") + "}\n"
	result += "\\vspace{-0.1cm}\n"
	conditional_additions = []
	if len(source.description) > 0:
		conditional_additions.append("\\textbf{Description}: " + source.description)
	if len(source.usage) > 0:
		conditional_additions.append("\\textbf{Usage}: " + source.usage)
	if len(source.complexity) > 0:
		conditional_additions.append("\\textbf{Complexity}: " + source.complexity)
	for addition in conditional_additions:
		result += addition
		if addition != conditional_additions[-1]:
			result += "\\\\\n"
	result += "\\hashlined{" + get_hash(source.source_code) + "}"
	result += "\\begin{lstlisting}[language=C++]\n"
	result += source.source_code + "\n"
	result += "\\end{lstlisting}\n"
	result += "\\solidline\n"
	return result

def make_tex(root: str):
	files = find_files(root)
	sources = {}
	for directory, filenames in files.items():
		for filename in filenames:
			sources.setdefault(directory, []).append(parse_source_code(os.path.join(root, directory, filename)))
	result = get_tex_template()
	result += "\n\\begin{document}\n\n\\frontpage\n\n\\begin{multicols}{3}\n\\raggedcolumns\n"
	for section, entries in sources.items():
		result += "\\section{" + section.replace("_", "\\_") + "}\n\n"
		for entry in entries:
			result += source_to_tex(entry)
			result += "\n"
	result += "\\end{multicols}\n\n\\end{document}"
	return result;

if len(sys.argv) != 2:
	print("Usage: make_tex.py <source_directory>")
	exit(1)
print(make_tex(sys.argv[1]))