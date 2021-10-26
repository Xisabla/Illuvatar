#include "map/PathFinder.h"

using namespace std;
using namespace directionutils;
using namespace pathfinder;


DirectionalPath computeShortestPath(Map& map, Tile current, Tile& target, Direction initialD, unsigned int nbTile) {
    Path generated = {};
    Path explored = {};
    Path notExplored = {};
    Path unlooped = {};
    DirectionalPath straightened = {};

    Path tmp_result = aStarGenerator(map, generated, current, target, explored, notExplored);
    tmp_result = unlooper(map, tmp_result, unlooped);
    DirectionalPath result = straightener(map, tmp_result, straightened, initialD);
    result.resize(min(static_cast<unsigned int>(result.size()), nbTile));
    return result;
}

Path aStarGenerator(Map& map, Path& path, Tile current, Tile& target, Path& explored, Path& notExplored) {
    if (current == target) {
        explored.clear();
        notExplored.clear();
        return path;
    }

    explored.push_back(current);

    vector<Tile> notExploredNeighbours = {};

    for (Direction i = Direction::DIRECTION_FIRST; i < Direction::DIRECTION_LAST;
         i = Direction(static_cast<int>(i) + 1)) {
        // TODO: Point.getXY() --> int[] or std::pair<int, int>
        int nextX = current.X() + nextDirection.at(i).X();
        int nextY = current.Y() + nextDirection.at(i).Y();

        if (!map.exists(Point(nextX, nextY)) ||
            map.getThingOnTile(nextX, nextY) == ThingOnMap::Obstacle)
            continue;

        // todo : verify from here
        Tile neighbor = map.getTile(Point(nextX, nextY));
        if (find(explored.begin(), explored.end(), neighbor) != explored.end())
            continue;

        notExploredNeighbours.push_back(neighbor);
    }

    if (!notExploredNeighbours.empty()) {
        sort(
        notExploredNeighbours.begin(),
        notExploredNeighbours.end(),
        [current] (Tile& a, Tile& b) { return a.distanceTo(current) < b.distanceTo(current); });

        current = notExploredNeighbours[0];

        reverse(notExploredNeighbours.begin(), notExploredNeighbours.end());
        notExploredNeighbours.pop_back();

        move(notExploredNeighbours.begin(),
             notExploredNeighbours.end(),
             back_inserter(notExplored));
    } else if (!notExplored.empty()) {
        current = notExplored.back();
        notExplored.pop_back();
    } else {
        cout << "fucked up" << endl; //kill him ?
    }

    path.push_back(current);
    return pathfinder::aStarGenerator(map, path, current, target, explored, notExplored);
}

Path unlooper(Map& map, Path& refPath, Path& path, int pos) {
    if (pos == path.size()) {
        refPath.clear();
        return path;
    }

    vector<pair<Tile, int>> neighbors = {};
    std::map<Tile, int> nbNeighs = {};
    for (int i = pos; i < refPath.size(); ++i) {
        Tile tile = refPath[i];
        if (refPath[pos - 1].isNeighbours(tile)) {
            neighbors.push_back({ tile, i });

            if (nbNeighs.count(tile)) {
                neighbors[/*position de tile*/0].second++;
            }
            else {
                neighbors.push_back({ tile, 1 });
            }
            //add ajout au nbNeighs
        }
    }

    for (int i = neighbors.size() - 1; i >= 0; --i) {
        pair<Tile, int> neigh = neighbors[i];
        if (nbNeighs[neigh.first] == 1) {
            pos = neigh.second;
            path.push_back(neigh.first);
            break;
        }
    }

    return pathfinder::unlooper(map, refPath, path, pos);
}

DirectionalPath straightener(Map& map, Path& refPath, DirectionalPath& path, Direction initialD, int pos) {
    if (pos + 4 == path.size()) {//vérifier ordre
        for (Path::iterator iter = refPath.end() - 4; iter < refPath.end(); ++iter) {
            Tile future = map.getTile(Point((*iter).X(), (*iter).Y()));
            path.push_back({ future, computeDirection(path.back().first, *iter) });
        }
        refPath.clear();
        return path;
    }

    Tile current = refPath[pos];
    Tile next = refPath[pos + 4];
    Tile bridge = Tile(Point(0, 0));
    Direction dir = path.empty() ? initialD : computeDirection(path.back().first, current);
    path.push_back({ current, dir });

    if (checkBothBridges(map, path, current.X() == next.X(), current, next, false, current.Y() - next.Y()) ||
        checkBothBridges(map, path, current.Y() == next.Y(), current, next, true, current.X() - next.X())) {
        return pathfinder::straightener(map, refPath, path, initialD, pos + 5);
    }

    return pathfinder::straightener(map, refPath, path, initialD, pos + 1);
}

bool checkBothBridges(Map &map, DirectionalPath& path, bool alignTest, Tile current, Tile next, bool first, int deltaBridge) {
    return alignTest &&
           (checkBridge(map, path, Tile(next.X() - first, next.Y() - !first), deltaBridge == -2, current, next) ||
            checkBridge(map, path, Tile(next.X() + first, next.Y() + !first), deltaBridge == 2, current, next));
}

bool checkBridge(Map &map, DirectionalPath& path, Tile bridge, bool alignTest, Tile current, Tile next) {
    if (alignTest && map.exists(Point(bridge.X(), bridge.Y())) &&
        map.getThingOnTile(bridge.X(), bridge.Y()) == ThingOnMap::Obstacle) {
        path.push_back({ map.getTile(Point(bridge.X(), bridge.Y())), computeDirection(current, bridge) });
        path.push_back({ map.getTile(Point(next.X(), next.Y())), computeDirection(bridge, next) });
        return true;
    }

    return false;
}
