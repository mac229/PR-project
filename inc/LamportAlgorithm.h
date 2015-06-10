#ifndef LAMPORTALGORITHM_H
#define LAMPORTALGORITHM_H

#include <iostream>

using namespace std;

class LamportAlgorithm
{
    public:
        void sendToAll();
        void receive();

        LamportAlgorithm();
        virtual ~LamportAlgorithm();
    protected:
    private:
};

#endif // LAMPORTALGORITHM_H
