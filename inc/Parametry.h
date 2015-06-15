#ifndef PARAMETRY_H
#define PARAMETRY_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <mpi.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>

#include "../inc/Zajaczek.h"
#include "../inc/Niedzwiedz.h"
#include "../inc/Zwierz.h"

#define REQUEST 100
#define WANT_TOO 200
#define DONT_WANT 300
#define LEAVE 400

using namespace std;

class Parametry
{
    public:
	 static int my_id;
	 static int processes;

	 static Zwierz *me;

         static int niedzwiedzie;
         static int zajaczki;
         static int polany;
         static int pojemnosc;
         static bool init(int argc, char * argv[], int size, int id);
	 static void createMe();

         Parametry();
         virtual ~Parametry();
    protected:
    private:
         static void setParameters(char * argv[]);

};

#endif // PARAMETRY_H
