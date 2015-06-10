#include "../inc/LamportAlgorithm.h"
#include <mpi.h>

//      MPI_SEND( skąd, ile, typ, do kogo, z jakim tagiem, MPI_COMM_WORLD)
//      MPI_Recv( gdzie, ile , jakiego typu, od kogo, z jakim tagiem, MPI_COMM_WORLD, &status);

#define MSG_TAG 100

void LamportAlgorithm::sendToAll(){
    int wyslana = 5;
    MPI::COMM_WORLD.Send(&wyslana, 4, MPI_INT, 1, MSG_TAG);

    cout << "wyslalem: " << wyslana << endl;
}

void LamportAlgorithm::receive(){
    int otrzymana = 0;

    MPI::Status status;
    MPI::COMM_WORLD.Recv(&otrzymana, 4, MPI_INT, MPI::ANY_SOURCE, MPI::ANY_TAG, status);
    cout << "otrzymalem: " << otrzymana << endl;
}

LamportAlgorithm::LamportAlgorithm()
{

}

LamportAlgorithm::~LamportAlgorithm()
{
    //dtor
}
