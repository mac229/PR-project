#include "../inc/LamportClock.h"

void LamportClock::increment(){
    time++;
}

void LamportClock::checkAndSet(int getted){
    if (getted > time)
        time = getted;
    time++;
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
