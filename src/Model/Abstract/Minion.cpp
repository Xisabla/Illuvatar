#include "Minion.h"

void Minion::Move()
{   
    int nbTile = rand() % (this->rangeMax - this->rangeMin + 1) + this->rangeMin;

    this->currentDirection = energy - nbTile > lowEnergy ? //soit avant sans la soustraction, soit ici
                            this->Explorate() :
                            this->FindMaster(Master());

    for (int i; i < nbTile; ++i) {
        swith(this->CheckDirection(this->currentDirection)) {
            case ThingOnMap::Nothing:
                //avance d'une tile et dépense de l'énergie
                break;

            case ThingOnMap::Obstacle:
                return;
        }

        for (ThingOnMap thing : this->CheckAround()) {
            swith() {
                case ThingOnMap::Ally:
                    //échange les infos
                    return;

                case ThingOnMap::Ennemy:
                    //fight
                    return;
            }
        }
    }
}

Direction Minion::Explorate() {
    vector<Direction> possibleDirs = vector();

    for (Direction dir : Minion.fanDirections[this->currentDirection]) {
        if (this->CheckDirection(dir) == ThingOnMap::Nothing) possibleDirs.push_back(dir);
    }

    return possibleDirs[rand() % possibleDirs.size()];
}

Direction Minion::FindMaster(Master const &master) {
    // do the a* or dijkstra pathfinder, then deduce the direction of the master (first move axis?)
    return Direction::S;
}

ThingOnMap Minion::CheckDirection(Direction const &direction)
{
    int nextX = this->tile->X() + Minion.nextDirection[direction]->X();
    int nextY = this->tile->Y() + Minion.nextDirection[direction]->Y();
    
    if (!this->map.exist(nextX, nextY)) return ThingOnMap::Void;//determine existence de la tuile

    Faction owner = this->map.getTile(nextX, nextY).getOwner());//determine contenu de la tuile

    if (owner == Faction::NoFaction) return ThingOnMap::Nothing;

    set<Faction> minionAllies = Minion.alliances[this->faction];
    return (minionAllies.find(owner) != minionAllies.end())? ThingOnMap::Ally : ThingOnMap::Ennemy;
}

vector<ThingOnMap> Minion::CheckAround()
{
    vector<ThingOnMap> things = vector();

    for (Direction direction = Direction::Begin; direction != Direction::End; ++direction) { //get all enum values
        ThingOnMap thing = CheckDirection(direction);
        if (thing == ThingOnMap::Ally || thing == ThingOnMap::Ennemy) things.push_back(thing);
    }

    return things;
}

void Minion::RollTheDice()
{

}

void Minion::Fight(Minion &minion)
{

}
