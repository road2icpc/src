# Guide to building the TRD PDF file and formatting of source files

## Formatting source files
All source files exist in `./src/<category>/<file>`.

#### Format
Each file can be accompanied by metadata that gets parsed as LaTeX (you can (should) use math mode where appropriate, etc.). **Please** make use of this...

**How?:**

Comments starting like this get removed from the code and parsed as LaTeX:

```c++
//# <block>: blah blah blah
```

Where `<block>` is one of:

- `Title` (as presented in the final document)
- `Description` (as needed during a contest to understand the code)
- `Usage` (quick example of how to use the code (syntax-wise))
- `Complexity` (time (and space, if out of the ordinary) complexity of important functions)

The comments can be broken into multiple lines in the source file as such:

```c++
//# <block>: blah blah
//# and more blah
//# ...
```

Comments like below are ignored entirely and can be used to communicate information during development without taking space in the document. Please at least use this to communicate information on where the code has been tested (if it has):

```
//@ blah blah blah
```

[>>> see example! <<<](./src/Data_structures/DSU.h)

Normal comments are left in the code as is.

## Building the TRD
Go to `./PDF/` and check the `README.md` there. In short:

```sh
$ ./make_pdf.sh <source code file path> <config file path> <output file path (.pdf)>
```

E.g.:

```sh
$ ./make_pdf.sh ../src/ config_file TRD.pdf
```

The config file is used to manually specify the rendering order of the categories. One already exists, don't worry about it `:)`.
