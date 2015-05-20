#
# makefile az F14 feladat kiprobalasahoz.
# Juhasz Balint, CGQ956 reszere
# Datum: 2014-03-15 23:47:26
# Ez az allomany tetszes szerint modosithato, de nem celszeru
#

CC = g++
CXXFLAGS = -Wall -pedantic
HFT = /home/a/tutors/szebi/hftest2
HEADS = f14.hpp

f14: f14_main.o 
	$(CC) -Wall -o f14 f14_main.o

f14_main.o: $(HEADS)

submit: f14
	$(HFT) -14


