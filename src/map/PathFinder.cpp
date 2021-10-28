#include "map/PathFinder.h"

using namespace std;
using namespace directionutils;
using namespace pathfinder;


DirectionalPath computeShortestPath(Map& map, Tile current, Tile& target, Direction initialD, unsigned int nbTile) {
    Path generated = {};
    Path explored = {};
    Path notExplored = {};
    Path tmp_result = aStarGenerator(map, generated, current, target, explored, notExplored);

    Path unlooped = {};
    tmp_result = unlooper(map, tmp_result, unlooped);

    DirectionalPath straightened = {};
    return straightenerAndCutter(map, tmp_result, straightened, initialD, nbTile);
}

Path aStarGenerator(Map& map, Path& path, Tile& current, Tile& target, Path& explored, Path& notExplored) {
    if (current == target) {
        explored.clear();
        notExplored.clear();
        return path;
    }

    explored.push_back(current);

    vector<Tile> notExploredNeighbours = {};
    for (Direction d = Direction::DIRECTION_FIRST; d < Direction::DIRECTION_LAST;
         d = Direction(static_cast<int>(d) + 1)) {
        Tile neighbor = map.jump(current, nextDirection.at(d));

        ThingOnMap content = map.getThingOnTile(neighbor.getPoint());
        if (content == ThingOnMap::Void ||
            content == ThingOnMap::Obstacle ||
            find(explored.begin(), explored.end(), neighbor) != explored.end())
            continue;

        notExploredNeighbours.push_back(neighbor);
    }

    Tile next = current;
    if (!notExploredNeighbours.empty()) {
        sort(
        notExploredNeighbours.begin(),
        notExploredNeighbours.end(),
        [&current] (Tile& a, Tile& b) { return a.distanceTo(current) > b.distanceTo(current); });

        next = notExploredNeighbours.back();
        notExploredNeighbours.pop_back();

        move(notExploredNeighbours.begin(),
             notExploredNeighbours.end(),
             back_inserter(notExplored));
    } else if (!notExplored.empty()) {
        next = notExplored.back();
        notExplored.pop_back();
    } else {
        cout << "no solution - suicide?" << endl;
    }

    path.push_back(next);
    return pathfinder::aStarGenerator(map, path, next, target, explored, notExplored);
}

Path unlooper(Map& map, Path& refPath, Path& path, int pos) {
    if (pos == refPath.size()) {
        refPath.clear();
        return path;
    }

    //liste le nombre d'occurence de chaque voisins avec leur position
    Tile current = refPath[pos - 1];
    vector<pair<Tile, int>> neighborsPos = {};
    std::map<Tile, int> neighborsOccurence = {};
    for (int i = pos; i < refPath.size(); ++i) {
        Tile tile = refPath[i];
        if (current.isNeighbours(tile)) {
            neighborsPos.push_back({ tile, i });

            if (neighborsOccurence.count(tile)) {
                neighborsOccurence.at(tile)++;
            }
            else {
                neighborsOccurence.insert({ tile, 1 });
            }
        }
    }

    //saute au dernier voisin croisé une seule fois (point de sortie du sac de noeud)
    for (int i = neighborsPos.size() - 1; i >= 0; --i) {
        pair<Tile, int> neighbor = neighborsPos[i];
        if (neighborsOccurence.at(neighbor.first) == 1) {
            pos = neighbor.second;
            path.push_back(neighbor.first);
            break;
        }
    }

    return pathfinder::unlooper(map, refPath, path, pos);
}

DirectionalPath straightenerAndCutter(Map& map, Path& refPath, DirectionalPath& path, Direction initialD, int nbTile, int pos) {
    if (path.size() == nbTile) return path;

    //si reste moins de 5 points, ne peut pas y avoir de pont : retourne le restant dans la limite du nombre de cases
    if (pos + 4 == refPath.size()) {
        int newSize = path.size() + 4;
        Path::iterator endIt = refPath.end() - (newSize > nbTile ? newSize - nbTile : 0);
        for (Path::iterator iter = refPath.end() - 4; iter < endIt; ++iter) {
            path.push_back({ *iter, computeDirection(path.back().first, *iter) });
        }
        refPath.clear();
        return path;
    }

    Tile current = refPath[pos];
    Tile next = refPath[pos + 4];
    Direction dir = path.empty() ? initialD : computeDirection(path.back().first, current);
    path.push_back({ current, dir });

    if (checkBothBridges(map, path, current.X() == next.X(), current, next, false, current.Y() - next.Y()) ||
        checkBothBridges(map, path, current.Y() == next.Y(), current, next, true, current.X() - next.X())) {
        return pathfinder::straightenerAndCutter(map, refPath, path, initialD, pos + 5);
    }

    return pathfinder::straightenerAndCutter(map, refPath, path, initialD, pos + 1);
}

bool checkBothBridges(Map &map, DirectionalPath& path, bool alignTest, Tile current, Tile next, bool first, int deltaBridge) {
    return alignTest &&
           (checkBridge(map, path, Point(next.X() - first, next.Y() - !first), deltaBridge == -2, current, next) ||
            checkBridge(map, path, Point(next.X() + first, next.Y() + !first), deltaBridge == 2, current, next));
}

bool checkBridge(Map &map, DirectionalPath& path, Point bridge, bool alignTest, Tile current, Tile next) {
    if (!alignTest) return false;

    ThingOnMap content = map.getThingOnTile(bridge);
    if (content == ThingOnMap::Void || content == ThingOnMap::Obstacle) return false;

    Tile bridgeTile = map.getTile(bridge);
    path.push_back({ bridgeTile, computeDirection(current, bridgeTile) });
    path.push_back({ next, computeDirection(bridgeTile, next) });
    return true;
}
