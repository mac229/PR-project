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
        cout << "ID: " << list[i][0] << " TIME: " << list[i][1]
        << " SIZE: " << list[i][2]<< endl;
    cout << "----------------------------" << endl;
}

void LamportAlgorithm::start(){
    resetValues();
    sendToAll(REQUEST);
    receiveFromAll();
    sorting();
    while (!canEnter())
        mustWait();
    enterToCriticalSection();
    leaveCriticalSection();
}

void LamportAlgorithm::resetValues(){
    clockList.clear();

    Parametry::createMe();
    gettedResponses = 1;
    wantParty = clock->getTime();
    addToList(clock->getID(), wantParty, Parametry::me->wielkosc);
}

void LamportAlgorithm::addToList(int id, int time, int size){
    vector <int> para(3);
    para[0] = id;
    para[1] = time;
    para[2] = size;
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

    cout << "SEND->" << showMsgType(TAG) << "\t"
    << "Proces: " << clock->getID() << " o czasie: " << clock->getTime() <<
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

    cout << "RECV->" << showMsgType(status.Get_tag()) << "\t"
    << "Proces: " << clock->getID() << " o czasie: " << clock->getTime() <<
    " otrzymal od procesu: " << msg.processID << " z jego czasem: " << msg.processTime << endl;

    makeAction(msg, status.Get_tag());
}

void LamportAlgorithm::makeAction(Message msg, int TAG){
    switch (TAG){
        case REQUEST:
            gettedRequest(msg);
            break;
        case WANT_TOO:
            gettedWantToo(msg);
            break;
        case DONT_WANT:
            gettedDontWant(msg);
            break;
        case LEAVE:
            gettedLeave(msg);
            break;
        default:
            cout << "BRAK TAGA" << endl;
            break;
    }
}

void LamportAlgorithm::gettedRequest(Message msg){
    if (msg.meadow == Parametry::me->polana)
        send(msg.processID, WANT_TOO);
    else
        send(msg.processID, DONT_WANT);
}

void LamportAlgorithm::gettedWantToo(Message msg){
    gettedResponses++;
    addToList(msg.processID, msg.processTime, msg.size);

    // TODO: not wait for all
        // sort
        // canEnter
}

void LamportAlgorithm::gettedDontWant(Message msg){
    gettedResponses++;
}

void LamportAlgorithm::gettedLeave(Message msg){
    if (msg.meadow == Parametry::me->polana)
        for (unsigned int i = 0; i < clockList.size(); i++)
            if (clockList[i][1] == msg.processID){
                clockList.erase(clockList.begin() + i);
                break;
            }
    //cout << "ID: " << msg.processID;
    //showList(clockList);
}

void LamportAlgorithm::sorting(){
    sort(clockList.begin(), clockList.end(), rosnaco);
    //showList(clockList);
}

bool LamportAlgorithm::canEnter(){
    unsigned int i = 0, bears = 0;
    int emptySpace = Parametry::pojemnosc;
    bool isSpace = false;
    int myPosition = -1;

    for (i = 0; i < clockList.size(); i++){
        if ((emptySpace - clockList[i][2]) >= 0){
            if (clockList[i][0] == clock->getID()){
                isSpace = true;
                myPosition = i;
            }
            if (clockList[i][2] == 4)
                bears++;

            emptySpace -= clockList[i][2];
        } else
            break;

    }

    takeAlkohol(i, bears, myPosition);

    return (isSpace && ((i - bears) > 0));
}

void LamportAlgorithm::takeAlkohol(int animals, int bears, int pos){
    if ( (bears > 0) && ( (animals - bears) > 0) && (pos > 0))
        if (pos <= bears)
            Parametry::me->alkohol++;
}

void LamportAlgorithm::mustWait(){
    receive();
}

void LamportAlgorithm::enterToCriticalSection(){
    clock->increment();

    cout << "\033[31m" << "ENTER\t" << "\033[0m"
    << "Proces: " << clock->getID() << " wchodzi do sekcji krytycznej z czasem: "
    << clock->getTime() << " i z liczba butelek: " << Parametry::me->alkohol << endl;
}

void LamportAlgorithm::leaveCriticalSection(){
    clock->increment();

    sendToAll(LEAVE);

    cout << "LEAVE\t"
    << "Proces: " << clock->getID() << " opuszcza sekcje krytyczna z czasem: "
    << clock->getTime() << endl;
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

LamportAlgorithm::LamportAlgorithm()
{
    clock = new LamportClock(Parametry::my_id);
    Parametry::me->polana = rand () % Parametry::pojemnosc;
}

LamportAlgorithm::~LamportAlgorithm()
{
    //dtor
}
