#include "../inc/LamportAlgorithm.h"
#include <mpi.h>

#define MSG_TAG 100

void LamportAlgorithm::sendToAll(){
    for (int i = 0; i < Parametry::processes; i++)
        if (i != Parametry::my_id)
            send(i);
}

void LamportAlgorithm::send(int to){
    Message msg;
    msg.processID = clock->getID();
    msg.processTime = clock->getTime();

    MPI::COMM_WORLD.Send(&msg, sizeof(struct Message), MPI_BYTE, to, MSG_TAG);

    clock->increment();

    cout << "Proces: " << msg.processID << " z czasem: " << msg.processTime <<
    " wysyla zadanie do procesu: " << to << endl;
}

void LamportAlgorithm::receive(){
    Message msg;

    MPI::Status status;
    MPI::COMM_WORLD.Recv(&msg, sizeof(struct Message), MPI_BYTE, MPI::ANY_SOURCE, MPI::ANY_TAG, status);

    clock->checkAndSet(msg.processTime);

    cout << "Proces: " << clock->getID() << " z czasem: " << clock->getTime() <<
    " otrzymal zadanie od procesu: " << msg.processID << " z jego czasem: " << msg.processTime << endl;
}

LamportAlgorithm::LamportAlgorithm(int id)
{
    clock = new LamportClock(id);
}

LamportAlgorithm::~LamportAlgorithm()
{
    //dtor
}
