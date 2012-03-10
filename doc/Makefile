# Makefile for LaTeX compilation, by Guillaume Pinot
# (guillaume.pinot@tremplin-utc.net), with the help of internet.
#
# Last modification: 2006-10-06
#
# Copyright (c) 2006 Guillaume Pinot.
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# usage: make a Makefile.in in your directory with the BASENAME
# variable set to the basename of your projet. For example, if your
# main file is named "report.tex", the Makefile.in will be :
#
# -----8<---------8<---------8<---------8<---------8<---------8<----
# BASENAME = report
# -----8<---------8<---------8<---------8<---------8<---------8<----

include Makefile.in

RERUN = "(There were undefined references|Rerun to get (cross-references|the bars) right)"
RERUNBIB = "No file.*\.bbl|Citation.*undefined"
COPY = if test -r $(BASENAME).toc; \
	then cp $(BASENAME).toc $(BASENAME).toc.bak; fi

all: pdf

ps: $(BASENAME).ps

pdf: $(BASENAME).pdf

ps.gz: $(BASENAME).ps.gz

dvi: $(BASENAME).dvi

dvi.gz: $(BASENAME).dvi.gz

clean:
	rm -f *.aux *.log *.toc *.out *.lof *.lot *.blg *.bbl *~ *.nav \
	  *.snm *.vrb .latexcompil.aux *.fff *.ttt

epsclean:
	if [ -d images ]; then cd images && $(MAKE) clean; fi

distclean: clean epsclean
	rm -f *.pdf *.ps *.dvi *.dvi.gz *.ps.gz

pkg: distclean
	export pkg=`echo $${PWD##*/}` && cd .. && tar czf $$pkg.tar.gz $$pkg

$(BASENAME).ps.gz: $(BASENAME).ps
	gzip $<

$(BASENAME).dvi.gz: $(BASENAME).dvi
	gzip $<

$(BASENAME).ps: $(BASENAME).dvi
	dvips -Ppdf $< -o $@

$(BASENAME).dvi:  $(BASENAME).tex *.tex *.bib
	touch .latexcompil.aux
	if [ -d images ]; then cd images && $(MAKE) eps; fi
	$(COPY); latex $<
	egrep -c $(RERUNBIB) $(BASENAME).log && \
	  (bibtex $(BASENAME); $(COPY); latex $<) ; true
	egrep $(RERUN) $(BASENAME).log && ($(COPY); latex $<) ; true
	egrep $(RERUN) $(BASENAME).log && ($(COPY); latex $<) ; true
	if cmp -s $(BASENAME).toc $(BASENAME).toc.bak; then :;\
	    else latex $< ; fi
	rm -f $(BASENAME).toc.bak
# Display relevant warnings
	egrep -i "(Reference|Citation).*undefined" $(BASENAME).log ; true

$(BASENAME).pdf:  $(BASENAME).tex *.tex *.bib
	test -r .latexcompil.aux && ($(MAKE) clean; rm .latexcompil.aux); true
	$(COPY); pdflatex $<
	egrep -c $(RERUNBIB) $(BASENAME).log && \
	  (bibtex $(BASENAME); $(COPY); pdflatex $<) ; true
	egrep $(RERUN) $(BASENAME).log && ($(COPY); pdflatex $<) ; true
	egrep $(RERUN) $(BASENAME).log && ($(COPY); pdflatex $<) ; true
	if cmp -s $(BASENAME).toc $(BASENAME).toc.bak; then :;\
	    else pdflatex $< ; fi
	rm -f $(BASENAME).toc.bak
# Display relevant warnings
	egrep -i "(Reference|Citation).*undefined" $(BASENAME).log ; true
