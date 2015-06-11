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

         Parametry();
         virtual ~Parametry();
    protected:
    private:
         static void setParameters(char * argv[]);
	 static void createMe();
         static void createBears(vector <Zwierz> &lista);
         static void createBunnies(vector <Zwierz> &lista);

};

#endif // PARAMETRY_H
