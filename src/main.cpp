#include "../inc/Parametry.h"
#include "../inc/LamportClock.h"

using namespace std;

void initMPI(int &rank, int &size){
   srand(time(NULL));                           /* starts MPI */
   MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
   MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */
}



int main(int argc, char** argv) {
   int rank, size;
   vector <Zwierz> lista;

   MPI_Init (&argc, &argv);
   initMPI(rank, size);

   if (Parametry::init(lista, argc, argv, size)){
      lista[rank].polana = rand() % Parametry::polany;

      if(rank == 0){
         cout << "Moja polana to: " << lista[rank].polana << endl;
         for(unsigned int i = 0; i < lista.size(); i++)
            cout << lista[i].wielkosc << endl;

      }
      //cout << "Hello world from process " << rank << " of " << size << endl;
   } else {
      cout << "Podano za malo argumentow" << endl;
   }

   MPI_Finalize();
   return 0;
}



