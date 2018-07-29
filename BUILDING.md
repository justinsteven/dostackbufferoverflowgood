# Building the PDF

A Makefile is provided to help you build the PDF from the Markdown and images
provided in the repository.

**NOTE:** Building the PDF is not required unless you wish to make changes to
the content of the source material or the layout compiled document. You are
free to modify the content or layout and you are free to redistribute modified
source material or compiled documents under the conditions of the Creative
Commons Attribution 4.0 International License license.

## Requirements

* `make` (e.g. as provided by the `build-essential` package on Debian)
* `pandoc` (provided by the `pandoc` package on Debian)
* `xelatex` (provided by the `texlive-xetex` package on Debian)

## Building the PDF

Simply do `make clean && make`

```
root@a44648c727e4:/dostackbufferoverflowgood# make clean
rm -f dostackbufferoverflowgood_tutorial.pdf

root@a44648c727e4:/dostackbufferoverflowgood# make
pandoc --latex-engine=xelatex dostackbufferoverflowgood_tutorial.md -o dostackbufferoverflowgood_tutorial.pdf

root@a44648c727e4:/dostackbufferoverflowgood# ls -la dostackbufferoverflowgood_tutorial.pdf
-rw-r--r-- 1 root root 1065481 Jul 29 03:15 dostackbufferoverflowgood_tutorial.pdf
```

## POC

The following is provided only to demonstrate that the above requirements can
build the PDF. I do not necessarily recommend that you build the PDF within a
Docker container. You can just as easily build the PDF on your local machine.

A `Dockerfile` that installs the required packages (it assumes the
`dostackbufferoverflowgood/` repo exists in the Docker build context):

```
FROM debian

COPY dostackbufferoverflowgood /dostackbufferoverflowgood

RUN \
  apt-get update && \
  apt-get install -y \
    build-essential \
    pandoc \
    texlive-xetex \
  && apt-get clean && \
  rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

CMD cd /dostackbufferoverflowgood && make clean && make
```

Building the Docker image:

```
% sudo -g docker docker build -t build_dostackbufferoverflowgood .
Sending build context to Docker daemon  10.11MB
Step 1/4 : FROM debian
 ---> da653cee0545
Step 2/4 : COPY dostackbufferoverflowgood /dostackbufferoverflowgood
 ---> Using cache
 ---> 357942793cc4
Step 3/4 : RUN apt-get update &&   apt-get install -y     build-essential     pandoc     texlive-xetex   && apt-get clean &&   rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
 ---> Using cache
 ---> b047d0fcf5e0
Step 4/4 : CMD cd /dostackbufferoverflowgood && make clean && make
 ---> Using cache
 ---> bb8e6ad2db61
Successfully built bb8e6ad2db61
Successfully tagged build_dostackbufferoverflowgood:latest
```

Running the Docker image as a container:

```
% sudo -g docker docker run build_dostackbufferoverflowgood
rm -f dostackbufferoverflowgood_tutorial.pdf
pandoc --latex-engine=xelatex dostackbufferoverflowgood_tutorial.md -o dostackbufferoverflowgood_tutorial.pdf
```

The PDF is successfully built and can be copied out of the stopped Docker
container using `docker cp`.
