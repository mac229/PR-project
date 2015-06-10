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
        lista[rank].polana = rand() % Parametry::polany;

        LamportAlgorithm *l = new LamportAlgorithm();


        if(rank == 0){
        l->sendToAll();
////            int wyslana = 5;
////            int i = MPI_Send(&wyslana, 1, MPI_INT, 1, MSG_TAG, MPI_COMM_WORLD);
////
////            cout << "wyslalem: " << wyslana << " i: " << i << endl;
//         cout << "Moja polana to: " << lista[rank].polana << endl;
//         for(unsigned int i = 0; i < lista.size(); i++)
//            cout << lista[i].wielkosc << endl;
        }
        if(rank == 1){
        l->receive();
//        int otrzymana = 5;
//                MPI_Status status;
//    MPI_Recv(&otrzymana, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
//    cout << "otrzymalem: " << otrzymana << endl;
        }
    } else {
      cout << "Podano za malo argumentow" << endl;
   }

   MPI_Finalize();
   return 0;
}



