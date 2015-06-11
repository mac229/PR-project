#include "../inc/Parametry.h"
#include "../inc/LamportAlgorithm.h"

using namespace std;

void initMPI(int argc, char** argv, int &rank, int &size);



int main(int argc, char** argv) {
   int rank, size;

   initMPI(argc, argv, rank, size);

   if (Parametry::init(argc, argv, size, rank)){
        LamportAlgorithm *l = new LamportAlgorithm();


        if(rank == 0){
            l->receiveFromAll();
        } else {
            l->send(0);
        }
//        cout << "Jestem: " << Parametry::me->wielkosc << " id: " << rank << endl;

    } else {
        cout << "Podano za malo argumentow" << endl;
   }

   MPI::Finalize();
   return 0;
}



void initMPI(int argc, char** argv, int &rank, int &size){
   srand(time(NULL));
   MPI::Init(argc, argv);                         /* starts MPI */
   rank = MPI::COMM_WORLD.Get_rank();        /* get current process id */
   size = MPI::COMM_WORLD.Get_size();        /* get number of processes */
}
