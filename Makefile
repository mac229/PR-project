all: zajaczki
zajaczki: obj/LamportClock.o obj/main.o obj/Niedzwiedz.o obj/Parametry.o obj/Zajaczek.o obj/Zwierz.o
	mpicxx obj/LamportClock.o obj/main.o obj/Niedzwiedz.o obj/Parametry.o obj/Zajaczek.o obj/Zwierz.o -Wall -o zajaczki
obj/LamportClock.o: src/LamportClock.cpp src/../inc/LamportClock.h
	mpicxx src/LamportClock.cpp -o $@ -Wall -c
obj/main.o: src/main.cpp src/../inc/Parametry.h src/../inc/../inc/Zajaczek.h src/../inc/../inc/../inc/Zwierz.h src/../inc/../inc/../inc/../inc/Parametry.h src/../inc/../inc/Niedzwiedz.h src/../inc/../inc/Zwierz.h src/../inc/LamportClock.h
	mpicxx src/main.cpp -o $@ -Wall -c
obj/Niedzwiedz.o: src/Niedzwiedz.cpp src/../inc/Niedzwiedz.h src/../inc/../inc/Zwierz.h src/../inc/../inc/../inc/Parametry.h src/../inc/../inc/../inc/../inc/Zajaczek.h src/../inc/../inc/../inc/../inc/../inc/Zwierz.h src/../inc/../inc/../inc/../inc/Niedzwiedz.h src/../inc/../inc/../inc/../inc/Zwierz.h
	mpicxx src/Niedzwiedz.cpp -o $@ -Wall -c
obj/Parametry.o: src/Parametry.cpp src/../inc/Parametry.h src/../inc/../inc/Zajaczek.h src/../inc/../inc/../inc/Zwierz.h src/../inc/../inc/../inc/../inc/Parametry.h src/../inc/../inc/Niedzwiedz.h src/../inc/../inc/Zwierz.h
	mpicxx src/Parametry.cpp -o $@ -Wall -c
obj/Zajaczek.o: src/Zajaczek.cpp src/../inc/Zajaczek.h src/../inc/../inc/Zwierz.h src/../inc/../inc/../inc/Parametry.h src/../inc/../inc/../inc/../inc/Zajaczek.h src/../inc/../inc/../inc/../inc/Niedzwiedz.h src/../inc/../inc/../inc/../inc/../inc/Zwierz.h src/../inc/../inc/../inc/../inc/Zwierz.h
	mpicxx src/Zajaczek.cpp -o $@ -Wall -c
obj/Zwierz.o: src/Zwierz.cpp src/../inc/Zwierz.h src/../inc/../inc/Parametry.h src/../inc/../inc/../inc/Zajaczek.h src/../inc/../inc/../inc/../inc/Zwierz.h src/../inc/../inc/../inc/Niedzwiedz.h src/../inc/../inc/../inc/Zwierz.h
	mpicxx src/Zwierz.cpp -o $@ -Wall -c
clean:
	rm -f obj/*
