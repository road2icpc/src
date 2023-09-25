# Generate PDF with content
With content from `../src/`:

```bash
./make_pdf.sh ../src <output_name>.pdf
```

# Using hash script
`hash.sh` is not used by `make_pdf.sh`, but might as well reside here:

```bash
./hash.sh < <file_path>
```

# What else?
The following are used by `make_pdf.sh`:

- `KU-logo.png`
- `make_tex.py`
- `tex_template.tex`