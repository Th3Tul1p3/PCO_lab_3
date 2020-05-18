//    ___  _________    ___  ___  ___  ___  //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  |/ _ \ //
//  / ___/ /__/ /_/ / / __// // / __// // / //
// /_/   \___/\____/ /____/\___/____/\___/  //
//                                          //
// Auteurs : Arn Jerôme, Bonzon Tiffany
//
#include "locomotivebehavior.h"
#include "ctrain_handler.h"

void LocomotiveBehavior::run()
{
    //Initialisation de la locomotive
    loco.allumerPhares();
    loco.demarrer();
    loco.afficherMessage("Ready!");

    attendre_contact(startPos);

    while(1) {
        // Faire 2 tours avant de changer de sens
        for(uint i = 0; i < 2; ++i) {
            accessSharedSection();
            attendre_contact(startPos);
        }

        // Changement de sens
        direction = !direction;
        loco.inverserSens();
    }
}

void LocomotiveBehavior::printStartMessage()
{
    qDebug() << "[START] Thread de la loco" << loco.numero() << "lancé";
    QString msg = "Je suis lancée en priorité ";
    if(priority == SharedSectionInterface::Priority::HighPriority) {
        msg.append("High");
    } else {
        msg.append("Low");
    }
    msg.append(" !");
    loco.afficherMessage(msg);
}

void LocomotiveBehavior::printCompletionMessage()
{
    qDebug() << "[STOP] Thread de la loco" << loco.numero() << "a terminé correctement";
    loco.afficherMessage("J'ai terminé");
}

void LocomotiveBehavior::accessSharedSection() {
    // Demande d'accès
    if(direction) {
        attendre_contact(points.requestInitDirection);
    } else {
        attendre_contact(points.requestChangedDirection);
    }
    sharedSection->request(loco, priority);

    // Accès à la SS à partir de ces points
    if(direction) {
        attendre_contact(points.accessInitDirection);
    } else {
        attendre_contact(points.accessChangedDirection);
    }
    sharedSection->getAccess(loco, priority);

    // Loco sortie de la SS à partir de ces points
    if(direction) {
        attendre_contact(points.exitInitDirection);
    } else {
        attendre_contact(points.exitChangedDirection);
    }
    sharedSection->leave(loco);

}
