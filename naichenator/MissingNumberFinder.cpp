//
//  MissingNumberFinder.cpp
//  naichenator
//
//  Created by Ben La Monica on 5/30/13.
//  Copyright (c) 2013 Ben La Monica. All rights reserved.
//

#include "MissingNumberFinder.h"

MissingNumberFinder::MissingNumberFinder(const Options &options) : minVal(options.getMinVal()), maxVal(options.getMaxVal()), filename(options.getFilename()) {
    tracking = new uint8_t[((maxVal - minVal) / 8)+1](); // () at the end initializes everything to 0
}

MissingNumberFinder::~MissingNumberFinder() {
    delete[] tracking;
}

/*
 * Reads one number from the file and converts it to an uint32_t
 * @returns, false if EOF
 */
bool MissingNumberFinder::getNextNumber(std::fstream &file, uint32_t &i) {
    if (file.eof()) {
        return false;
    }
    char buf[15];
    file.getline(buf, 15);
    if (strnlen(buf,15) == 0) {
        // if we have an empty line, get the next number until EOF
        return getNextNumber(file, i);
    } else {
        i = atoi(buf);
        return true;
    }
}

/*
 * Populates a bit-array to determine if a number was found.
 * @throws FileMissingException if file could not be opened.
 */
void MissingNumberFinder::findNumbers() throw(FileMissingException) {
    std::fstream file(filename.c_str(), std::ios_base::in);
    if (!file.is_open()) {
        throw FileMissingException("File not found.");
    }
    
    uint32_t num;
    while (getNextNumber(file, num)) {
        // calculate the index in the bit-array, minNum = index 0
        uint32_t index = (num - minVal);
        uint8_t *t = tracking+(index / 8);
        // bitwise-or the index to notate that it was found
        *t |= 1 << (index % 8);
    }
}

/*
 * Finds a missing number in the file. Each call will return the next number missing.
 * @returns true if a number was found
 * @throws FileMissingException if file was not able to be opened.
 */
bool MissingNumberFinder::findMissingNumber(uint32_t &num) throw(FileMissingException) {
    if(!parsed) {
        findNumbers();
    }
    
    for (int i = minVal; i < maxVal; i++) {
        uint32_t index = (i - minVal);
        uint8_t *t = tracking+(index / 8);
        // check the "index" bit to see if it is set, if the bit is 0, then we are missing that number
        if (((1 << (index % 8)) & *t) != (1 << (index % 8))) {
            num = index + minVal;
            *t |= 1 << (index % 8); // mark the number as being shown already
            return true;
        }
    }
    
    
    return false;
}