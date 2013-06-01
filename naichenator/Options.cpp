//
//  Options.cpp
//  naichenator
//
//  Created by Ben La Monica on 6/1/13.
//  Copyright (c) 2013 Ben La Monica. All rights reserved.
//

#include "Options.h"
#include <getopt.h>

Options::Options(char * const argv[], int argc) {
    int flag;
    
    while ((flag = getopt(argc, argv, "h?m:x:p:gf:")) != -1) {
        switch (flag) {
            case 'm':
                isMinSet = true;
                min = atoi(optarg);
                break;
            case 'x':
                isMaxSet = true;
                max = atoi(optarg);
                break;
            case 'p':
                isProbSet = true;
                probability = atof(optarg);
                break;
            case 'g':
                generateFile = true;
                break;
            case 'f':
                filename = std::string(optarg);
                break;
            case '?':
            case 'h':
            default:
                displayHelp = true;
        }
    }
}

/*
 * Determines if the command line options are valid.
 * @returns false if they are not valid, and populates the err string with the error message.
 */
bool Options::isValid(std::string &err) const {
    if (displayHelp) {
        err = "";
        return false;
    }
    
    if (filename == "") {
        err = "You must specify a filename.";
        return false;
    }
    
    if (!isMaxSet) {
        err = "You must set a max value (like -x 1000)";
        return false;
    }
    
    if (!isMinSet) {
        err = "You must set a min value (like -m 0)";
        return false;
    }
    
    if (shouldGenerateFile() && !isProbSet) {
        err = "You must specify the probability (like -p 0.1) when generating a file";
        return false;
    }
    
    return true;

}