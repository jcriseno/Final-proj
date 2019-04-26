//
// Created by Joseph Criseno on 2019-04-25.
//

#include "Range.h"

Range::Range() {
    currentLoop = 0;
    increment = 1;
}

Range::Range(int x) {
    currentLoop = 0;
    stop = x;
    increment = 1;
}

Range::Range(int x, int y) {
    currentLoop = 0;
    start = x;
    stop = y;
    increment = 1;
}

Range::Range(int x, int y, int z) {
    currentLoop = 0;
    start = x;
    stop = y;
    increment = z;
}

void Range::nextLoop() {
    currentLoop += increment;

}

bool Range::isFinished() {
    if (currentLoop == stop){
        return true;
    }
    else{
        return false;
    }
}

bool Range::thisLoop() {
    return currentLoop;
}
