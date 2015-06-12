#ifndef LAMPORTALGORITHM_H
#define LAMPORTALGORITHM_H

#include <iostream>
#include <mpi.h>
#include <vector>
#include <algorithm>

#include "Wiadomosc.h"
#include "LamportClock.h"
#include "Parametry.h"

using namespace std;

class LamportAlgorithm
{
    public:
	void start();

        LamportAlgorithm();
        virtual ~LamportAlgorithm();
    protected:
    private:
	int gettedResponses;
	int wantParty;
        vector< vector<int> > clockList;
        LamportClock *clock;

	void resetValues();

        void sendToAll(int TAG);
        void send(int TO, int TAG);
        
	void receiveFromAll();
	void receive();

	void makeAction(Message msg, int TAG);

	void gettedRequest(Message msg);
	void gettedWantToo(Message msg);
	void gettedDontWant(Message msg);
	void gettedLeave(Message msg);

	void sorting();

	bool canEnter();
	void takeAlkohol(int animals, int bears, int pos);

	void mustWait();

	void enterToCriticalSection();
        void leaveCriticalSection();

	Message createMessage();
	string showMsgType(int TAG);
	void addToList(int id, int time, int size);
};

#endif // LAMPORTALGORITHM_H
