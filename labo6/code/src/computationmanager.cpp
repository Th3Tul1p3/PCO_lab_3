//    ___  _________    ___  ___  ___  ___  //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  |/ _ \ //
//  / ___/ /__/ /_/ / / __// // / __// // / //
// /_/   \___/\____/ /____/\___/____/\___/  //
//                                          //
// Auteurs : Prénom Nom, Prénom Nom


// A vous de remplir les méthodes, vous pouvez ajouter des attributs ou méthodes pour vous aider
// déclarez les dans ComputationManager.h et définissez les méthodes ici.
// Certaines fonctions ci-dessous ont déjà un peu de code, il est à remplacer, il est là temporairement
// afin de faire attendre les threads appelants et aussi afin que le code compile.

#include "computationmanager.h"
#include <utility>      // std::pair


ComputationManager::ComputationManager(int maxQueueSize): MAX_TOLERATED_QUEUE_SIZE(maxQueueSize), id(0), waitNotFullA(Condition()),
                                                                                                        waitNotFullB(Condition()),
                                                                                                        waitNotFullC(Condition()),
                                                                                                        waitNotEmptyA(Condition()),
                                                                                                        waitNotEmptyB(Condition()),
                                                                                                        waitNotEmptyC(Condition()),
                                                                                                        waitNotEmptyResult(Condition())

{
    // TODO
}

int ComputationManager::requestComputation(Computation c) {
    // TODO
    monitorIn();
    id ++;
    switch(c.computationType){
        case ComputationType::A:
            // on se met en attente si plus de place dans la file
            while(computationA.size() >= MAX_TOLERATED_QUEUE_SIZE)
                wait(waitNotFullA);

            // on ajoute le calcul à la file et on signale qu'il y a un calcul
            computationA.emplace(id, c);
            signal(waitNotEmptyA);
            break;
        case ComputationType::B:
            // on se met en attente si plus de place dans la file
            while(computationB.size() >= MAX_TOLERATED_QUEUE_SIZE)
                wait(waitNotFullB);

            // on ajoute le calcul à la file et on signale qu'il y a un calcul
            computationB.emplace(id, c);
            signal(waitNotEmptyB);
            break;
        case ComputationType::C:
            // on se met en attente si plus de place dans la file
            while(computationC.size() >= MAX_TOLERATED_QUEUE_SIZE)
                wait(waitNotFullC);

            // on ajoute le calcul à la file et on signale qu'il y a un calcul
            computationC.emplace(id, c);
            signal(waitNotEmptyC);
            break;
    }
    monitorOut();

    return id;
}

void ComputationManager::abortComputation(int id) {
    // TODO
}

Result ComputationManager::getNextResult() {
    // TODO
    std::map<int,Result>::iterator it;
    monitorIn();
    // si il n' y a pas de résultat on se met en attente
    while(resultMap.empty())
        wait(waitNotEmptyResult);
    it = resultMap.begin();
    resultMap.erase(it);
    monitorOut();

    return it->second;
}

Request ComputationManager::getWork(ComputationType computationType) {
    // TODO
    std::map<int, Computation> tmpPair;

    monitorIn();
    switch(computationType){
        case ComputationType::A:
            // si la file est vide on se met en attente
            while(computationA.size() == 0)
                wait(waitNotEmptyA);
            // on copie et efface le premier calcul de la file
            tmpPair.emplace(computationA.begin()->first,computationA.begin()->second);
            computationA.erase(computationA.begin());

            // on signal au buffer qu'il y a une place de libre
            signal(waitNotFullA);
            break;
        case ComputationType::B:
            // si la file est vide on se met en attente
            while(computationB.size() == 0)
                wait(waitNotEmptyB);

            // on copie et efface le premier calcul de la file
            tmpPair.emplace(computationB.begin()->first,computationB.begin()->second);
            computationB.erase(computationB.begin());

            // on signal au buffer qu'il y a une place de libre
            signal(waitNotFullB);
            break;
        case ComputationType::C:
            // si la file est vide on se met en attente
            while(computationC.size() == 0)
                wait(waitNotEmptyC);

            // on copie et efface le premier calcul de la file
            tmpPair.emplace(computationC.begin()->first,computationC.begin()->second);
            computationC.erase(computationC.begin());

            // on signal au buffer qu'il y a une place de libre
            signal(waitNotFullC);
            break;
    }
    monitorOut();

    return Request(tmpPair.begin()->second, tmpPair.begin()->first);
}

bool ComputationManager::continueWork(int id) {
    // TODO
    return true;
}

void ComputationManager::provideResult(Result result) {
    // on ajoute un résultat dans la file et on le signal
    monitorIn();
    resultMap.emplace(result.getId(),result);
    signal(waitNotEmptyResult);
    monitorOut();
}

void ComputationManager::stop() {
    // TODO
}
