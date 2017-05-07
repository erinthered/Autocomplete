/******************************************************************
Title:            trienode.cpp
Author:           Erin Williams
Date Created:     4/28/2017
Class:            Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:        Aarsh Vora
Purpose:          Assignment #3
Description:      TrieNode header file
*******************************************************************/

#ifndef _CS235_TRIENODE_H_
#define _CS235_TRIENODE_H_
#include <map>

namespace triewilliams {

class TrieNode {
public:
    TrieNode();
    ~TrieNode() { }

    //Getters and setters
    inline bool getWordMarker() { return wordEnd_; }
    inline void setWordMarker(bool isWordEnd) { wordEnd_ = isWordEnd; }

    //Returns an iterator to the letter if found, otherwise returns children_.end()
    //std::map<char,TrieNode*>::iterator findChild(char letter) { return children_.find(letter); }
    TrieNode* findChild(char letter);
    //Add a child node to the children_ map
    void addChild(char letter, TrieNode* child) { children_.insert(std::pair<char, TrieNode*> (letter, child)); }
    //Remove a child node containing key letter from the children_ map
    void removeChild(char letter) { children_.erase(letter); }
    //Map of next characters
    std::map<char, TrieNode*>& children() { return children_; }

private:
    //True if TrieNode marks the end of a word
    bool wordEnd_;
    //Map of key, value pairs of type <char, TrieNode*>
    std::map<char, TrieNode*> children_;
};

} //triewilliams

#endif
//_CS235_TRIENODE_H_