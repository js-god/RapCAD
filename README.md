[![Travis CI](https://api.travis-ci.org/GilesBathgate/RapCAD.png)](https://travis-ci.org/GilesBathgate/RapCAD)

# Introduction

RapCAD is a Rapid prototyping CAD IDE for RepRap and RepStrap 3D printing
machines. RapCAD is published under the GPLv3 licence.

Unlike most CAD packages RapCAD is not GUI based. One of the things that you
often do when using a traditional CAD package, for example, is to create
temporary construction lines that you either delete or put on a layer that is
never used or seen. From another persons perspective its not always obvious how
you arrived at your final design. In the software industry, the vital role of
version control is that it allows the transcript of decisions made during the
design process to be recorded. RapCAD solves this problem by allowing designs
to be described with a modular scene description language. This not only
provides compatability with traditional text based source control management
software, but it also allows for the creation of re-usable component modules
that can be distributed as a design library.

# Installation

## Windows

+ Download the [latest installer](https://github.com/GilesBathgate/RapCAD/releases/download/v0.9.4/rapcad_0.9.4_setup.exe).
+ Double click the installer exe and follow the on-screen instructions.

## Ubuntu

+ Supports: Saucy, Trusty
+ Simply run the following commands in a terminal.
	sudo apt-add-repository ppa:gilesbathgate/rapcad
	sudo apt-get update
	sudo apt-get install rapcad

## Mac OS X

+ Download the [latest disk image](https://github.com/GilesBathgate/RapCAD/releases/download/v0.9.0/rapcad_0.9.0.dmg).
+ Open the image and run the rapcad package.
