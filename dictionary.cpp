/******************************************************************
Title:            dictionary.cpp
Author:           Erin Williams
Date Created:     5/2/2017
Class:            Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:        Aarsh Vora
Purpose:          Assignment #3
Description:      Dictionary header file
*******************************************************************/

#include <string>
#include <utility>
#include <vector>
#include <queue>
#include "trie.h"
#include "trienode.h"
#include "dictionary.h"

namespace dictwilliams {

//Returns a vector of n strings. Strings are legal words that require the
//fewest additional characters. The words are organized by lenghth, then
//alphabetically
std::vector<std::string> Dictionary::suggest(const std::string& s, int n) const {

    //NEED TO WORRY ABOUT LOWERCASE/UPPERCASE
    //Vector to store suggested strings
    std::vector<std::string> vec;
    std::string prefix = s;
    //Get last node of s
    triewilliams::TrieNode* node = trie_.find(prefix);
    //Node/prefix string pair to store in queue
    std::pair<triewilliams::TrieNode*, std::string> p(node, prefix);
    //Queue to store nodes and prefix strings
    std::queue<std::pair<triewilliams::TrieNode*, std::string>> q;
    //Keeps track of number of words requested
    int count = 0;

    if(node == NULL) {
        return vec;
    }
    //If input string is a word, push to vector
    if(node->getWordMarker()) {
        vec.push_back(prefix);
        ++count;
    }
    
    //push first pair to queue
    q.push(p);

    while(!(q.empty())) {
        //Current node is node at front of queue
        triewilliams::TrieNode* current = q.front().first;

        //Prefix is second value in pair
        prefix = q.front().second;

        q.pop();

        std::map<char, triewilliams::TrieNode*>::iterator it;
        for(it = current->children().begin(); it != current->children().end(); ++it) {
            
            //Pair is now the node pointed to by iterator and prefix + the letter key
            p = std::make_pair(it->second, std::string(prefix + it->first));

            q.push(p);
             
            //Push string to vector if it is the end of a word
            //and requested number of words not yet reached
            if(it->second->getWordMarker() && count < n) {               
                vec.push_back(prefix + it->first);
                ++count;
            }
        }
    }

    return vec;
}

} //dictwilliams