/******************************************************************
Title:            trienode.cpp
Author:           Erin Williams
Date Created:     4/30/2017
Class:            Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:        Aarsh Vora
Purpose:          Assignment #3
Description:      TrieNode implementation file
*******************************************************************/

#include <map>
#include <string>
#include "trienode.h"

namespace triewilliams {

TrieNode::TrieNode() : wordEnd_(false) { 
	std::map<char, TrieNode*> map; 
	children_ = map; 
}

TrieNode* TrieNode::findChild(char letter) {
	//Get iterator to node containing letter
	std::map<char, TrieNode*>::iterator it = children_.find(letter);
	
	//If found in current case:
	if(it != children_.end()) {
		return it->second;
	}
	//If not found in current case, look for opposite case
	else {
		//If uppercase char, look for lowercase version
		if(isupper(letter)) { 
            std::map<char, TrieNode*>::iterator LCit = children_.find(tolower(letter));
            //Found lowercase version
            if(LCit != children_.end()) {
            	return LCit->second;
            }
            //Not found, letter not in map
            else {
            	return NULL;
            }
	    }
	    //If lowercase char, look for uppercase version
	    else {
            std::map<char, TrieNode*>::iterator UCit = children_.find(toupper(letter));
            //Found lowercase version
            if(UCit != children_.end()) {
            	return UCit->second;
            }
            //Not found, char not in map
            else {
            	return NULL;
            }
	    }
	}
}

} //triewilliams