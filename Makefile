dostackbufferoverflowgood_tutorial.pdf: dostackbufferoverflowgood_tutorial.md
	pandoc --latex-engine=xelatex $< -o $@

all: dostackbufferoverflowgood_tutorial.pdf

clean:
	rm -f dostackbufferoverflowgood_tutorial.pdf
