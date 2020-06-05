#ifndef PCOBARRIER_H
#define PCOBARRIER_H
#include<pcosynchro/pcoconditionvariable.h>
#include<pcosynchro/pcosemaphore.h>
class PcoBarrier
{
private:
    unsigned nbtwait, nbWaiting;
    PcoConditionVariable cond;
    PcoMutex mutex;
public:
    PcoBarrier(unsigned int nbToWait):nbWaiting(0),nbtwait(nbToWait)
    {
    }

    ~PcoBarrier()
    {
    }

    void wait()
    {
        mutex.lock();
        nbWaiting++;
        if (nbWaiting < nbtwait){
            cond.wait(&mutex);
        }else{
            cond.notifyAll();
        }
        nbWaiting--;
        mutex.unlock();
    }
};

#endif // PCOBARRIER_H
