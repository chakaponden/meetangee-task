Task for Aleksandra Zabiran <a.zabiran@itransition.com> ITransition
-------------------------------------------------------------------

[![Build Status](https://ci.appveyor.com/api/projects/status/github/chakaponden/itransition-task?branch=dev&svg=true)](https://ci.appveyor.com/project/chakaponden/itransition-task)

Your program must work and will be judged based on which algorithms, libraries you use, on code
structure and documentation (must be in English). You can use any information source you wish and take
as much time as you need. The program must be developed in C++ (using OOP style) and must run on
Ubuntu 16.04. You can also use any library in Ubuntu 16.04 repository if it helps you. For compilation you
can use any command line tool (i.e. no Eclipse project...) or command. You are not allowed to use any
external programs during execution of your application. Write the interface of your code so it could be
reused in some other program.

Assignment
----------

Download the front page HTML file of www.meetangee.com, scan it as fast as you can and download
every file the page references. These files must be downloaded as fast as possible, so download them in
parallel. Make hash of every file with Adler 32 algorithm. Print list of file names and their hashes to the
command line. Highlight the biggest and smallest (in size) file.

Requirements
------------
	
The following packages are needed to build:

* gcc 5.4.0
* cmake 2.8.0
* zlib 1.2.8
* curl 7.47.0
* gumbo 1.6.0
* cpp-netlib 0.12.0

Ubuntu 16.04 dependencies installation:

    $ sudo apt-get install zlib1g-dev libcurl4-gnutls-dev libgumbo-dev libcppnetlib-dev libboost-test-dev

How to build
-------------

	$ cmake "path-to-sources"
	$ make
	$ ./itransition-task http://www.meetangee.com