//    ___  _________    ___  ___  ___  ___  //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  |/ _ \ //
//  / ___/ /__/ /_/ / / __// // / __// // / //
// /_/   \___/\____/ /____/\___/____/\___/  //
//                                          //
// Auteurs : Arn Jerôme, Bonzon Tiffany
//
#include "locomotivebehavior.h"
#include "ctrain_handler.h"
#include <algorithm>

#define NB_TOUR_CHANGEMENT_SENS 2

void LocomotiveBehavior::getAccessSS(unsigned int actualContact)
{
    // si les contacts sont ceux qui permettent l'accès à la section partagée
    if(qFind(acceptContact.begin(),acceptContact.end(), actualContact) != acceptContact.end()){
        if(!sharedSectionAccessed){
            sharedSection->getAccess(loco,priority);
        }else{
            sharedSection->leave(loco);
        }
        sharedSectionAccessed = !sharedSectionAccessed;
    }
}

void LocomotiveBehavior::getRequestSS(unsigned int actualContact)
{
    // si les contacts sont ceux pour la requête de section partagée
    if(qFind(requestContact.begin(),requestContact.end(), actualContact) != requestContact.end()){
        if(!sharedSectionRequested){
            sharedSection->request(loco,priority);
            sharedSectionRequested = !sharedSectionRequested;
        }else{
            sharedSectionRequested = !sharedSectionRequested;
        }
    }
}

void LocomotiveBehavior::processContat(int contact)
{
    attendre_contact(contactList.at(contact));
    getRequestSS(contactList.at(contact));
    getAccessSS(contactList.at(contact));
}

void LocomotiveBehavior::run()
{
    //Initialisation de la locomotive
    loco.allumerPhares();
    loco.demarrer();
    loco.afficherMessage("Ready!");

    // la loco commence par attendre le premier prochain contact
    attendre_contact(contactList.at(0));
    while(1) {
        // effectue NB_TOUR_CHANGEMENT_SENS fois un tour de circuit
        for(int i = 0; i < NB_TOUR_CHANGEMENT_SENS; i ++)
            for(int j = 1; j < contactList.size(); j++){
                processContat(j);
            }
        loco.inverserSens();

        // effectue NB_TOUR_CHANGEMENT_SENS fois un tour de circuit
        for(int i = 0; i < NB_TOUR_CHANGEMENT_SENS; i ++)
            for(int j = contactList.size() - 2; j >= 0; j--){
                processContat(j);
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
