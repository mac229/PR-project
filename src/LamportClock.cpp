#include "../inc/LamportClock.h"
/*
MPI_Send(&tablica[i], 1, MPI_INT, 1, MSG_TAG, MPI_COMM_WORLD);
//MPI_SEND( skąd, ile, typ, do kogo, z jakim tagiem, MPI_COMM_WORLD)

MPI_Recv(&sorted[i], 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
//    MPI_Recv( gdzie, ile , jakiego typu, od kogo, z jakim tagiem, MPI_COMM_WORLD, &status);
*/

void LamportClock::increment(){
    time++;
}

void LamportClock::checkAndSet(int getted){
    if (getted > time)
        time = getted;
    increment();
}

int LamportClock::getID(){
    return id;
}

int LamportClock::getTime(){
    return time;
}

LamportClock::LamportClock(int nr)
{
    id = nr;
    time = 0;
}

LamportClock::~LamportClock()
{
    //dtor
}
