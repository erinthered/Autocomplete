/******************************************************************
Title:            dictionary.h
Author:           Erin Williams
Date Created:     5/2/2017
Class:            Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:        Aarsh Vora
Purpose:          Assignment #3
Description:      Dictionary header file
*******************************************************************/
#ifndef _CS235_DICTIONARY_H_
#define _CS235_DICTIONARY_H_

#include <fstream>
#include <string>
#include <vector>
#include "trie.h"

namespace dictwilliams {

class Dictionary {

public:
    Dictionary() { }
    //Constructs a Dictionary based on a file stream to a text file
    Dictionary(std::ifstream& file) { load(file); }

    ~Dictionary() { }

    //Create a new Dictionary
    //If Dictionary contains data, clear first
    bool load(std::ifstream& file) { return trie_.load(file); }

    //Return true if word is in the dictionary, false otherwise
    bool isLegalWord(const std::string& word) const { return trie_.contains(word); }

    //Return the number of words stored in the dictionary
    inline int numWords() const { return trie_.numWords(); }

    //Returns a vector of n strings. Strings are legal words that require the
    //fewest additional characters. The words are organized by lenghth, then
    //alphabetically
    std::vector<std::string> suggest(const std::string& s, int n) const;

private:

    triewilliams::Trie trie_;
};


} //dictionarywilliams
#endif 
//_CS235_DICTIONARY_H_