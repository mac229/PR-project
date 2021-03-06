#include "../inc/Parametry.h"

int Parametry::niedzwiedzie = 0;
int Parametry::zajaczki = 0;
int Parametry::polany = 0;
int Parametry::pojemnosc = 0;
int Parametry::processes = 0;
int Parametry::my_id = 0;
Zwierz *Parametry::me = new Zwierz();

bool Parametry::init(int argc, char * argv[], int size, int id){

    my_id = id;
    processes = size;

   if (argc == 5){
      setParameters(argv);
      if ((niedzwiedzie + zajaczki) == processes){
         createMe();
         return true;
      }
  }
      return false;
}

void Parametry::createMe(){
    if (my_id < niedzwiedzie)
        me = new Niedzwiedz();
    else
        me = new Zajaczek();
    me->polana = rand() % pojemnosc;
}

void Parametry::setParameters(char * argv[]){
      istringstream iss1(argv[1]);
		iss1 >> niedzwiedzie;
      istringstream iss2(argv[2]);
		iss2 >> zajaczki;
		istringstream iss3(argv[3]);
		iss3 >> polany;
      istringstream iss4(argv[4]);
		iss4 >> pojemnosc;
}

Parametry::Parametry()
{
    //ctor
}

Parametry::~Parametry()
{
    //dtor
}
