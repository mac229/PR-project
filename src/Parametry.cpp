#include "../inc/Parametry.h"

int Parametry::niedzwiedzie = 0;
int Parametry::zajaczki = 0;
int Parametry::polany = 0;
int Parametry::pojemnosc = 0;

bool Parametry::init(vector <Zwierz> &lista, int argc, char * argv[], int size){

   if (argc == 5){
      setParameters(argv);
      if ((niedzwiedzie + zajaczki) == size){
         createBears(lista, size);
         createBunnies(lista, size);
         return true;
      }
  }
      return false;
}

void Parametry::createBears(vector <Zwierz> &lista, int size){
      for (int i = 0; i < niedzwiedzie; i++){
         Niedzwiedz *niedzwiedz = new Niedzwiedz();
         lista.push_back(*niedzwiedz);
      }
}

void Parametry::createBunnies(vector <Zwierz> &lista, int size){
      for (int i = niedzwiedzie; i < size; i++){
         Zajaczek *zajaczek = new Zajaczek();
         lista.push_back(*zajaczek);
      }
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
