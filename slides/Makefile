SRC_DIR = src
PDF_TOP = ../pdfs

LATEX_MKF = ../Makefile.latex
MAKE_LATEX = $(MAKE) -f $(LATEX_MKF) -e STYLE=$(STYLE) SRC_DIR=$(SRC_DIR) PDF_TOP=$(PDF_TOP)

SED_EXP_STYLE = sed -i.bak -e 's/^\\LoadClass\[.*\]{beamer}/\\LoadClass[$(1)]{beamer}/' $(SRC_DIR)/mybeamer.cls; rm -f $(SRC_DIR)/mybeamer.cls.bak
SED_EXP_NOTES = sed -i.bak -e 's/^%*\(.*% <4sed:show notes>\)$$/$(1)\1/' $(SRC_DIR)/mybeamer.cls; rm -f $(SRC_DIR)/mybeamer.cls.bak

.PHONY: all, clean, pres, prin, alum, pres_s, prin_s, alum_s
.NOTPARALLEL:

default: pres

all: pres prin alum

pres: STYLE = pres
pres: pres_s
	+$(MAKE_LATEX)

prin: STYLE = prin
prin: prin_s
	+$(MAKE_LATEX)

alum: STYLE = alum
alum: alum_s
	+$(MAKE_LATEX)

pres_s :
	$(call SED_EXP_STYLE,beamer)
	$(call SED_EXP_NOTES,)

prin_s :
	$(call SED_EXP_STYLE,handout)
	$(call SED_EXP_NOTES,%)

alum_s :
	$(call SED_EXP_STYLE,beamer)
	$(call SED_EXP_NOTES,%)

clean:
	+$(MAKE_LATEX) clean
