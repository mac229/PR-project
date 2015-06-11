#ifndef LAMPORTALGORITHM_H
#define LAMPORTALGORITHM_H

#include <iostream>
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

        void sendToAll();
        void receiveFromAll();
        void enterToCriticalSection();
        void leaveCriticalSection();

        void send(int to);
        void receive();

        LamportAlgorithm(int id);
        virtual ~LamportAlgorithm();
    protected:
    private:
};

#endif // LAMPORTALGORITHM_H
