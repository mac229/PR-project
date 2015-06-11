#include "../inc/LamportAlgorithm.h"


void LamportAlgorithm::sendToAll(int TAG){
    for (int i = 0; i < Parametry::processes; i++)
        if (i != Parametry::my_id)
            send(i, TAG);
}

void LamportAlgorithm::receiveFromAll(){                    // TODO: nie czekanie na wszystkie otrzymane wiadomosci
    for (int i = 0; i < Parametry::processes; i++)
        if (i != Parametry::my_id)
            receive();
}

void LamportAlgorithm::send(int TO, int TAG){
    Message msg;
    msg.processID = clock->getID();
    msg.processTime = clock->getTime();

    MPI::COMM_WORLD.Send(&msg, sizeof(struct Message), MPI_BYTE, TO, TAG);
    clock->increment();

    cout << "SEND\t";
    cout << "Proces: " << msg.processID << " z czasem: " << msg.processTime <<
    " wysyla żądanie do procesu: " << TO << endl;
}

void LamportAlgorithm::receive(){
    Message msg;
    MPI::Status status;

    MPI::COMM_WORLD.Recv(&msg, sizeof(struct Message), MPI_BYTE, MPI::ANY_SOURCE, MPI::ANY_TAG, status);
    clock->checkAndSet(msg.processTime);

    makeAction(status.Get_tag());

    cout << "RECV\t";
    cout << "Proces: " << clock->getID() << " z czasem: " << clock->getTime() <<
    " otrzymal żądanie od procesu: " << msg.processID << " z jego czasem: " << msg.processTime << endl;
}

void LamportAlgorithm::makeAction(int TAG){
    switch (TAG){
        case REQUEST:
            cout << "REQUEST" << endl;
            break;
        case RESPONSE:
            cout << "RESPONSE" << endl;
            break;
        case WANT_TOO:
            cout << "WANT_TOO" << endl;
            break;
        case DONT_WANT:
            cout << "DONT_WANT" << endl;
            break;
        case LEAVE:
            cout << "LEAVE" << endl;
            break;
        default:
            cout << "BRAK TAGA" << endl;
            break;
    }
}

void LamportAlgorithm::enterToCriticalSection(){
    //sleep
    cout << "ENTER\t";
    cout << "Proces: " << clock->getID() << " wchodzi do sekcji krytycznej z czasem: "
    << clock->getTime() << endl;
}

void LamportAlgorithm::leaveCriticalSection(){
    cout << "LEAVE\t";
    cout << "Proces: " << clock->getID() << " opuszcza sekcje krytyczna z czasem: "
    << clock->getTime() << endl;
}

LamportAlgorithm::LamportAlgorithm()
{
    clock = new LamportClock(Parametry::my_id);
    Parametry::me->polana = rand () % Parametry::pojemnosc;
}

LamportAlgorithm::~LamportAlgorithm()
{
    //dtor
}
