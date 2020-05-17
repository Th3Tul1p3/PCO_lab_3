//    ___  _________    ___  ___  ___  ___  //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  |/ _ \ //
//  / ___/ /__/ /_/ / / __// // / __// // / //
// /_/   \___/\____/ /____/\___/____/\___/  //
//                                          //
// Auteurs : Arn Jerôme, Bonzon Tiffany
//
#ifndef SHAREDSECTION_H
#define SHAREDSECTION_H

#include <QDebug>

#include <pcosynchro/pcosemaphore.h>

#include "locomotive.h"
#include "ctrain_handler.h"
#include "sharedsectioninterface.h"

/**
 * @brief La classe SharedSection implémente l'interface SharedSectionInterface qui
 * propose les méthodes liées à la section partagée.
 */
class SharedSection final : public SharedSectionInterface
{
public:

    /**
     * @brief SharedSection Constructeur de la classe qui représente la section partagée.
     * Initialisez vos éventuels attributs ici, sémaphores etc.
     */
    SharedSection(): isFree(true),nbHigh(0), nbWaiting(0), mutex(1), mutexPriority(1), waitingLoco(0) {
    }

    /**
     * @brief request Méthode a appeler pour indiquer que la locomotive désire accéder à la
     * section partagée (deux contacts avant la section partagée).
     * @param loco La locomotive qui désire accéder
     * @param priority La priorité de la locomotive qui fait l'appel
     */
    void request(Locomotive& loco, Priority priority) override {
        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 requested the shared section.").arg(loco.numero())));
        mutexPriority.acquire();
        if(priority == Priority::HighPriority)
            nbHigh++;
        mutexPriority.release();
    }

    void prepareRail(Locomotive &loco)
    {
        unsigned int direction;
        if(loco.numero() == 7)
            direction = DEVIE;
        else
            direction = TOUT_DROIT;

        diriger_aiguillage(8,  direction, 0);
        diriger_aiguillage(9,  direction, 0);
    }

    /**
     * @brief getAccess Méthode à appeler pour accéder à la section partagée, doit arrêter la
     * locomotive et mettre son thread en attente si la section est occupée ou va être occupée
     * par une locomotive de plus haute priorité. Si la locomotive et son thread ont été mis en
     * attente, le thread doit être reveillé lorsque la section partagée est à nouveau libre et
     * la locomotive redémarée. (méthode à appeler un contact avant la section partagée).
     * @param loco La locomotive qui essaie accéder à la section partagée
     * @param priority La priorité de la locomotive qui fait l'appel
     */
    void getAccess(Locomotive &loco, Priority priority) override {
        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 accesses the shared section.").arg(loco.numero())));
        bool isStop = false;
        mutex.acquire();
        while(!isFree || (priority == SharedSectionInterface::Priority::LowPriority && nbHigh > 0)){
            loco.arreter();
            isStop = true;
            nbWaiting++;
            mutex.release();
            waitingLoco.acquire();
            mutex.acquire();
        }
        isFree = false;

        // préparation des aiguillages pour le train
        prepareRail(loco);

        // lancement de la locomotive et bloquage de la section partagée
        if (isStop)
            loco.demarrer();
        if(priority == Priority::HighPriority)
            nbHigh--;
        mutex.release();
        return;
    }

    /**
     * @brief leave Méthode à appeler pour indiquer que la locomotive est sortie de la section
     * partagée. (reveille les threads des locomotives potentiellement en attente).
     * @param loco La locomotive qui quitte la section partagée
     */
    void leave(Locomotive& loco) override {
        afficher_message(qPrintable(QString("The engine no. %1 leaves the shared section.").arg(loco.numero())));
        // libération de la zone partagée et envoi d'un "signal" à la locolotive qui attend
        mutex.acquire();
        isFree = true;
        if(nbWaiting){
            waitingLoco.release();
            nbWaiting--;
        }
        mutex.release();
    }

private:
    bool isFree;
    unsigned nbHigh, nbWaiting;
    PcoSemaphore mutex, mutexPriority,waitingLoco;
};


#endif // SHAREDSECTION_H
