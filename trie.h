/******************************************************************
Title:            trie.h
Author:           Erin Williams
Date Created:     4/27/2017
Class:            Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:        Aarsh Vora
Purpose:          Assignment #3
Description:      Trie header file
*******************************************************************/

#ifndef _CS235_TRIE_H_
#define _CS235_TRIE_H_
#include <map>
#include <fstream>
#include <iostream>
#include <string>

#include "trienode.h"

namespace triewilliams {

class Trie {
public:
    Trie() : wordCount_(0) { root_ = new TrieNode; }

    //Constructor creates Trie object from an open filestream
    //Postcondition: Trie contains words from file
    Trie(std::ifstream& file);

    ~Trie();

    //Loads a Trie from a file. Clears Trie if it is already loaded before function call.
    bool load(std::ifstream& file);
    //Insert a word in Trie
    bool insert(const std::string& word);
    //Locate a word in the given trie, return true if found, false otherwise
    bool contains(const std::string& word) const;
    //If word is in the Trie (and is a word), remove word and return true, otherwise return false
    bool remove(const std::string& word);
    //Clear all nodes of Trie except root and set word count to zero
    void clear();

    //Return number of words in Trie
    inline int numWords() const { return wordCount_; }
    //Returns number of existing TrieNodes in Trie (excluding root)
    int countNodes() const;
    //Returns true if Trie is empty, false othewise
    inline bool empty() const { return wordCount_ == 0; }

    //Finds a specific node containing the specified string
    //Returns NULL if the node is not found
    TrieNode* find(const std::string& word) const;

private:
    TrieNode* root_; //"Dummy" node, root of Trie
    int wordCount_;  //Number of words in Trie

    //Recursive helper function for remove
    bool remove(TrieNode* node, const std::string& word, unsigned int level);
    //Returns true if node has no children, false otherwise
    bool noChildren(TrieNode* node) const;
    //Recursive helper function for clear
    //void clear(std::map<char, TrieNode*> map);
    void clear(TrieNode* node);
    //Recursive helper function for countNodes
    int countNodes(std::map<char, TrieNode*> children) const;
};

} //triewilliams
#endif 
//_CS235_TRIE_H_