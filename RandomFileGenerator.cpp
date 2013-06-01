//
//  RandomFileGenerator.cpp
//  naichenator
//
//  Created by Ben La Monica on 5/29/13.
//  Copyright (c) 2013 Ben La Monica. All rights reserved.
//

#include "RandomFileGenerator.h"
#include <fstream>

RandomFileGenerator::RandomFileGenerator(const Options &options) :
    minVal(options.getMinVal()),
    maxVal(options.getMaxVal()),
    probSkip(options.getProbability())
{ }

RandomFileGenerator::~RandomFileGenerator()
{ }

void RandomFileGenerator::write(std::string filename) {
    SwapMap swapMem; // this will grow to be about n/4 in size
    
    std::fstream file; // file closes at end of the method automatically RAII.
    file.open(filename.c_str(),std::ios_base::out);
    
    /*Fisher and Yates Shuffle Algo
     To shuffle an array a of n elements (indicies 0..n-1)
     for i from n - 1 downto 1 do
     j = random integeger with 0 <= j <= i
     exchange a[j] and a[i]
     */
    
    uint32_t numSkipped = 0;
    std::cout << "minVal=" << minVal << " maxVal=" << maxVal << std::endl;
    std::cout << "Numbers Skipped: " << std::endl;
    for (uint32_t i = maxVal; i != minVal-1; --i ) {
        // generate a random number
        const uint32_t j = arc4random_uniform(i-minVal)+minVal;
        
        // see if we have something in the map that has already been swapped
        SwapMap::iterator iit = swapMem.find(i);
        SwapMap::iterator jit = swapMem.find(j);
        uint32_t numToWrite = 0;
        
        if (iit == swapMem.end()) {
            if (jit == swapMem.end()) {
                numToWrite = j; // nothing swapped in the map, so just "swap" a[i] and a[j]. a[i] == j and a[j] == i, and since i is decreasing, we can just write it to the file.
            } else {
                // found something in a[j], take that value
                numToWrite = jit->second; // we've already swapped at least once, so use the value that we've swapped to write
            }
            swapMem[j] = i; // a[j] = i ; save i for later
        } else if (jit == swapMem.end()) {
            numToWrite = j; // a[i] was found, but no a[j], so just put the value of j into a[i] (which is then written to diks)
            swapMem[j] = iit->second; // save a[j] = a[i]
            swapMem.erase(iit); // erase a[i] since we will never see it again (i is being decremented)
        } else {
            numToWrite = jit->second; // write a[j] to disk
            swapMem[j] = iit->second; // a[j] = a[i]
            swapMem.erase(iit); // erase a[i] since we'll never see it again
        }

        if (arc4random_uniform(1000) < (probSkip * 1000)) {
            std::cout << numToWrite << std::endl; // we're skipping this number
            numSkipped++;
        } else {
            file << numToWrite << std::endl;
        }
    }

    std::cout << "Skipped " << numSkipped << " out of " << (maxVal - minVal) << std::endl;
}
