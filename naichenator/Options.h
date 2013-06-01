//
//  Options.h
//  naichenator
//
//  Created by Ben La Monica on 6/1/13.
//  Copyright (c) 2013 Ben La Monica. All rights reserved.
//

#ifndef __naichenator__Options__
#define __naichenator__Options__

#include <iostream>

/*
 * Parses the options for the program and validates them.
 */
class Options {
public:
    Options(char * const argv[], int argc);
    virtual ~Options() { }
    bool isValid(std::string &err) const;
    double getProbability() const { return probability; }
    uint32_t getMinVal() const { return min; }
    uint32_t getMaxVal() const { return max; }
    const std::string &getFilename() const { return filename; }
    bool shouldGenerateFile() const { return generateFile; }
    bool shouldDisplayHelp() const { return displayHelp; }
private:
    bool generateFile = false;
    bool displayHelp = false;
    std::string filename;
    double probability = 0.0;
    bool isProbSet = false, isMinSet = false, isMaxSet = false;
    uint32_t min = 0, max = 10;
};

#endif /* defined(__naichenator__Options__) */
