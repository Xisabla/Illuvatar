#include "map/PathFinder.h"

using namespace std;
using namespace directionutils;
using namespace pathfinder;


DirectionalPath pathfinder::computeShortestPath(Map& map, Point current, Point& target, Direction initialD, unsigned int nbTile) {
    if (!map.exists(current) || !map.exists(target)) {
        cout << "error at pathfinder::computeShortestPath(...," << current << ", " << target << ", ...);" << endl;
        exit(1);
    }

    Path generated = {};
    Path explored = {};
    Path notExplored = {};
    Path tmp_result = aStarGenerator(map, generated, current, target, explored, notExplored);

    Path unlooped = {};
    tmp_result = unlooper(map, tmp_result, unlooped);

    DirectionalPath straightened = {};
    return straightenerAndCutter(map, tmp_result, straightened, computeDirection(current, unlooped[0]), nbTile);
}

Path pathfinder::aStarGenerator(Map& map, Path& path, Point& current, Point& target, Path& explored, Path& notExplored) {
    if (current == target) {
        explored.clear();
        notExplored.clear();
        return path;
    }

    explored.push_back(current);

    vector<Point> notExploredNeighbours = {};
    for (Direction d = Direction::DIRECTION_FIRST; d <= Direction::DIRECTION_LAST; d = Direction(static_cast<int>(d) + 1)) {
        Point neighbor = map.project(current, nextDirection.at(d));
        ThingAtPoint content = map.getThingAtPoint(neighbor);

        if (content == ThingAtPoint::Void || content == ThingAtPoint::Obstacle ||
            find(explored.begin(), explored.end(), neighbor) != explored.end())
            continue;

        notExploredNeighbours.push_back(neighbor);
    }

    Point next = current;
    if (!notExploredNeighbours.empty()) {
        sort(
        notExploredNeighbours.begin(),
        notExploredNeighbours.end(),
        [&target] (Point& a, Point& b) { return target.distanceTo(a) > target.distanceTo(b); });

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
        explored.clear();
        notExplored.clear();
        return path;
    }

    path.push_back(next);
    return pathfinder::aStarGenerator(map, path, next, target, explored, notExplored);
}

Path pathfinder::unlooper(Map& map, Path& refPath, Path& path, unsigned int pos) {
    Point current = refPath[pos - 1];
    path.push_back(current);

    if (pos == refPath.size()) {
        refPath.clear();
        return path;
    }

    //liste le nombre d'occurence de chaque voisins avec leur position
    vector<pair<Point, int>> neighborsPos = {};
    std::map<Point, int> neighborsOccurence = {};
    for (int i = pos; i < refPath.size(); ++i) {
        Point point = refPath[i];
        if (map.areNeighbours(current, point)) {
            neighborsPos.push_back({ point, i });

            if (neighborsOccurence.count(point)) {
                neighborsOccurence.at(point)++;
            }
            else {
                neighborsOccurence.insert({ point, 1 });
            }
        }
    }

    //saute au dernier voisin croisé une seule fois (point de sortie du sac de noeud)
    for (int i = neighborsPos.size() - 1; i >= 0; --i) {
        pair<Point, int> neighbor = neighborsPos[i];
        if (neighborsOccurence.at(neighbor.first) == 1) {
            pos = neighbor.second;
            break;
        }
    }

    return pathfinder::unlooper(map, refPath, path, pos + 1);
}

DirectionalPath pathfinder::straightenerAndCutter(Map& map, Path& refPath, DirectionalPath& path, Direction initialD, unsigned int nbTile, unsigned int pos) {
    if (path.size() == nbTile) {
        refPath.clear();
        return path;
    }

    //si reste moins de 5 points, ne peut pas y avoir de pont : retourne le restant dans la limite du nombre de cases
    int deltaSize = refPath.size() - pos;
    if (deltaSize <= 4) {
        int newSize = path.size() + deltaSize;
        Path::iterator endIt = refPath.end() - (newSize > nbTile ? newSize - nbTile : 0);
        for (Path::iterator iter = refPath.end() - deltaSize; iter < endIt; ++iter) {
            path.push_back({ *iter, path.empty() ? initialD : computeDirection(path.back().first, *iter) });
        }
        refPath.clear();
        return path;
    }

    Point current = refPath[pos];
    Point next = refPath[pos + 4];
    Point last = path.empty() ? map.computeLastPosition(current, initialD) : path.back().first;
    Direction dir = computeDirection(last, current);
    path.push_back({ current, dir });

    if (checkBothBridges(map, path, current.X() == next.X(), current, next, false, current.Y() - next.Y()) ||
        checkBothBridges(map, path, current.Y() == next.Y(), current, next, true, current.X() - next.X())) {
        return pathfinder::straightenerAndCutter(map, refPath, path, initialD, nbTile, pos + 5);
    }

    return pathfinder::straightenerAndCutter(map, refPath, path, initialD, nbTile, pos + 1);
}

bool pathfinder::checkBothBridges(Map &map, DirectionalPath& path, bool alignTest, Point current, Point next, bool first, int deltaBridge) {
    return alignTest &&
           (checkBridge(map, path, Point(next.X() - first, next.Y() - !first), deltaBridge == -2, current, next) ||
            checkBridge(map, path, Point(next.X() + first, next.Y() + !first), deltaBridge == 2, current, next));
}

bool pathfinder::checkBridge(Map &map, DirectionalPath& path, Point bridge, bool alignTest, Point current, Point next) {
    if (!alignTest) return false;

    ThingAtPoint content = map.getThingAtPoint(bridge);
    if (content == ThingAtPoint::Void || content == ThingAtPoint::Obstacle) return false;

    path.push_back({ bridge, computeDirection(current, bridge) });
    path.push_back({ next, computeDirection(bridge, next) });
    return true;
}
