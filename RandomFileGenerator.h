//
//  RandomFileGenerator.h
//  naichenator
//
//  Created by Ben La Monica on 5/29/13.
//  Copyright (c) 2013 Ben La Monica. All rights reserved.
//

#ifndef __naichenator__RandomFileGenerator__
#define __naichenator__RandomFileGenerator__

#include <iostream>
#include <map>
#include "Options.h"

/*
 * Generates a file with randomly shuffled integegers in a range. 
 * Will also randomly drop selected numbers based on a probability supplied.
 */
class RandomFileGenerator {
public:
    typedef std::map<uint32_t,uint32_t> SwapMap;

    RandomFileGenerator(const Options &options);
    virtual ~RandomFileGenerator();
    void write(std::string filename);
    
private:
    uint32_t minVal;
    uint32_t maxVal;
    double probSkip;
    
};

#endif /* defined(__naichenator__RandomFileGenerator__) */
