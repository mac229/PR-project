#ifndef LAMPORTALGORITHM_H
#define LAMPORTALGORITHM_H

#include "Wiadomosc.h"
#include <iostream>

using namespace std;

class LamportAlgorithm
{
    public:
        void sendToAll();
        void receiveFromAll();

        void send();
        void receive();

        LamportAlgorithm();
        virtual ~LamportAlgorithm();
    protected:
    private:
};

#endif // LAMPORTALGORITHM_H
