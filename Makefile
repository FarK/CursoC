PDF_TOP = pdfs
SLIDES_PDF_DIR    = $(PDF_TOP)/slides
EXERCISES_PDF_DIR = $(PDF_TOP)/exercises
ANNEXES_PDF_DIR   = $(PDF_TOP)/annexes

SLIDES_DIR = slides
EXERCISES_DIR = exercises
ANNEXES_DIR = annexes


MAKE_SLIDES    = cd $(SLIDES_DIR)    && $(MAKE) -e PDF_TOP=../$(SLIDES_PDF_DIR)
MAKE_EXERCISES = cd $(EXERCISES_DIR) && $(MAKE) -e PDF_TOP=../$(EXERCISES_PDF_DIR)
MAKE_ANNEXES   = cd $(ANNEXES_DIR)   && $(MAKE) -e PDF_TOP=../$(ANNEXES_PDF_DIR)

.PHONY: all, pres_n_exer, clean, mrproper, spres, sprin, salum, sall, exer, annex

pres_n_exer: spres exer annex

all: sall exer annex

sall:
	+$(MAKE_SLIDES) all

spres: | $(SLIDES_PDF_DIR)
	+$(MAKE_SLIDES) pres

sprin: | $(SLIDES_PDF_DIR)
	+$(MAKE_SLIDES) prin

salum: | $(SLIDES_PDF_DIR)
	+$(MAKE_SLIDES) alum

exer: | $(EXERCISES_PDF_DIR)
	+$(MAKE_EXERCISES)

annex: | $(ANNEXES_PDF_DIR)
	+$(MAKE_ANNEXES)

$(SLIDES_PDF_DIR):
	@-mkdir -pv $(SLIDES_PDF_DIR)

$(EXERCISES_PDF_DIR):
	@-mkdir -pv $(EXERCISES_PDF_DIR)

$(ANNEXES_PDF_DIR):
	@-mkdir -pv $(ANNEXES_PDF_DIR)

clean:
	+$(MAKE_SLIDES) clean
	+$(MAKE_EXERCISES) clean
	+$(MAKE_ANNEXES) clean
	@-rmdir -v $(PDF_TOP)

mrproper: clean
	+cd $(SLIDES_DIR)    && $(MAKE) clean
	+cd $(EXERCISES_DIR) && $(MAKE) clean
	+cd $(ANNEXES_DIR)   && $(MAKE) clean
