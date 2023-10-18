all:
	mkdir -p ./resource
	cp -f ../resource/* ./resource
	cp -f ../tutorial/*/resource/* ./resource
# python gen tex
	python3 ./cppFileToTex.py
#first make gen main.toc
	pdflatex --shell-escape main.tex
#make all
	pdflatex --shell-escape main.tex
	mv main.pdf chino-acm-template-v0.0.2.pdf
clean:
	rm -rf `find -type f | grep -v makefile | grep -v main.tex | grep -v cppFileToTex.py`
	rm -rf `find -type d | grep /`