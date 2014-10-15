
FN=wmi

all: pdf html

pdf:
	texi2pdf $(FN).texi

html:
	rm -rf $(FN)
	makeinfo --no-split --html $(FN).texi

a:
	acroread $(FN).pdf

e:
	evince $(FN).pdf

clean:
	@ rm -f $(FN).aux $(FN).cp $(FN).fn $(FN).info $(FN).ky $(FN).log \
           $(FN).toc $(FN).tp $(FN).vr $(FN).pg

PREFIX1=$(HOME)/cimplework/cimple/doc

release:
	cp $(FN).pdf $(PREFIX1)/$(FN)-1.0.0.pdf

publish:
	cp $(FN).html $(PREFIX1)/$(FN)-1.0.0.html
	cp $(FN).pdf $(PREFIX1)/$(FN)-1.0.0.pdf
