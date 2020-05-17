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
#include <pcosynchro/pcomutex.h>

#include "locomotive.h"
#include "ctrain_handler.h"
#include "sharedsectioninterface.h"

/**
 * @brief La classe SharedSection implémente l'interface SharedSectionInterface qui
 * propose les méthodes liées à la section partagée.
 */
class SharedSection final : public SharedSectionInterface
{  
private:
    // Méthodes privées ...
    // Attributes privés ...
    PcoMutex mutex;
    PcoSemaphore synchro;
    bool isSectionFree;

public:

    /**
     * @brief SharedSection Constructeur de la classe qui représente la section partagée.
     * Initialisez vos éventuels attributs ici, sémaphores etc.
     */
    SharedSection() : synchro(0), isSectionFree(true) {}

    /**
     * @brief request Méthode a appeler pour indiquer que la locomotive désire accéder à la
     * section partagée (deux contacts avant la section partagée).
     * @param loco La locomotive qui désire accéder
     * @param priority La priorité de la locomotive qui fait l'appel
     */
    void request(Locomotive& loco, Priority priority) override {
        // TODO prog2

        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 requested the shared section.").arg(loco.numero())));
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
        bool isLocoStopped = false;

        mutex.lock();

        // Attente que la section se  libère
        while(!isSectionFree) {
            loco.arreter();
            isLocoStopped = true;
            mutex.unlock();
            synchro.acquire();
        }

        // Mise en place des aiguillages une fois la SS libérée
        if(loco.numero() == 7) {
            diriger_aiguillage(3,  TOUT_DROIT, 0);
            diriger_aiguillage(4,  DEVIE     , 0);
            diriger_aiguillage(7,  DEVIE     , 0);
            diriger_aiguillage(8,  TOUT_DROIT, 0);
        } else { //Loco 42
            diriger_aiguillage(3,  DEVIE     , 0);
            diriger_aiguillage(4,  TOUT_DROIT, 0);
            diriger_aiguillage(7,  TOUT_DROIT, 0);
            diriger_aiguillage(8,  DEVIE     , 0);
        }

        // La loco entre dans la SS
        if(isLocoStopped) {
            loco.demarrer();
        }
        isSectionFree = false;

        mutex.unlock();

        // Messages d'entrée global + spécifique à la locomotive
        afficher_message(qPrintable(QString("The engine no. %1 accesses the shared section.").arg(loco.numero())));
        loco.afficherMessage("Entrée dans la section partagée");
    }

    /**
     * @brief leave Méthode à appeler pour indiquer que la locomotive est sortie de la section
     * partagée. (reveille les threads des locomotives potentiellement en attente).
     * @param loco La locomotive qui quitte la section partagée
     */
    void leave(Locomotive& loco) override {
        mutex.lock();

        synchro.release();
        isSectionFree = true;

        mutex.unlock();

        // Messages de sortie global + spécifique à la locomotive
        afficher_message(qPrintable(QString("The engine no. %1 leaves the shared section.").arg(loco.numero())));
        loco.afficherMessage("Sortie de la section partagée");
    }

    /* A vous d'ajouter ce qu'il vous faut */
};


#endif // SHAREDSECTION_H
