#include "../inc/LamportAlgorithm.h"

bool rosnaco(vector<int> const a, vector<int> const b)
{
    if (a[1] == b[1])
        return a[0] < b[0];
	return a[1] < b[1];
}

void showList(vector< vector<int> > list){
    cout << "----------------------------" << endl;
    for (unsigned int i = 0; i < list.size(); i++)
        cout << "ID: " << list[i][0] << " TIME: " << list[i][1] << endl;
    cout << "----------------------------" << endl;
}

void LamportAlgorithm::start(){
    resetValues();
    sendToAll(REQUEST);
    receiveFromAll();
    sorting();
    if (canEnter()){
        enterToCriticalSection();
        leaveCriticalSection();
    }
}

void LamportAlgorithm::resetValues(){
    clockList.clear();
    gettedResponses = 1;
    wantParty = clock->getTime();
    addToList(clock->getID(), wantParty);
}

void LamportAlgorithm::addToList(int id, int time){
    vector <int> para(2);
    para[0] = id;
    para[1] = time;
    clockList.push_back(para);
}

void LamportAlgorithm::sendToAll(int TAG){
    for (int i = 0; i < Parametry::processes; i++)
        if (i != Parametry::my_id)
            send(i, TAG);
}

void LamportAlgorithm::send(int TO, int TAG){
    Message msg = createMessage();

    MPI::COMM_WORLD.Send(&msg, sizeof(struct Message), MPI_BYTE, TO, TAG);
    clock->increment();

    cout << "SEND->" << showMsgType(TAG) << "\t";
    cout << "Proces: " << clock->getID() << " o czasie: " << clock->getTime() << //msg.processTime <<
    " wysyla komunikat do procesu: " << TO << endl;
}

void LamportAlgorithm::receiveFromAll(){
    while (gettedResponses < Parametry::processes){
        receive();
    }
}

void LamportAlgorithm::receive(){
    Message msg;
    MPI::Status status;

    MPI::COMM_WORLD.Recv(&msg, sizeof(struct Message), MPI_BYTE, MPI::ANY_SOURCE, MPI::ANY_TAG, status);
    clock->checkAndSet(msg.processTime);

    cout << "RECV->" << showMsgType(status.Get_tag()) << "\t";
    cout << "Proces: " << clock->getID() << " o czasie: " << clock->getTime() <<
    " otrzymal od procesu: " << msg.processID << " z jego czasem: " << msg.processTime << endl;

    makeAction(msg, status.Get_tag());
}

void LamportAlgorithm::makeAction(Message msg, int TAG){
    switch (TAG){
        case REQUEST:
            // cout << "REQUEST" << endl;
            gettedRequest(msg);
            break;
        case WANT_TOO:
            //cout << "WANT_TOO" << endl;
            gettedWantToo(msg);
            break;
        case DONT_WANT:
            //cout << "DONT_WANT" << endl;
            gettedDontWant(msg);
            break;
        case LEAVE:
            //cout << "LEAVE" << endl;
            gettedLeave(msg);
            break;
        default:
            //cout << "BRAK TAGA" << endl;
            break;
    }
}

void LamportAlgorithm::gettedRequest(Message msg){
    if (msg.meadow == Parametry::me->polana)
        send(msg.processID, WANT_TOO);
    else
        send(msg.processID, DONT_WANT);
}

void LamportAlgorithm::gettedResponse(Message msg){
    if (msg.meadow == Parametry::me->polana){

    }
}

void LamportAlgorithm::gettedWantToo(Message msg){
    gettedResponses++;
    addToList(msg.processID, msg.processTime);

    // if from all processes
        // sort
        // canEnter
}

void LamportAlgorithm::gettedDontWant(Message msg){
    gettedResponses++;
}

void LamportAlgorithm::gettedLeave(Message msg){

}

void LamportAlgorithm::sorting(){
    sort(clockList.begin(), clockList.end(), rosnaco);
    showList(clockList);
}

bool LamportAlgorithm::canEnter(){
    return false;
}



Message LamportAlgorithm::createMessage(){
    Message msg;

    msg.processID = clock->getID();
    msg.processTime = wantParty;
    msg.size = Parametry::me->wielkosc;
    msg.meadow = Parametry::me->polana;

    return msg;
}

string LamportAlgorithm::showMsgType(int TAG){
    switch (TAG){
        case REQUEST:
            return "REQUEST";
        case WANT_TOO:
            return "WANT_TOO";
        case DONT_WANT:
            return "DONT_WANT";
        case LEAVE:
            return "LEAVE";
        default:
            return "BRAK TAGA";
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LamportAlgorithm::receiveRequestFromAll(){
    for (int i = 0; i < Parametry::processes; i++){
        if (i != Parametry::my_id){
            receiveRequest();
            // TODO: nie czekanie na wszystkie otrzymane wiadomosci
            // sort
            if (canEnter()){
                enterToCriticalSection();
                break;
            }
        }
    }
    if (canEnter()){
        enterToCriticalSection();
    }
}

void LamportAlgorithm::receiveRequest(){
    receive();
    Message msg; //error

    cout << "RECV\t";
    cout << "Proces: " << clock->getID() << " z czasem: " << clock->getTime() <<
    " otrzymal żądanie od procesu: " << msg.processID << " z jego czasem: " << msg.processTime << endl;
}
