#include "map/PathFinder.h"

using namespace std;


PathFinder::PathFinder(Map const &map, Tile const &current, Tile const &target): 
    map(map), current(current), target(target) {
    this->path = this->straightener(this->unlooper(this->aStarGenerator()));
}

vector<Tile> PathFinder::getResult() {
    return this->path;
}

vector<Tile> PathFinder::aStarGenerator(vector<Tile> &path=vector()) {
    if (this->current == this->target) {
        this->explored.clear();
        this->notExplored.clear();
        return path;
    }

    this->explored.append(this->current);

    vector<Tile> notExploredNeighbords = vector();
    for (Direction direction = Direction::Begin; direction != Direction::End; ++direction) { //get all enum values
        int nextX = this->tile->X() + Utils.nextDirection[direction]->X();
        int nextY = this->tile->Y() + Utils.nextDirection[direction]->Y();
        if (!this->map.exist(nextX, nextY)) continue;

        Tile neighbor = this->map.getTile(nextX, nextY);
        if (find(this->explored.begin(), this->explored.end(), neighbor) != this->explored.end()) continue;

        notExploredNeighbords.push_back(neighbor);    
    }

    if (!notExploredNeighbords.empty()) {
        sort(notExploredNeighbords.begin(),
            notExploredNeighbords.end(),
            [](Tile &a, Tile &b) { return distanceToCurrent(a) < distanceToCurrent(b); })
        
        this->current = notExploredNeighbords[0]; //.at(0) sinon

        reverse(notExploredNeighbords.begin(), notExploredNeighbords.end());
        notExploredNeighbords.pop_back();

        move(notExploredNeighbords.begin(), notExploredNeighbords.end(), back_inserter(this->notExplored));
    }
    else {
        this->current = this->notExplored.back();
        this->notExplored.pop_back();
    }

    path.push_back(this->current);
    return this->aStarGenerator(path);
}

double PathFinder::distanceToCurrent(Tile &other) {
    return sqrt(pow(this->current->X() - other.X(), 2) + pow(this->current->Y() - other.Y(), 2))
}

vector<Tile> PathFinder::unlooper(vector<Tile> &refPath, vector<Tile> &path=vector(), int pos=1) {
    if (pos == this->path.size()) {
        refPath.clear();
        return path;
    }

    vector<pair<Tile, int>> neighbors = vector();
    map<Tile, int> nbNeighs = map();
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
        pair<Tile, int> neigh = neighbors[i];
        //if (count_if(neighbors.begin(), neighbors.end(), [](pair<Tile, int> other){return other.first == neigh.first;}) == 1) {
        if (nbNeighs[neigh.first] == 1) {
            pos = neigh.second;
            path.push_back(neigh.first);
            break;
        }
    }

    return PathFinder::unlooper(refPath, path, pos);
}

vector<Tile> PathFinder::straightener(vector<Tile> &refPath, vector<Tile> &path=vector(), int pos=0) {
    if (pos == this->path.size() + 4) {
        move(refPath.end() - 4, refPath.end(), back_inserter(path));
        refPath.clear();
        return path;
    }

    Tile current = path[pos];
    Tile next = path[pos + 4];
    Tile bridge;
    path.push_back(current);

    if (current.X() == next.X()) {
        bridge = Tile(next.X(), next.Y() - 1);
        if (current.Y() == next.Y() - 2 && this->map.exist(bridge.X(), bridge.Y())) {
            path.push_back(bridge);
            return this->straightener(refPath, path, pos + 4);
        }
        
        bridge = Tile(next.X(), next.Y() + 1);
        if (current.Y() == next.Y() + 2 && this->map.exist(bridge.X(), bridge.Y())) {
            path.push_back(bridge);
            return this->straightener(refPath, path, pos + 4);
        }
    }

    if (current.Y() == next.Y()) {
        bridge = Tile(next.X() - 1, next.Y());
        if (current.X() == next.X() - 2 && this->map.exist(bridge.X(), bridge.Y())) {
            path.push_back(bridge);
            return this->straightener(refPath, path, pos + 4);
        }
        
        bridge = Tile(next.X() + 1, next.Y());
        if (current.X() == next.X() + 2 && this->map.exist(bridge.X(), bridge.Y())) {
            path.push_back(bridge);
            return this->straightener(refPath, path, pos + 4);
        }
    }

    return this->straightener(refPath, path, pos + 1);
}
