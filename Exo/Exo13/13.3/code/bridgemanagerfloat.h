
#include <pcosynchro/pcosemaphore.h>
#include<pcosynchro/pcohoaremonitor.h>

class BridgeManagerFloat:PcoHoareMonitor
{
private:
    float Max, current;
    Condition cond;
public:
    BridgeManagerFloat(float maxWeight):Max(maxWeight),current(0),cond(Condition())
    {

    }

    ~BridgeManagerFloat()
    {

    }

    void access(float weight)
    {
        monitorIn();
        while(current + weight > Max)
            wait(cond);
        current += weight;
        monitorOut();
    }

    void leave(float weight)
    {
        monitorIn();
        current -= weight;
        signal(cond);
        monitorOut();
    }
};
