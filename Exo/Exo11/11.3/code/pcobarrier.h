#ifndef PCOBARRIER_H
#define PCOBARRIER_H
#include<pcosynchro/pcohoaremonitor.h>

class PcoBarrier:PcoHoareMonitor
{
private:
   unsigned nbToWait, nbWaiting;
   Condition cond;

public:
    PcoBarrier(unsigned int nbToWait):nbToWait(nbToWait), nbWaiting(0),cond(Condition())
    {
    }

    ~PcoBarrier()
    {
    }

    void wait()
    {
        monitorIn();
        nbWaiting++;
        if(nbWaiting < nbToWait){
            PcoHoareMonitor::wait(cond);
        }
        PcoHoareMonitor::signal(cond);
        monitorOut();
    }
};

#endif // PCOBARRIER_H
