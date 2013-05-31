//
//  main.cpp
//  naichenator
//
//  Created by Ben La Monica on 5/29/13.
//  Copyright (c) 2013 Ben La Monica. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "RandomFileGenerator.h"
#include "MissingNumberFinder.h"

using std::cout;

void usage(const std::string &errorMessage) {
    cout << errorMessage << std::endl;
    cout << "Usage: naichenator [-g -p <probability>] -m <minNum> -x <maxNum> -f <filename>" << std::endl << std::endl;
}

int main(int argc, char * const argv[])
{
    bool generateFile = false;
    std::string filename;
    double probability = 1.0;
    uint32_t min = 0, max = 10;
    int flag;
    
    while ((flag = getopt(argc, argv, "m:x:p:gf:")) != -1) {
        switch (flag) {
            case 'm':
                min = atoi(optarg);
                break;
            case 'x':
                max = atoi(optarg);
                break;
            case 'p':
                probability = atof(optarg);
                break;
            case 'g':
                generateFile = true;
                break;
            case 'f':
                filename = std::string(optarg);
                break;
            case '?':
            default:
                usage("");
        }
    }
    argc -= optind;
    argv += optind;

    if (filename == "") {
        usage("You must specify a filename.");
        return -1;
    }
    
    if (generateFile) {
        RandomFileGenerator r(min,max,probability);
        r.write(filename);
    } else {
        MissingNumberFinder f(filename,min,max);
        uint32_t num = 0;
        if (f.findMissingNumber(num)) {
            cout << "Missing number: " << num << std::endl;
        } else {
            cout << "No missing numbers found." << std::endl;
        }
    }
    return 0;
}
