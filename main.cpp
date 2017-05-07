/******************************************************************
Title:            main.cpp
Author:           Erin Williams
Date Created:     4/30/2017
Class:            Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:        Aarsh Vora
Purpose:          Assignment #3
Description:      main file for Assignment 3 - Autocomplete
*******************************************************************/

#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>
#include "trie.h"
#include "trienode.h"
#include "dictionary.h"

using namespace triewilliams;
using namespace dictwilliams;

int main(int argc, char *argv[]) {
    //Only one command line arguement is accepted, or program ends
    if(argc != 2) {
        std::cout << "No command line argument, program ending.\n";
        return 0;
    }
    else {
        //Command line arguement is name of file
        std::ifstream file(argv[1]);

        if(!file) {
            std::cout << "Command line argument was not the name of a file. Program ending.\n";
            return 0;
        }

        Dictionary dict(file);
        
        std::string inputString;
        int numSuggestions;

        while(true) {
            std::cout << "Enter a string: ";
            std::cin >> inputString;

            std::cout << "Enter a number: ";
            std::cin >> numSuggestions;

            std::vector<std::string> vec = dict.suggest(inputString, numSuggestions);

            for(int i = 0; i < vec.size(); ++i) {
                std::cout << vec[i] << std::endl;
            }
        }
        file.close();
    }

	return 0;
}