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

class RandomFileGenerator {
public:
    typedef std::map<uint32_t,uint32_t> SwapMap;

    RandomFileGenerator(uint32_t min, uint32_t max, double probSkip);
    virtual ~RandomFileGenerator();
    void write(std::string filename);
    
private:
    uint32_t minVal;
    uint32_t maxVal;
    double probSkip;
    
};

#endif /* defined(__naichenator__RandomFileGenerator__) */
