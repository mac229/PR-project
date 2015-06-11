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
        vector<int> clockList;
        LamportClock *clock;

        void sendToAll(int TAG);
        void receiveFromAll();
        void enterToCriticalSection();
        void leaveCriticalSection();

        void send(int TO, int TAG);
        void receive();

        LamportAlgorithm();
        virtual ~LamportAlgorithm();
    protected:
    private:
	void makeAction(int TAG);
};

#endif // LAMPORTALGORITHM_H
