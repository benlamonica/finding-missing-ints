//
//  MissingNumberFinder.cpp
//  naichenator
//
//  Created by Ben La Monica on 5/30/13.
//  Copyright (c) 2013 Ben La Monica. All rights reserved.
//

#include "MissingNumberFinder.h"

MissingNumberFinder::MissingNumberFinder(const std::string &filename, uint32_t min, uint32_t max) {
    minVal = min;
    maxVal = max;
    file.open(filename,std::ios_base::in);
    tracking = new uint8_t[((max - min) / 8)+1](); // () at the end initializes everything to 0
}

MissingNumberFinder::~MissingNumberFinder() {
    file.close();
    delete[] tracking;
}

bool MissingNumberFinder::getNextNumber(uint32_t &i) {
    if (file.eof()) {
        return false;
    }
    char buf[15];
    file.getline(buf, 15);
    i = atoi(buf);
    return true;
}

void MissingNumberFinder::findNumbers() {
    uint32_t num;
    while (getNextNumber(num)) {
        uint32_t index = (num - minVal);
        uint8_t *t = tracking+(index / 8);
        *t |= 1 << (index % 8);
    }
}

bool MissingNumberFinder::findMissingNumber(uint32_t &num) {
    
    if(!parsed) {
        findNumbers();
    }
    
    for (int i = minVal; i < maxVal; i++) {
        uint32_t index = (i - minVal);
        uint8_t *t = tracking+(index / 8);
        if (((1 << (index % 8)) & *t) != (1 << (index % 8))) {
            num = index + minVal;
            return true;
        }
    }
    
    
    return false;
}