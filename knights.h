#ifndef KNIGHTS_H
#define KNIGHTS_H

#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cstdint>

// Do not add any extra #includes without asking on the KEATS discussion forum

using std::pair;
using std::make_pair;
using std::vector;

typedef vector<pair<int,int> > Path;

/** Helper function: adds two pairs of ints */
pair<int,int> operator+(const pair<int,int> & a, const pair<int,int> & b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

// TODO - your code goes here

Path moves(const pair<int, int> & initialPosition) {
    Path reachablePositions = Path();

    reachablePositions.push_back(make_pair(initialPosition.first + 1, initialPosition.second + 2));
    reachablePositions.push_back(make_pair(initialPosition.first + 2, initialPosition.second + 1));
    reachablePositions.push_back(make_pair(initialPosition.first + 2, initialPosition.second - 1));
    reachablePositions.push_back(make_pair(initialPosition.first + 1, initialPosition.second - 2));
    reachablePositions.push_back(make_pair(initialPosition.first - 1, initialPosition.second - 2));
    reachablePositions.push_back(make_pair(initialPosition.first - 2, initialPosition.second - 1));
    reachablePositions.push_back(make_pair(initialPosition.first - 2, initialPosition.second + 1));
    reachablePositions.push_back(make_pair(initialPosition.first - 1, initialPosition.second + 2));

    return reachablePositions;
}


Path legal_moves(const int & size, const Path & path, const pair<int, int> & position) {
    Path legalPositions = Path();
    Path reachablePositions = moves(position);

    std::copy_if(reachablePositions.begin(), reachablePositions.end(), std::back_inserter(legalPositions), [size, path](const pair<int, int> & currentPosition) {

        bool isInside = currentPosition.first >= 0 && currentPosition.first < size && currentPosition.second >= 0 && currentPosition.second < size;
        bool isInPath = std::find(path.begin(), path.end(), currentPosition) != path.end();
        return isInside && !isInPath;
    });

    return legalPositions;
}


pair<Path, bool> first_tour(const int & size, const Path & path) {
    auto initialPosition = path.back();
    auto legalPositions = legal_moves(size, path, initialPosition);

    std::sort(legalPositions.begin(), legalPositions.end(), [size, path](pair<int, int> & x, pair<int, int> & y) {

        return legal_moves(size, path, x).size() < legal_moves(size, path, y).size();
    });

    for (int i = 0; i < legalPositions.size(); ++i) {
        Path copyOfPath(path);
        copyOfPath.push_back(legalPositions[i]);
        auto checker = first_tour(size, copyOfPath);
        if(checker.second == true) return make_pair(checker.first, true);
    }

    if (path.size() == size*size) return make_pair(path, true);
    else return make_pair(Path(), false);
};


// Do not edit below this line

#endif
