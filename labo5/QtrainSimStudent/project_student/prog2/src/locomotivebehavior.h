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
#include "locoSSPoints.h"

/**
 * @brief La classe LocomotiveBehavior représente le comportement d'une locomotive
 */
class LocomotiveBehavior : public Launchable
{
private:
    int startPos;
    SharedSectionInterface::Priority priority;
    LocoSSPoint points;
    // Indique la direction de la locomotive (true si direction initiale, false autrement)
    bool direction;
public:
    /*!
     * \brief locomotiveBehavior Constructeur de la classe
     * \param loco la locomotive dont on représente le comportement
     */
    LocomotiveBehavior(Locomotive& loco, std::shared_ptr<SharedSectionInterface> sharedSection, int startPos, LocoSSPoint pointsLoco) : loco(loco),
                                                                                                                                        sharedSection(sharedSection),
                                                                                                                                        startPos(startPos),
                                                                                                                                        points(pointsLoco)
    {
        direction = true;
        if(loco.priority == 1) {
            priority = SharedSectionInterface::Priority::HighPriority;
        } else {
            priority = SharedSectionInterface::Priority::LowPriority;
        }
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

    /*
     * Vous êtes libres d'ajouter des méthodes ou attributs
     *
     * Par exemple la priorité ou le parcours
     */

    /**
     * @brief accessSharedSection Fonction permettant à une loco de demander l'accès, d'entrer et de sortir de la SS
     */
    void accessSharedSection();
};

#endif // LOCOMOTIVEBEHAVIOR_H
