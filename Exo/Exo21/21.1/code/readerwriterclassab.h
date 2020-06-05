/** @file readerwriterclassab.h
 *  @brief Reader-writer with equal priority between two classes
 *
 *  Implementation of a reader-writer resource manager with equal
 *  priority for both classes. Mutual exclusion between classes must be
 *  ensured
 *
 *
 *
 *  @author Yann Thoma
 *  @date 15.05.2017
 *  @bug No known bug
 */

#ifndef READERWRITERCLASSAB_H
#define READERWRITERCLASSAB_H

#include <pcosynchro/pcosemaphore.h>
#include <pcosynchro/pcohoaremonitor.h>

#include "abstractreaderwriter.h"


class ReaderWriterClassAB
{
protected:
    PcoSemaphore mutex, waitA, waitB;
    int nbWaitA, nbWaitB, nbA,nbB;
public:
  ReaderWriterClassAB():mutex(1), waitA(0),waitB(0),nbWaitA(0),nbWaitB(0),nbA(0),nbB(0){
  }

  void lockA() {
      mutex.acquire();
      nbWaitA++;
      while(nbB >0){
          mutex.release();
          waitA.acquire();
          mutex.acquire();
      }
      nbWaitA--;

      if(nbWaitA > 0 )waitA.release();

      nbA++;
      mutex.release();
  }

  void unlockA() {
      mutex.acquire();
      nbA--;
      if(nbA==0)
          waitB.release();
      mutex.release();
  }

  void lockB() {
      mutex.acquire();
      nbWaitB++;
      while(nbA >0){
          mutex.release();
          waitB.acquire();
          mutex.acquire();
      }
      nbWaitB--;

      if(nbWaitB > 0 )waitB.release();

      nbB++;
      mutex.release();
  }

  void unlockB() {
      mutex.acquire();
      nbB--;
      if(nbB==0)
          waitA.release();
      mutex.release();
  }
};
#endif // READERWRITERCLASSAB_H
