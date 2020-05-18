//    ___  _________    ___  ___  ___  ___  //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  |/ _ \ //
//  / ___/ /__/ /_/ / / __// // / __// // / //
// /_/   \___/\____/ /____/\___/____/\___/  //
//                                          //
// Auteurs : Arn Jerôme, Bonzon Tiffany
//

#ifndef LOCOSSPOINTS_H
#define LOCOSSPOINTS_H

/**
 * @brief La classe LocoSSPoint est une classe de données concernant les points importants
 *          pour la section partagée (point de requête, d'accès, de sortie)
 */
class LocoSSPoint {
public:
    int requestInitDirection,       // Le point où la locomotive fait sa requête si elle va dans le sens initial
        requestChangedDirection,    // Le point où la locomotive fait sa requête si elle ne va pas dans le sens initial
        accessInitDirection,        // Le point où la locomotive fait son access si elle va dans le sens initial
        accessChangedDirection,     // Le point où la locomotive fait son access si elle ne va pas dans le sens initial
        exitInitDirection,          // Le point où la locomotive fait sa sortie si elle va dans le sens initial
        exitChangedDirection;       // Le point où la locomotive fait sa sortie si elle ne va pas dans le sens initial
};

#endif // LOCOSSPOINTS_H
