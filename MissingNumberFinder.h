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
#include <exception>
#include "Options.h"

class FileMissingException : public std::exception {
public:
    FileMissingException(const char *what_in) : _what(what_in) {
    }
    
    virtual ~FileMissingException() throw () { }
    
    virtual const char *what() {
        return _what;
    }
    
private:
    const char *_what;
};

class MissingNumberFinder {
public:
    MissingNumberFinder(const Options &options);
    virtual ~MissingNumberFinder();
    virtual bool findMissingNumber(uint32_t &num) throw(FileMissingException);
private:
    bool getNextNumber(std::fstream &file, uint32_t &i);
    void findNumbers() throw (FileMissingException);
    uint32_t minVal;
    uint32_t maxVal;
    std::string filename;
    uint8_t *tracking;
    bool parsed;
};

#endif /* defined(__naichenator__MissingNumberFinder__) */
