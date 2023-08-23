if [ $# -ne 2 ]; then
	echo "Usage: make_pdf.sh <path to content directory> <output file name>"
	exit 1
fi

content_dir=$(realpath "$1")
output_file="$2"

if [ ! -d "$content_dir" ]; then
	echo "Error: given content directory ('$content_dir') does not exist"
	exit 1
fi

if [ -f "$output_file" ]; then
	echo "Error: given output file ('$output_file') already exists"
	exit 1
fi

if [[ ! "$output_file" =~ \.pdf$ ]]; then
	echo "Error: output file ('$output_file') must have .pdf extension"
	exit 1
fi

if [ -d bin ]; then
	echo "Warning: bin directory already exists, ensure nothing important is overwritten, remove bin directory and rerun"
	exit 1
fi

mkdir -p bin

python3 make_tex.py "$content_dir" > bin/content.tex

if [ $? -ne 0 ]; then
	echo "Error: failed to generate tex file"
	exit 1
fi

cp KU-logo.png bin/

cd bin

pdflatex -interaction=nonstopmode content.tex > tex_err_log 2>&1

if [ $? -ne 0 ]; then
	echo "Error: pdflatex failed to generate pdf file, see tex_err_log for details"
	if [ -f ../tex_err_log ]; then
		echo "Warning: tex_err_log already exists, cannot write details"
	else
		cp tex_err_log ..
	fi
	cd ..
	rm -rf bin
	exit 1
fi

cp content.pdf ../"$output_file"

cd ..

rm -rf bin
