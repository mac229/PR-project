#include "../inc/Parametry.h"
#include "../inc/LamportClock.h"
#include "../inc/LamportAlgorithm.h"

using namespace std;

void initMPI(int &rank, int &size){
   srand(time(NULL));                           /* starts MPI */
   MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
   MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */
}

#define MSG_TAG 100

int main(int argc, char** argv) {
   int rank, size;
   vector <Zwierz> lista;

   MPI_Init (&argc, &argv);
   initMPI(rank, size);

   if (Parametry::init(lista, argc, argv, size)){
        LamportClock *lamportClock = new LamportClock(rank);
        LamportAlgorithm *l = new LamportAlgorithm();
        lista[rank].polana = rand() % Parametry::polany;

        if(rank == 0){
            l->send();
        }
        if(rank == 1){
            l->receive();
        }
    } else {
      cout << "Podano za malo argumentow" << endl;
   }

   MPI_Finalize();
   return 0;
}



