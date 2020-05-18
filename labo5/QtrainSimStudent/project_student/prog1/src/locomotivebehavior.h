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

/**
 * @brief La classe LocomotiveBehavior représente le comportement d'une locomotive
 */
class LocomotiveBehavior : public Launchable
{
private:
    int startPos;

    // Indique la direction des locomotives (true si direction initiale, false autrement)
    //  Serait mieux d'avoir cet attribut dans la classe Locomotive
    bool initialDirectionLocoA, initialDirectionLocoB;
public:
    /*!
     * \brief locomotiveBehavior Constructeur de la classe
     * \param loco la locomotive dont on représente le comportement
     */
    LocomotiveBehavior(Locomotive& loco, std::shared_ptr<SharedSectionInterface> sharedSection, int startPos /*, autres paramètres éventuels */) : loco(loco),
                                                                                                                                                   sharedSection(sharedSection),
                                                                                                                                                   startPos(startPos),
                                                                                                                                                   initialDirectionLocoA(true),
                                                                                                                                                   initialDirectionLocoB(true) {
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

    /**
     * @brief accessSharedSection Fonction permettant à une loco d'entrer et de sortir de la SS
     * @param isInitDirection Un bool indiquant la direction de la loco
     * @param entryInitDirection Le point de contact avant l'entrée de la loco si elle va dans sa direction initiale
     * @param entryChangedDirection Le point de contact avant l'entrée de la loco si elle ne va pas dans sa direction initiale
     * @param exitInitDirection Le point de sortie si la loco va dans sa direction initiale
     * @param exitChangedDirection Le point de sortie si la loco ne va pas dans sa direction initiale
     */
    void accessSharedSection(bool isInitDirection, int entryInitDirection, int entryChangedDirection, int exitInitDirection, int exitChangedDirection);
};

#endif // LOCOMOTIVEBEHAVIOR_H
