//
//  MissingNumberFinder.h
//  naichenator
//
//  Created by Ben La Monica on 5/30/13.
//  Copyright (c) 2013 Ben La Monica. All rights reserved.
//

#ifndef __naichenator__MissingNumberFinder__
#define __naichenator__MissingNumberFinder__

#include <iostream>
#include <fstream>

class MissingNumberFinder {
public:
    MissingNumberFinder(const std::string &filename, uint32_t min, uint32_t max);
    virtual ~MissingNumberFinder();
    virtual bool findMissingNumber(uint32_t &num);
private:
    bool getNextNumber(uint32_t &i);
    void findNumbers();
    uint32_t minVal;
    uint32_t maxVal;
    std::fstream file;
    uint8_t *tracking;
    bool parsed;
};

#endif /* defined(__naichenator__MissingNumberFinder__) */
