#ifndef TRADE_H
#define TRADE_H

#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cstdint>

// Do not add any extra #includes without asking on the KEATS discussion forum

// TODO your code goes here:

template <typename T>
int bestProfit(T begin, T end) {
    int bestProfit = std::accumulate(begin, end, 0, [begin](int difference, int & price) {
               if ((price - * begin) > difference)
                   difference = price - * begin;
               if (price < * begin) * begin = price;
               return difference;
    });
    
    return bestProfit;
}





// Don't write any code below this line

#endif
