#include "../inc/Parametry.h"

int Parametry::niedzwiedzie = 0;
int Parametry::zajaczki = 0;
int Parametry::polany = 0;
int Parametry::pojemnosc = 0;

bool Parametry::init(int argc, char * argv[]){

   if (argc == 5){
      istringstream iss1(argv[1]);
		iss1 >> niedzwiedzie;
      istringstream iss2(argv[2]);
		iss2 >> zajaczki;
		istringstream iss3(argv[3]);
		iss3 >> polany;
      istringstream iss4(argv[4]);
		iss4 >> pojemnosc;

      return true;
  } else
      return false;
}

Parametry::Parametry()
{
    //ctor
}

Parametry::~Parametry()
{
    //dtor
}
