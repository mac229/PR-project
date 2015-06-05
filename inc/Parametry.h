#ifndef PARAMETRY_H
#define PARAMETRY_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "../inc/Zajaczek.h"
#include "../inc/Niedzwiedz.h"
#include "../inc/Zwierz.h"

using namespace std;

class Parametry
{
    public:
         static int niedzwiedzie;
         static int zajaczki;
         static int polany;
         static int pojemnosc;
         static bool init(vector <Zwierz> &lista, int argc, char * argv[], int size);

         Parametry();
         virtual ~Parametry();
    protected:
    private:
};

#endif // PARAMETRY_H
