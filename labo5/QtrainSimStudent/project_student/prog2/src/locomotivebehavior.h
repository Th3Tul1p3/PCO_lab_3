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
#include "ctrain_handler.h"
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
    LocomotiveBehavior(Locomotive& loco,
                       std::shared_ptr<SharedSectionInterface> &sharedSection ,
                       const QVector<int> &contactList,
                       const QVector<int> &acceptContact,
                       const QVector<int> &requestContact) :
        loco(loco),
        sharedSection(sharedSection),
        contactList(contactList),
        acceptContact(acceptContact),
        requestContact(requestContact){
        priority = loco.priority > 0? SharedSectionInterface::Priority::HighPriority : SharedSectionInterface::Priority::LowPriority;
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


private:
    QVector<int> contactList;
    void getAccessSS(unsigned int actualContact);
    void getRequestSS(unsigned int actualContact);
    // contacts auquel on accepte ou non l'accès
    QVector<int> acceptContact;
    // contacts auquel on demande l'accès
    QVector<int> requestContact;
    // garde une trace de la demande de bloquage de la section paratagée
    bool sharedSectionAccessed = false;
    bool sharedSectionRequested = false;
    // conversion en niveau de priorité
    SharedSectionInterface::Priority priority;
    void processContat(int contact);
};

#endif // LOCOMOTIVEBEHAVIOR_H
