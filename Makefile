# Useful directories

MYCODEDIR := .

# Directories to search for header files

SEARCHDIRS := -I- -I${MYCODEDIR}

# makemake variables

LINKER       := gcc
DEPENDFLAGS  := -DLINUXELF_I386 -g -Wall ${SEARCHDIRS} `gtk-config --cflags`
TOUCHHEADERS := ${MYCODEDIR}/*.h

# make variables

CC       := gcc
CXX      := g++
CCC      := g++
CPPFLAGS  := ${DEPENDFLAGS}
LOADLIBES := -lstdc++ `gtk-config --libs`


# This is what makemake added


# debug

debug : DMXObject.o DMXContainer.o Main.o MainWindow.o MainNotebook.o LightingBoard.o Stage.o Slider.o ChannelSlider.o Scene.o MainMenu.o
	${LINKER} ${LDFLAGS} -o $@ ${filter-out %.a, $^} ${LOADLIBES}


# release

release : DMXObject.o DMXContainer.o Main.o MainWindow.o MainNotebook.o LightingBoard.o Stage.o Slider.o ChannelSlider.o Scene.o MainMenu.o
	${LINKER} ${LDFLAGS} -o $@ ${filter-out %.a, $^} ${LOADLIBES}


# target for making everything

.PHONY : all
all: debug release


# target for removing all object files

.PHONY : tidy
tidy::
	@${RM} core ChannelSlider.o DMXContainer.o DMXObject.o LightingBoard.o Main.o MainMenu.o MainNotebook.o MainWindow.o Scene.o Slider.o Stage.o

# target for removing all object files

.PHONY : clean
clean:: tidy
	@${RM} debug release

# list of all source files

MM_ALL_SOURCES := ChannelSlider.cc DMXContainer.cc DMXObject.cc LightingBoard.cc Main.cc MainMenu.cc MainNotebook.cc MainWindow.cc Scene.cc Slider.cc Stage.cc


# target for checking a source file

CHECKSYNTAXFILE := ${basename ${filter %${CHECKSTRING}, ${MM_ALL_SOURCES}}}

.PHONY : checksyntax
checksyntax:
  ifneq (${CHECKSYNTAXFILE},)
	@${MAKE} ${addsuffix .o, ${CHECKSYNTAXFILE}}
  else
	@echo No target to make ${CHECKSTRING}
  endif


# target for touching appropriate source files

.PHONY : touch
touch:
	@echo
	@echo Please ignore \"file arguments missing\" errors
	@echo
	@echo   `grep -l ${TOUCHSTRING} ${MM_ALL_SOURCES}`
	@-touch `grep -l ${TOUCHSTRING} ${MM_ALL_SOURCES}`
	@echo
	@echo   `grep -l ${TOUCHSTRING} ${TOUCHHEADERS}`
	@-touch `grep -l ${TOUCHSTRING} ${TOUCHHEADERS}`


# target for calculating dependencies

.PHONY : jdepend
jdepend:
	@makemake -depend Makefile -- ${DEPENDFLAGS} -- ChannelSlider.cc ChannelSlider.o DMXContainer.cc DMXContainer.o DMXObject.cc DMXObject.o LightingBoard.cc LightingBoard.o Main.cc Main.o MainMenu.cc MainMenu.o MainNotebook.cc MainNotebook.o MainWindow.cc MainWindow.o Scene.cc Scene.o Slider.cc Slider.o Stage.cc Stage.o


# DO NOT DELETE THIS LINE -- makemake depends on it.

ChannelSlider.o: ./ChannelSlider.h ./DMXObject.h ./Slider.h /usr/include/gtk/gtk.h

DMXObject.o: ./DMXObject.h /usr/include/gtk/gtk.h

LightingBoard.o: ./DMXContainer.h ./DMXObject.h ./LightingBoard.h ./Slider.h /usr/include/gtk/gtk.h

Main.o: ./DMXContainer.h ./DMXObject.h ./LightingBoard.h ./MainMenu.h ./MainNotebook.h ./MainWindow.h ./Slider.h ./Stage.h /usr/include/gtk/gtk.h

MainMenu.o: ./DMXContainer.h ./DMXObject.h ./MainMenu.h /usr/include/gtk/gtk.h

MainNotebook.o: ./DMXContainer.h ./DMXObject.h ./LightingBoard.h ./MainNotebook.h ./Slider.h ./Stage.h /usr/include/gtk/gtk.h

MainWindow.o: ./DMXContainer.h ./DMXObject.h ./MainWindow.h /usr/include/gtk/gtk.h

Scene.o: ./DMXContainer.h ./DMXObject.h ./Scene.h /usr/include/gtk/gtk.h

Slider.o: ./DMXObject.h ./Slider.h /usr/include/gtk/gtk.h

Stage.o: ./DMXContainer.h ./DMXObject.h ./Stage.h /usr/include/gtk/gtk.h

