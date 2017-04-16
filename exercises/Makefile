SRC_DIR = src
PDF_TOP = ../pdfs/exercises

LATEX_MKF = ../Makefile.latex
MAKE_LATEX = $(MAKE) -f $(LATEX_MKF) -e STYLE=$(STYLE) SRC_DIR=$(SRC_DIR) PDF_TOP=$(PDF_TOP)

.PHONY: all, clean
.NOTPARALLEL:

all:
	+$(MAKE_LATEX)

clean:
	+$(MAKE_LATEX) clean
