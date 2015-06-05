#ifndef PARAMETRY_H
#define PARAMETRY_H

#include <sstream>
#include <iostream>

using namespace std;

class Parametry
{
    public:
         static int niedzwiedzie;
         static int zajaczki;
         static int polany;
         static int pojemnosc;
         static bool init(int argc, char * argv[]);

         Parametry();
         virtual ~Parametry();
    protected:
    private:
};

#endif // PARAMETRY_H
