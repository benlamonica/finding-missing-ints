//
//  main.cpp
//  naichenator
//
//  Created by Ben La Monica on 5/29/13.
//  Copyright (c) 2013 Ben La Monica. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "Options.h"
#include "RandomFileGenerator.h"
#include "MissingNumberFinder.h"
#include <exception>

using std::cout;

void usage(const std::string &errorMessage) {
    cout << errorMessage << std::endl;
    cout << "Usage: naichenator [-g -p <probability>] -m <minNum> -x <maxNum> -f <filename>\n";
    cout << "  -g : generate random number file\n";
    cout << "  -p : probability that we will not write the number to the file\n";
    cout << "  -m : minimum number in the range\n";
    cout << "  -x : maximum number in the range\n";
    cout << "  -f : filename for numbers (either read or write)\n\n";
}

int main(int argc, char * const argv[])
{
    try {
        Options options(argv,argc);
        std::string error;
        if (!options.isValid(error)) {
            usage(error.c_str());
            return -1;
        }

        if (options.shouldGenerateFile()) {
            RandomFileGenerator generator(options);
            generator.write(options.getFilename());
        } else {
            MissingNumberFinder finder(options);
            uint32_t num = 0;
            if (finder.findMissingNumber(num)) {
                cout << "Missing number: " << num << std::endl;
            } else {
                cout << "No missing numbers found." << std::endl;
            }
        }
    } catch (FileMissingException &e) {
        usage("Error: " + std::string(e.what()));
        return -1;
    } catch (std::exception &e) {
        usage("Unknown error.");
    }
    return 0;
}
