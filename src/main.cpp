#include "../inc/Parametry.h"
#include "../inc/LamportAlgorithm.h"

#define ITERATIONS 1

using namespace std;

void initMPI(int argc, char** argv, int &rank, int &size);

int main(int argc, char** argv) {
   int rank, size;

   initMPI(argc, argv, rank, size);

   if (Parametry::init(argc, argv, size, rank)){

        for (unsigned int i = 0; i < ITERATIONS;  i++){
            LamportAlgorithm *l = new LamportAlgorithm();
            l->start();
        }

    } else {
        cout << "Podano zle argumenty" << endl;
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
