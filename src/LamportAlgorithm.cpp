#include "../inc/LamportAlgorithm.h"
#include <mpi.h>

#define MSG_TAG 100

void LamportAlgorithm::send(){
    Message msg;
    msg.processID = 5;
    msg.processTime = 0;
    MPI::COMM_WORLD.Send(&msg, sizeof(struct Message), MPI_BYTE, 1, MSG_TAG);

    cout << "wyslalem: " << 5 << endl;
}

void LamportAlgorithm::receive(){
    Message msg;

    MPI::Status status;
    MPI::COMM_WORLD.Recv(&msg, sizeof(struct Message), MPI_BYTE, MPI::ANY_SOURCE, MPI::ANY_TAG, status);
    cout << "otrzymalem: " << msg.processID << endl;
}

LamportAlgorithm::LamportAlgorithm()
{

}

LamportAlgorithm::~LamportAlgorithm()
{
    //dtor
}
