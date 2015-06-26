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
    tryEnter();
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
    Message msg = createMessage(TAG);
    clock->increment();
    MPI::COMM_WORLD.Send(&msg, sizeof(struct Message), MPI_BYTE, TO, TAG);

    cout << "SEND->" << showMsgType(TAG) << "\t"
    << "Proces: " << clock->getID() << " z czasem: " << clock->getTime() <<
    " wysyla komunikat do procesu: " << TO << endl;
}

Message LamportAlgorithm::createMessage(int TAG){
    Message msg;

    msg.processID = clock->getID();
    msg.size = Parametry::me->wielkosc;
    msg.meadow = Parametry::me->polana;
    if ((TAG == REQUEST) || (TAG == WANT_TOO))
        msg.processTime = wantParty;
    else
        msg.processTime = clock->getTime();


    return msg;
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
    << "Proces: " << clock->getID() << " z czasem: " << clock->getTime() <<
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
}

void LamportAlgorithm::gettedDontWant(Message msg){
    gettedResponses++;
}

void LamportAlgorithm::gettedLeave(Message msg){
    if (msg.meadow == Parametry::me->polana)
        for (unsigned int i = 0; i < clockList.size(); i++)
            if (clockList[i][0] == msg.processID){
                clockList.erase(clockList.begin() + i);
                break;
            }
}

void LamportAlgorithm::noWait(){
    if (canEnter() == 0)
        gettedResponses = Parametry::processes;
}

void LamportAlgorithm::sorting(){
    sort(clockList.begin(), clockList.end(), rosnaco);
    //showList(clockList);
}

void LamportAlgorithm::tryEnter(){
    int flag = -1;

    cout << "\033[33m" << "TRY TO ENTER\t" << "\033[0m"
    << "Proces: " << clock->getID() << " sprawdza mozliwosc wejscia na polane: " << Parametry::me->polana << endl;

    do {
       flag = canEnter();
       if (flag == 0){
            enterToCriticalSection();
            leaveCriticalSection();
       }

       if (flag == 1){
            cout << "\033[34m" << "NO SPACE\t" << "\033[0m"
            << "Proces: " << clock->getID() << " czas: " << clock->getTime() << " czeka na zwolnienie miejsca" << endl;

            mustWait();
        }

       if (flag == 2){
            cout << "\033[34m" << "NO BUNNIES\t" << "\033[0m"
            << "Proces: " << clock->getID() << " czas: " << clock->getTime() << " rezygnuje z imprezy" << endl;

            sendToAll(LEAVE);
        }
    }
    while ( flag == 1);
}

int LamportAlgorithm::canEnter(){
    unsigned int i = 0, bunnies = 0;
    int emptySpace = Parametry::pojemnosc;
    bool isSpace = false;
    int myPosition = -1;

 //   showList(clockList);

    for (i = 0; i < clockList.size(); i++){
        if ((emptySpace - clockList[i][2]) >= 0){
            bool onList = false;
            if (bunnies == 0) {
                if ((clockList[i][2] == 4) && (willBeBunnie(i + 1, emptySpace - 4))){
                    emptySpace -= clockList[i][2];
                    onList = true;
                }
                else if (clockList[i][2] == 1){
                    emptySpace -= clockList[i][2];
                    bunnies++;
                    onList = true;
                }
            } else {
                emptySpace -= clockList[i][2];
                onList = true;
                if (clockList[i][2] == 1)
                    bunnies++;
            }

            if ( onList && (clockList[i][0] == clock->getID())){
                isSpace = true;
                myPosition = i;
            }
        }
    }

    takeAlkohol(i, bunnies, myPosition);

    if (isSpace && (bunnies > 0))
        return 0;                   // can enter
    if (!isSpace && (bunnies > 0))
        return 1;                   // no space

    return 2;                       // no bunnies
}

bool LamportAlgorithm::willBeBunnie(int number, int emptySpace){
    for (unsigned int i = number; i < clockList.size(); i++){
        if (((emptySpace - clockList[i][2]) >= 0) && (clockList[i][2] == 1)){
            return true;
        }
    }
    return false;
}

void LamportAlgorithm::takeAlkohol(int animals, int bunnies, int pos){
    if ( (bunnies > 0) && ( (animals - bunnies) > 0) && (pos >= 0))
        if (pos < (animals - bunnies))
            Parametry::me->alkohol++;
}

void LamportAlgorithm::mustWait(){
    receive();
}

void LamportAlgorithm::enterToCriticalSection(){
    clock->increment();

    cout << "\033[32m" << "ENTER\t" << "\033[0m"
    << "Proces: " << clock->getID() << " wchodzi do sekcji krytycznej z czasem: "
    << clock->getTime() << " i z liczba butelek: " << Parametry::me->alkohol << endl;
}

void LamportAlgorithm::leaveCriticalSection(){
    clock->increment();

    cout << "\033[31m" << "LEAVE\t" << "\033[0m"
    << "Proces: " << clock->getID() << " opuszcza sekcje krytyczna z czasem: "
    << clock->getTime() << endl;

    sendToAll(LEAVE);
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
}

LamportAlgorithm::~LamportAlgorithm()
{
    //dtor
}
