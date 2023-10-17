all:
# python gen tex
	python3 ./cppFileToTex.py
#first make gen main.toc
	pdflatex main.tex
#make all
	pdflatex main.tex
clean:
	rm -rf `find -type f |grep -v makefile |grep -v main.tex |grep -v cppFileToTex.py`