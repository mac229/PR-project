#include <mpi.h>
#include <vector>
#include <iostream>


#include "../inc/Zajaczek.h"
#include "../inc/Niedzwiedz.h"
#include "../inc/Parametry.h"
#include "../inc/LamportClock.h"

using namespace std;

int main(int argc, char** argv) {
   int rank, size;

   MPI_Init (&argc, &argv);                      /* starts MPI */
   MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
   MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */

   if (Parametry::init(argc, argv)){
      cout << "Liczba niedzwiedzi: " << Parametry::niedzwiedzie << endl;
      cout << "Hello world from process " << rank << " of " << size << endl;
   } else {
      cout << "Podano za malo argumentow" << endl;
   }

   MPI_Finalize();
   return 0;
}

