
#include <pcosynchro/pcosemaphore.h>
#include <pcosynchro/pcoconditionvariable.h>

class BridgeManagerFloat
{
    float Max, current;
    PcoConditionVariable cond;
    PcoMutex mut;
public:
    BridgeManagerFloat(float maxWeight): Max(maxWeight), current(0)
    {

    }

    ~BridgeManagerFloat()
    {

    }

    void access(float weight)
    {
        mut.lock();
        while(current + weight > Max)
            cond.wait(&mut);
        current += weight;
        mut.unlock();
    }

    void leave(float weight)
    {
        mut.lock();
        current -= weight;
        cond.notifyOne();
        mut.unlock();
    }
};
