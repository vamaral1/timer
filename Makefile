#Kevin Rowland, Victor Jose Amaral, Sarah Azody
CPPFLAGS=-std=c++0x -pedantic -Wall -Wextra -O -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual -Wsign-promo
CPPFLAGS+=$(shell pkg-config gtkmm-3.0 --cflags)
LDFLAGS=
LDFLAGS=$(shell pkg-config gtkmm-3.0 --libs)
CC=g++

all: gui

gui: gui.o mywindow.o optionsbox.o settingswindow.o timer.o
	$(CC) $^ -o $@ $(LDFLAGS) $(CPPFLAGS)

clean:
	rm -rf *.o gui

.PHONY: zip
zip: 
	tar zcvf cs120-assignment-8-vamaral1-krowlan3-sazody1.tar.gz README Makefile gui.cpp settingswindow.cc settingswindow.h timer.cc optionsbox.h timer.h optionsbox.cpp mywindow.cc mywindow.h
