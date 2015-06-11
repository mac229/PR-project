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
        vector< vector<int> > clockList;
        LamportClock *clock;

        void sendToAll(int TAG);
        void send(int TO, int TAG);
        
	void receiveFromAll();
	void receiveRequestFromAll();
	void receiveRequest();
        Message receive(int TAG);

        LamportAlgorithm();
        virtual ~LamportAlgorithm();
    protected:
    private:
	void start();

	void enterToCriticalSection();
        void leaveCriticalSection();


	Message createMessage();
	void addToList(int id, int time);
	void makeAction(int TAG);
};

#endif // LAMPORTALGORITHM_H
