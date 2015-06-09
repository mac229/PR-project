#ifndef LAMPORTCLOCK_H
#define LAMPORTCLOCK_H


class LamportClock
{
    public:
        void increment();
        void checkAndSet(int getted);
        int getID();
        int getTime();

        LamportClock(int nr);
        virtual ~LamportClock();
    protected:
    private:
        int id;
        int time;
};

#endif // LAMPORTCLOCK_H
