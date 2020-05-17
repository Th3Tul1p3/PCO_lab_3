//    ___  _________    ___  ___  ___  ___  //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  |/ _ \ //
//  / ___/ /__/ /_/ / / __// // / __// // / //
// /_/   \___/\____/ /____/\___/____/\___/  //
//                                          //
// Auteurs : Arn Jerôme, Bonzon Tiffany
//
#ifndef LOCOMOTIVEBEHAVIOR_H
#define LOCOMOTIVEBEHAVIOR_H

#include "locomotive.h"
#include "launchable.h"
#include "sharedsectioninterface.h"
#include <QVector>

/**
 * @brief La classe LocomotiveBehavior représente le comportement d'une locomotive
 */
class LocomotiveBehavior : public Launchable
{
public:
    /*!
     * \brief locomotiveBehavior Constructeur de la classe
     * \param loco la locomotive dont on représente le comportement
     */
    LocomotiveBehavior(Locomotive& loco, std::shared_ptr<SharedSectionInterface> sharedSection , QVector<int> contactList, unsigned int contatPointsTD,unsigned int contactPointsD) :
        loco(loco), sharedSection(sharedSection), contactList(contactList),CONTACT_POINTS_1(contatPointsTD), CONTACT_POINTS_2(contactPointsD){
    }

protected:
    /*!
     * \brief run Fonction lancée par le thread, représente le comportement de la locomotive
     */
    void run() override;

    /*!
     * \brief printStartMessage Message affiché lors du démarrage du thread
     */
    void printStartMessage() override;

    /*!
     * \brief printCompletionMessage Message affiché lorsque le thread a terminé
     */
    void printCompletionMessage() override;

    /**
     * @brief loco La locomotive dont on représente le comportement
     */
    Locomotive& loco;

    /**
     * @brief sharedSection Pointeur sur la section partagée
     */
    std::shared_ptr<SharedSectionInterface> sharedSection;

    QVector<int> contactList;
    /*
     * Vous êtes libres d'ajouter des méthodes ou attributs
     *
     * Par exemple la priorité ou le parcours
     */
private:
    void getAccessSS(unsigned int actualContact, unsigned int pointsTD, unsigned int pointsD);
    // contact auquel on change l'aiguillage sur tout droit
    const unsigned int CONTACT_POINTS_1;
    // contact auquel on change l'aiguillage sur dévié
    const unsigned int CONTACT_POINTS_2;
    // garde une trace de la demande de bloquage de la section paratagée
    bool sharedSectionRequested = false;
};

#endif // LOCOMOTIVEBEHAVIOR_H
