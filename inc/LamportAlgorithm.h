#ifndef LAMPORTALGORITHM_H
#define LAMPORTALGORITHM_H

#include <iostream>
#include <mpi.h>
#include <vector>

#include "Wiadomosc.h"
#include "LamportClock.h"
#include "Parametry.h"

using namespace std;

class LamportAlgorithm
{
    public:
	void start();

        void sendToAll(int TAG);
        void send(int TO, int TAG);
        
	void receiveFromAll();
	void receiveRequestFromAll();
	void receiveRequest();
	void receive();

	void gettedRequest(Message msg);
	void gettedResponse(Message msg);
	void gettedWantToo(Message msg);
	void gettedDontWant(Message msg);
	void gettedLeave(Message msg);

        LamportAlgorithm();
        virtual ~LamportAlgorithm();
    protected:
    private:
	int gettedResponses;
        vector< vector<int> > clockList;
        LamportClock *clock;

	void enterToCriticalSection();
        void leaveCriticalSection();


	Message createMessage();
	string showMsgType(int TAG);
	void addToList(int id, int time);
	bool canEnter();
	void makeAction(Message msg, int TAG);
};

#endif // LAMPORTALGORITHM_H
