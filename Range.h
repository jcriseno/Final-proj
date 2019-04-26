//
// Created by Joseph Criseno on 2019-04-25.
//

#ifndef EXPRINTER_RANGE_H
#define EXPRINTER_RANGE_H


class Range {
public:
    Range();
    Range(int x);
    Range(int x, int y);
    Range(int x, int y, int z);

    void nextLoop();
    bool isFinished();
    bool thisLoop();


private:
    int start;
    int stop;
    int increment;
    int currentLoop;

};


#endif //EXPRINTER_RANGE_H
