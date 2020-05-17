//    ___  _________    ___  ___  ___  ___  //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  |/ _ \ //
//  / ___/ /__/ /_/ / / __// // / __// // / //
// /_/   \___/\____/ /____/\___/____/\___/  //
//                                          //
// Auteurs : Arn Jerôme, Bonzon Tiffany
//
#include "locomotivebehavior.h"
#include "ctrain_handler.h"

#define NB_TOUR_CHANGEMENT_SENS 2

void LocomotiveBehavior::getAccessSS(unsigned int actualContact, unsigned int points1, unsigned int points2)
{
    // si les contacts sont ceux d'entrée ou de sortie on réserve ou libère la section paratagée
    if(actualContact == points1 || actualContact == points2){
        if(!sharedSectionRequested){
            sharedSectionRequested = !sharedSectionRequested;
            sharedSection->getAccess(loco,SharedSectionInterface::Priority::LowPriority);
        }else{
            sharedSectionRequested = !sharedSectionRequested;
            sharedSection->leave(loco);
        }
    }
}

void LocomotiveBehavior::run()
{
    //Initialisation de la locomotive
    loco.allumerPhares();
    loco.demarrer();
    loco.afficherMessage("Ready!");

    // Vous pouvez appeler les méthodes de la section partagée comme ceci :
//    sharedSection->request(loco,SharedSectionInterface::Priority::LowPriority);
//    sharedSection->getAccess(loco,SharedSectionInterface::Priority::LowPriority);
//    sharedSection->leave(loco);

    // la loco commence par attendre le premier prochain contact
    attendre_contact(contactList.at(0));
    while(1) {
        // effectue NB_TOUR_CHANGEMENT_SENS fois un tour de circuit
        for(int i = 0; i < NB_TOUR_CHANGEMENT_SENS; i ++)
            for(int j = 1; j < contactList.size(); j++){
                attendre_contact(contactList.at(j));
                getAccessSS(contactList.at(j), CONTACT_POINTS_1, CONTACT_POINTS_2);
            }
        loco.inverserSens();

        // effectue NB_TOUR_CHANGEMENT_SENS fois un tour de circuit
        for(int i = 0; i < NB_TOUR_CHANGEMENT_SENS; i ++)
            for(int j = contactList.size() - 2; j >= 0; j--){
                attendre_contact(contactList.at(j));
                getAccessSS(contactList.at(j), CONTACT_POINTS_1, CONTACT_POINTS_2);
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
    loco.afficherMessage("J'ai terminé");
}
