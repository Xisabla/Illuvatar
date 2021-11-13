/*=========================================================================

  Project:   Illuvatar
  File:      GoodMinion.cpp

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#include "characters/GoodMinion.h"
#include "unirand.h"

//  --------------------------------------------------------------------------------------
//  GoodMinion
//  --------------------------------------------------------------------------------------

GoodMinion::GoodMinion(unsigned int x, unsigned int y, Faction faction): Minion(x, y, faction) { }

//  --------------------------------------------------------------------------------------
//  GoodMinion > PUBLIC METHODS
//  --------------------------------------------------------------------------------------

void GoodMinion::specialAttack(Minion* minion) {
    int damages = std::max(1, unirand::getValueAround(this->getEnergyReduction(), 2));
    printAction("Inflige "+std::to_string(damages)+" points de dégâts énergétique(s) à l'ennemi !");
    minion->reduceEnergy(damages);
    this->normalAttack(minion);
}
