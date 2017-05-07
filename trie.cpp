/******************************************************************
Title:            trie.cpp
Author:           Erin Williams
Date Created:     4/27/2017
Class:            Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:        Aarsh Vora
Purpose:          Assignment #3
Description:      Trie implementation file
*******************************************************************/

#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include "trie.h"
#include "trienode.h"

namespace triewilliams {

//Construct new Trie from a file
Trie::Trie(std::ifstream& file) : root_(new TrieNode), wordCount_(0) {
    load(file);
}

Trie::~Trie() {
    clear();
    delete root_;
}

//Loads all words from a file into a Trie. 
//If the Trie is not empty, clears Trie first.
bool Trie::load(std::ifstream& file) {
    //clear Trie if it is not empty
    if(!(empty())) {
        clear();
    }

    std::string line;
    //check that file is open
    if(file) {
        while(std::getline(file, line)) {
            insert(line);
        }
        return true;
    }
    else {
        return false;
    } 
}

//Insert a new word in Trie
//Precondition: word is not an empty string
//Postcondition: Trie contains word
bool Trie::insert(const std::string& word) {
    TrieNode* current = root_;

    for(unsigned int i = 0; i < word.length(); ++i) {
        
        char currentChar = word[i];

        //get node with location of word[i] in children map of current node
        //if word[i] is not in children, returns NULL
        TrieNode* tmp = current->findChild(currentChar);

        //string[i] found in children of current node
        if(tmp != NULL) {
            current = tmp;
            if(i == word.length()-1 && current->getWordMarker()) {
                return false;  //duplicate
            }
        } 
        //string[i] not found in children
        else {  
                TrieNode* newChild = new TrieNode;
                //Add new node to children
                current->addChild(currentChar, newChild);
                current = newChild;
        }

        //End of word is reached  
        if(i == word.length()-1) {
            //last char of string, so set wordEnd to true 
            current->setWordMarker(true);
            ++wordCount_;
            //return true;
        }
    }
    return true; 
}

//Returns true if word is found in Trie, false otherwise
bool Trie::contains(const std::string& word) const {

   //Empty Trie does not contain word
   if(empty()) { 
        return false; 
    }

    TrieNode* current = root_;

    for(unsigned int i = 0; i < word.length(); ++i) {

        char currentChar = word[i];

        //get node with location of word[i] in children map of current node
        //if word[i] is not in children, returns NULL
        TrieNode* tmp = current->findChild(currentChar);
        
        //Current letter not found = word not found, so stop searching
        if(tmp == NULL) {
            return false;
        }
        else {
            current = tmp;
            //reached end of word
            if(current->getWordMarker() && i == word.length()-1) {
                return true;
            }
        }
    }
    return false;      //word found in Trie
    
}

bool Trie::remove(const std::string& word) {
    //empty trie, nothing to remove
    if(empty()) { 
        return false; 
    }
    else {
        if(!(word.empty())) {
            remove(root_, word, 0);
            --wordCount_;
            return true;
        }
        return false;
    }
}

bool Trie::remove(TrieNode* node, const std::string& word, unsigned int level) {
    if(node == NULL) {
        return false;
    }
    //base case, reached end of word
    if(level == word.length()) {
        //effectively remove word from Trie if word is also a prefix
        node->setWordMarker(false);
            
        if(noChildren(node)) {
            //okay to remove, leaf node
            return true;
        }
        //not okay to delete, node has children
        return false;
    }
    else {
        char currentChar = word[level];
        TrieNode* child = node->findChild(currentChar);

        if(remove(child, word, level+1)) {
            //Okay to delete, marked as true
            node->removeChild(currentChar);
            //return true if node is not the end of another word and has no children
            return(!(node->getWordMarker()) && noChildren(node));
        }
        return false;
    }
}

//Returns true if current node has no children, false if the current node has children
bool Trie::noChildren(TrieNode* node) const {
   return node->children().empty(); 
}

//Clear tree
//Postcondition: root_ is a node containing an empty map
void Trie::clear() {

    clear(root_);
    wordCount_ = 0;
}

//Delete the trie following post-order traversal
void Trie::clear(TrieNode* node){

    if(!(node->children().empty())) {
        std::map<char, TrieNode*>::iterator it = node->children().begin();
        for(; it != node->children().end(); ++it) {
            clear(it->second);
 
            delete it->second;
        }
        node->children().clear();
    }
}

//Returns number of nodes in Trie
int Trie::countNodes() const {
  return countNodes(root_->children());
}

int Trie::countNodes(std::map<char, TrieNode*> map) const {
  if (map.empty()) {
    return 0;
  }
  else {
    int count = 0;
    
    for (std::map<char, TrieNode*>::iterator it = map.begin(); it != map.end(); ++it) {
      ++count;
      count += countNodes(it->second->children());
    }
    return count;
  }
}


//Finds and returns last node in given string if string is found in Trie
//If not found, returns NULL
TrieNode* Trie::find(const std::string& word) const {
   //Empty Trie does not contain word
   if(empty()) { 
        return NULL; 
    }

    TrieNode* current = root_;

    for(unsigned int i = 0; i < word.length(); ++i) {

        //set current character to lowercase
        char currentChar = word[i];

        //get node with location of word[i] in children map of current node
        //if word[i] is not in children, returns NULL
        TrieNode* tmp = current->findChild(currentChar);
        
        if(tmp == NULL) {
            return NULL;
        }
        else {
            current = tmp;
            //reached end of word
            if(i == word.length()-1) {
                return current;
            }
        }
    }
    return current;       
}

} //triewilliams
