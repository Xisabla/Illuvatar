#include "map/PathFinder.h"

using namespace std;
using namespace directionutils;
using namespace superTypes;
using namespace pathfinder;


DirectionalPath
pathfinder::shortest(Map& map, Point current, Point& target, unsigned int maxDistance) {
    // TODO: Throw exception
    if (!map.exists(current) || !map.exists(target)) {
        cout << "error at pathfinder::shortest(...," << current << ", " << target << ", ...);"
             << endl;
        exit(1);
    }

    Path generated = {};
    Path explored = {};
    Path unexplored = {};
    Path res = AStar(map, generated, current, target, explored, unexplored);

    Path unlooped = {};
    res = unlooper(map, res, unlooped);

    DirectionalPath straightened = {};
    return straightenerAndCutter(
    map, res, straightened, computeDirection(current, unlooped[0]), maxDistance);
}

Path pathfinder::AStar(Map& map,
                       Path& path,
                       Point& current,
                       Point& target,
                       Path& explored,
                       Path& unexplored) {
    if (current == target) {
        explored.clear();
        unexplored.clear();

        return path;
    }

    explored.push_back(current);

    vector<Point> neighbours = {};

    for (Direction d = Direction::DIRECTION_FIRST; d <= Direction::DIRECTION_LAST;
         d = Direction(static_cast<int>(d) + 1)) {
        Point neighbor = Map::project(current, nextDirection.at(d));
        ThingAtPoint content = map.getThingAtPoint(neighbor);

        if (content == ThingAtPoint::Void || content == ThingAtPoint::Obstacle || //ou si character et que ce character est master ?
            find(explored.begin(), explored.end(), neighbor) != explored.end())
            continue;

        neighbours.push_back(neighbor);
    }

    Point next = current;

    if (!neighbours.empty()) {
        sort(neighbours.begin(), neighbours.end(), [&target](Point& a, Point& b) {
            return target.distanceTo(a) > target.distanceTo(b);
        });

        next = neighbours.back();
        neighbours.pop_back();

        move(neighbours.begin(), neighbours.end(), back_inserter(unexplored));
    } else if (!unexplored.empty()) {
        next = unexplored.back();
        unexplored.pop_back();
    } else {
        cout << "no solution - suicide?" << endl;

        explored.clear();
        unexplored.clear();

        return path;
    }

    path.push_back(next);

    return pathfinder::AStar(map, path, next, target, explored, unexplored);
}

Path pathfinder::unlooper(Map& map, Path& refPath, Path& path, unsigned int pos) {
    Point current = refPath[pos - 1];
    path.push_back(current);

    // Recursion endpoint
    if (pos == refPath.size()) {
        refPath.clear();
        return path;
    }

    // List neighbours occurrences in Path
    vector<pair<Point, int>> neighbours = {};
    std::map<Point, int> occurrences = {};
    for (unsigned int i = pos; i < refPath.size(); ++i) {
        Point point = refPath[i];
        if (Map::areNeighbours(current, point)) {
            neighbours.emplace_back(point, i);

            if (occurrences.count(point)) {
                occurrences.at(point)++;
            } else {
                occurrences.insert({ point, 1 });
            }
        }
    }

    if (!neighbours.empty()) {
        // Figure out pos
        for (unsigned int i = neighbours.size() - 1; i >= 0; --i) {
            pair<Point, int> neighbor = neighbours[i];
            if (occurrences.at(neighbor.first) == 1) {
                pos = neighbor.second;
                break;
            }
        }
    }

    return pathfinder::unlooper(map, refPath, path, pos + 1);
}

DirectionalPath pathfinder::straightenerAndCutter(Map& map,
                                                  Path& ref,
                                                  DirectionalPath& path,
                                                  Direction direction,
                                                  unsigned int maxDistance,
                                                  unsigned int pos) {
    // Recursion endpoint
    if (path.size() == maxDistance) {
        cout << "easy end" << endl;
        ref.clear();
        return path;
    }

    unsigned int deltaSize = static_cast<unsigned int>(ref.size()) - pos;

    // Can't have bridges if there are less than 5 points
    if (deltaSize < 5) {
        cout << "buggy end" << endl;
        cout << ref.size() << " - " << pos << " = " << deltaSize << endl;
        unsigned int size = static_cast<unsigned int>(path.size()) + deltaSize;
        cout << "add " << ref.size() - (size > maxDistance ? size - maxDistance : 0) << " elems to path of " << path.size() << " elems (max is " << size << ")" << endl;
        auto endIt = ref.end() - (size > maxDistance ? size - maxDistance : 0);

        for (auto iter = ref.end() - deltaSize; iter < endIt; ++iter) {
            path.push_back(
            { *iter, path.empty() ? direction : computeDirection(path.back().first, *iter) });
        }

        ref.clear();

        return path;
    }

    Point current = ref[pos];
    Point next = ref[pos + 4];
    Point last = path.empty() ? map.computeLastPosition(current, direction) : path.back().first;
    Direction dir = computeDirection(last, current);
    path.push_back({ current, dir });

    if (checkAllBridges(map, path, current, next))
        return pathfinder::straightenerAndCutter(map, ref, path, direction, maxDistance, pos + 5);

    return pathfinder::straightenerAndCutter(map, ref, path, direction, maxDistance, pos + 1);
}

bool pathfinder::checkAllBridges(Map& map, DirectionalPath& path, Point current, Point next) {
    bool xAxis = checkBothBridges(map, path, current.X() == next.X(), current, next, false, current.Y() - next.Y());
    bool yAxis = checkBothBridges(map, path, current.Y() == next.Y(), current, next, true, current.X() - next.X());
    return xAxis || yAxis;
}

bool pathfinder::checkBothBridges(Map& map,
                                  DirectionalPath& path,
                                  bool alignTest,
                                  Point current,
                                  Point next,
                                  bool first,
                                  int deltaBridge) {
    if (!alignTest) return false;

    bool firstCheck = checkBridge(map, path, Point(next.X() - first, next.Y() - !first), deltaBridge == -2, current, next);
    bool secondCheck = checkBridge(map, path, Point(next.X() + first, next.Y() + !first), deltaBridge == 2, current, next);
    return firstCheck || secondCheck;
}

bool pathfinder::checkBridge(Map& map,
                             DirectionalPath& path,
                             Point bridge,
                             bool alignTest,
                             Point current,
                             Point next) {
    if (!alignTest) return false;

    ThingAtPoint content = map.getThingAtPoint(bridge);
    if (content == ThingAtPoint::Void || content == ThingAtPoint::Obstacle) return false; //ou si character et que ce character est master ?

    path.push_back({ bridge, computeDirection(current, bridge) });
    path.push_back({ next, computeDirection(bridge, next) });
    return true;
}
