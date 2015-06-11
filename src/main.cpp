#include "../inc/Parametry.h"
#include "../inc/LamportAlgorithm.h"

using namespace std;

void initMPI(int &rank, int &size){
   srand(time(NULL));                           /* starts MPI */
   rank = MPI::COMM_WORLD.Get_rank();        /* get current process id */
   size = MPI::COMM_WORLD.Get_size();        /* get number of processes */
}

#define MSG_TAG 100

int main(int argc, char** argv) {
   int rank, size;

   MPI::Init(argc, argv);
   initMPI(rank, size);

   if (Parametry::init(argc, argv, size, rank)){
        LamportAlgorithm *l = new LamportAlgorithm(rank);


//        if(rank == 0){
//            l->sendToAll();
//        } else {
//            l->receive();
//        }
        cout << "Jestem: " << Parametry::me->wielkosc << endl;

    } else {
        cout << "Podano za malo argumentow" << endl;
   }

   MPI::Finalize();
   return 0;
}



