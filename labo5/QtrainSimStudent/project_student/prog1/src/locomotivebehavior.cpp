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

    /* A vous de jouer ! */

    // Vous pouvez appeler les méthodes de la section partagée comme ceci :
    //sharedSection->request(loco);
    //sharedSection->getAccess(loco);
    //sharedSection->leave(loco);

    attendre_contact(startPos);

    while(1) {
        // Faire 2 tours avant de changer de sens
        for(uint i = 0; i < 2; ++i) {
            if(loco.numero() == 7) {
                accessSharedSection(initialDirectionLocoA, 16, 5, 6, 15);
            } else { //Loco 42
                accessSharedSection(initialDirectionLocoB, 12, 2, 3, 11);
            }
            attendre_contact(startPos);
        }

        // Changement de sens
        if(loco.numero() == 7) {
            initialDirectionLocoA = !initialDirectionLocoA;
        } else {
            initialDirectionLocoB = !initialDirectionLocoB;
        }
        loco.inverserSens();
    }
}

void LocomotiveBehavior::printStartMessage()
{
    qDebug() << "[START] Thread de la loco" << loco.numero() << "lancé";
    loco.afficherMessage("Je suis lancée !");
}

void LocomotiveBehavior::printCompletionMessage()
{
    qDebug() << "[STOP] Thread de la loco" << loco.numero() << "a terminé correctement";
}

void LocomotiveBehavior::accessSharedSection(bool isInitDirection, int entryInitDirection, int entryChangedDirection, int exitInitDirection, int exitChangedDirection) {
    // Accès à la SS à partir de ces points
    if(isInitDirection) {
        attendre_contact(entryInitDirection);
    } else {
        attendre_contact(entryChangedDirection);
    }
    sharedSection->getAccess(loco, SharedSectionInterface::Priority::HighPriority);

    // Loco sortie de la SS à partir de ces points
    if(isInitDirection) {
        attendre_contact(exitInitDirection);
    } else {
        attendre_contact(exitChangedDirection);
    }
    sharedSection->leave(loco);

}
