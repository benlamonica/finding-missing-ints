//
//  RandomFileGenerator.cpp
//  naichenator
//
//  Created by Ben La Monica on 5/29/13.
//  Copyright (c) 2013 Ben La Monica. All rights reserved.
//

#include "RandomFileGenerator.h"
#include <fstream>

RandomFileGenerator::RandomFileGenerator(uint32_t min, uint32_t max, double probSkip) {
    this->minVal = min;
    this->maxVal = max;
    this->probSkip = probSkip;
}

RandomFileGenerator::~RandomFileGenerator() {
    
}

void RandomFileGenerator::write(std::string filename) {
    SwapMap swapMem;
    std::fstream file;
    file.open(filename,std::ios_base::out);
    
    /*Fisher and Yates Shuffle Algo
     To shuffle an array a of n elements (indicies 0..n-1)
     for i from n - 1 downto 1 do
     j = random integeger with 0 <= j <= i
     exchange a[j] and a[i]
     */
    
    uint64_t largest_map_size = 0;
    uint32_t numSkipped = 0;
    std::cout << "minVal=" << minVal << " maxVal=" << maxVal << std::endl;
    std::cout << "Numbers Skipped: " << std::endl;
    for (uint32_t i = maxVal; i != minVal-1; --i ) {
        largest_map_size = swapMem.size() > largest_map_size ? swapMem.size() : largest_map_size;
        const uint32_t j = arc4random_uniform(i-minVal)+minVal;
        SwapMap::iterator iit = swapMem.find(i);
        SwapMap::iterator jit = swapMem.find(j);
        uint32_t numToWrite = 0;
        if (iit == swapMem.end()) {
            if (jit == swapMem.end()) {
                numToWrite = j;
            } else {
                numToWrite = jit->second;
            }
            swapMem[j] = i;
        } else if (jit == swapMem.end()) {
            numToWrite = j;
            swapMem[j] = iit->second;
            swapMem.erase(iit);
        } else {
            numToWrite = jit->second;
            swapMem[j] = iit->second;
            swapMem.erase(iit);
        }

        if (arc4random_uniform(1000) < (probSkip * 1000)) {
            std::cout << numToWrite << std::endl;
            numSkipped++;
        } else {
            file << numToWrite << std::endl;
        }
    }

    file.close();
    
    std::cout << "Skipped " << numSkipped << " out of " << (maxVal - minVal) << std::endl;
    std::cout << "Largest Map Size: " << largest_map_size << std::endl;
    std::cout << "Map Size Now: " << swapMem.size() << std::endl;
}
