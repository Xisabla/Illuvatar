#include "map/PathFinder.h"

using namespace std;


PathFinder::PathFinder(Map const &map, Tile const &current, Tile const &target, Direction const &initialDirection): 
    map(map), current(current), target(target), initialDirection(initialDirection) {
    this->path = this->straightener(this->unlooper(this->aStarGenerator()));
}

vector<pair<Tile*, Direction>> PathFinder::getResult(int const nbTile) {
    this->path.resize(min(this->path.size(), nbTile));
    return this->path;
}

vector<Tile*> PathFinder::aStarGenerator(vector<Tile*> &path=vector()) {
    if (this->current == this->target) {
        this->explored.clear();
        this->notExplored.clear();
        return path;
    }

    this->explored.append(this->current);

    vector<Tile*> notExploredNeighbords = vector();
    for (Direction direction = Direction::Begin; direction != Direction::End; ++direction) { //get all enum values
        int nextX = this->tile->X() + DirectionUtils::nextDirection.at(direction)->X();
        int nextY = this->tile->Y() + DirectionUtils::nextDirection.at(direction)->Y();
        if (!this->map.exist(nextX, nextY)) continue;

        Tile* neighbor = this->map.getTile(nextX, nextY);
        if (neighbor.getThingOnMap() == ThingOnMap::Obstacle) continue;
        if (find(this->explored.begin(), this->explored.end(), neighbor) != this->explored.end()) continue;

        notExploredNeighbords.push_back(neighbor);
    }

    if (!notExploredNeighbords.empty()) {
        sort(notExploredNeighbords.begin(), notExploredNeighbords.end(),
            [](Tile &a, Tile &b) { return this->distanceToCurrent(a) < this->distanceToCurrent(b); })

        this->current = notExploredNeighbords[0];

        reverse(notExploredNeighbords.begin(), notExploredNeighbords.end());
        notExploredNeighbords.pop_back();

        move(notExploredNeighbords.begin(), notExploredNeighbords.end(), back_inserter(this->notExplored));
    }
    else if (!notExplored.empty()) {
        this->current = this->notExplored.back();
        this->notExplored.pop_back();
    }
    else {
        cout << "fucked up" << endl;
    }

    path.push_back(this->current);
    return this->aStarGenerator(path);
}

double PathFinder::distanceToCurrent(Tile &other) {
    return sqrt(pow(this->current->X() - other.X(), 2) + pow(this->current->Y() - other.Y(), 2))
}

vector<Tile*> PathFinder::unlooper(vector<Tile*> &refPath, vector<Tile*> &path=vector(), int pos=1) {
    if (pos == this->path.size()) {
        refPath.clear();
        return path;
    }

    vector<pair<Tile*, int>> neighbors = vector();
    map<Tile*, int> nbNeighs = map();
    for (int i = pos; i < refPath.size(); ++i) {
        Tile tile = refPath[i];
        if (refPath[pos - 1].isNeighbor(tile)) { //todo : bool Tile::isNeighbor(const &other)
            neighbors.push_back({ tile, i });

            nbNeighs.count(tile) ?
                neighbors[tile]++ :
                neighbors.insert({ tile, 1 });
        }
    }

    for (int i = neighbors.size() - 1; i >= 0; --i) {
        pair<Tile*, int> neigh = neighbors[i];
        if (nbNeighs[neigh.first] == 1) {
            pos = neigh.second;
            path.push_back(neigh.first);
            break;
        }
    }

    return PathFinder::unlooper(refPath, path, pos);
}

vector<pair<Tile*, Direction>> PathFinder::straightener(vector<Tile*> &refPath, vector<pair<Tile*, Direction>> &path=vector(), int pos=0) {
    if (pos == this->path.size() + 4) {
        for (vector<Tile*>* iter = refPath.end() - 4; iter < refPath.end(); ++iter) {
            path.push_back({ this->map.getTile(&iter.X(), &iter.Y()), this->computeDirection(path.back().first, &iter) });
        }
        refPath.clear();
        return path;
    }

    Tile* current = refPath[pos];
    Tile* next = refPath[pos + 4];
    Tile bridge;
    Direction dir = path.empty() ? this->initialDirection : DirectionUtils::computeDirection(path.back().first, current);
    path.push_back({ current, dir });

    if (checkBothBridges(path, current.X() == next.X(), current, next, false, current.Y() - next.Y()) ||
        checkBothBridges(path, current.Y() == next.Y(), current, next, true,  current.X() - next.X())) {
        return this->straightener(refPath, path, pos + 5);
    }

    return this->straightener(refPath, path, pos + 1);
}

bool PathFinder::checkBothBridges(vector<pair<Tile*, Direction>> &path, bool alignTest, Tile* current, Tile* next, bool first, int deltaBridge) {
    return alignTest && 
            (this->checkBridge(path, Tile(next.X() - first, next.Y() - !first), deltaBridge == -2, current, next) ||
             this->checkBridge(path, Tile(next.X() + first, next.Y() + !first), deltaBridge == 2,  current, next))
}

bool PathFinder::checkBridge(vector<pair<Tile*, Direction>> &path, Tile bridge, bool alignTest, Tile* current, Tile* next) {
    if (alignTest && this->map.exist(bridge.X(), bridge.Y()) && this->map.getTile(bridge.X(), bridge.Y()).getThingOnMap() == ThingOnMap::Obstacle) {
        path.push_back({ this->map.getTile(bridge.X(), bridge.Y()), DirectionUtils::computeDirection(current, bridge) });
        path.push_back({ this->map.getTile(next.X(),   next.Y()),   DirectionUtils::computeDirection(bridge, next)    });
        return true;
    }

    return false;
}
