**************************************************************************************
Title:              README.txt
Author:             Erin Williams
Date Created:       5/4/2017
Class:              Spring 2017, CSCI 235-04, Mon & Wed 7:00pm-8:15pm
Professor:          Marsh Vora
Purpose:            Assignment #3
Description:        Readme file for third project
***************************************************************************************

The makefile for this project compiles an executable, Project3, using the g++ compiler,
from the included .cpp files for the project. The make clean command is available.

All parts of this project are completed, nothing is incomplete.

The project is a Dictionary that takes in an integer n and a string that may be a word, a prefix
to a word, or neither, and returns a list of n suggested words from the Dictionary, sorted by
word length, then alphabetically.

The underlying data structure for this project is a Trie, which stores strings of characters. 
Each Trie is a tree consisting of a “dummy” head pointer, which is the first Trie Node in a 
series of Trie Nodes, which each contain two data members: a boolean and a map containing 
key value pairs of a single character and a pointer to a Trie Node. The boolean is set
to true if the Trie Node is the final character of a word. The map determines the next
level of the tree. The Trie is a space efficient way of searching words, as any shared
prefix of two or more words with not need to duplicate storage for any shared characters
in the prefix.

The TrieNode class contains one notable function, findChild, which takes in a character
and returns a pointer to the TrieNode which has the character as the key in the map stored
in the “parent” TrieNode, or returns NULL if the character is not a key in the parent node’s
map. This function is designed to be case-insensitive when searching for a character key.

Each Trie contains a head pointer and an integer value as data members. The head pointer
points at the head node of the tree, which contains a map, but has no key, and the integer
value stores the number of words current stored in the Trie, for convenient access.

Notable functions/algorithms in Trie include: load, insert, contains, remove, clear,
countNodes, and find, as well as their associated overloaded helper functions in the
functions where recursion is used. The default constructor creates a single head node
containing an empty map. The second constructor takes in a filestream as input and calls
load to load the file. The destructor calls clear to clear the tree, then deletes the head.

Load takes an open file input stream as input. If the Trie is not empty, it is first cleared,
then the file is read in line by line until the end of the input file is reached. The file
input is specified as a file of single word strings followed by a newline character, so the
getline function was used to get input. The function then calls insert to insert the new word
into the Trie.

The insert function takes in a string and iterates through the string letter by letter. If the
current letter is not found, it is inserted as the key to a new entry in the map of the current
Trie Node. If it is found, if it his not the end of the word, the search moves to the next letter.
If it is found and the current node is already marked as the end of a word, the word is a duplicate and is not inserted and the function returns false. If the end of the word is reached and the word
was not a duplicate, the end of word marker is set to true and the word count int is incremented.

The contains function takes a string as input and returns true is the word is found in the Trie,
and false if it is not found. If the Trie is empty, the string is not found and the function returns
false. Otherwise the function iterates through the given string. If the current character in the word
is ever not matched to the key of the current node, the given string is not found and the function
returns false. Otherwise the function matches characters to keys until the end of the string is
reached, then returns true.

The remove function actually removes nodes from the Trie that are not shared prefixes with another
word. I considered lazy delete for this function, but decided to actually delete nodes from the Trie
to save space. Considering that this project is a dictionary, remove will probably almost never be
called, so I didn’t think it was a big deal to go either way. The actual function is recursive and
consists of two functions with the name remove. The public function returns false if the Trie is 
empty when the function is called, otherwise if the word is not an empty string, it calls remove 
on the root. The essential algorithm of the overloaded helper remove function is that each letter
of the word is iterated through using the current level of the tree. When nodes are found that are 
not shared prefixes of another word (i.e. they contain empty maps), the word end marker is set to
false and the node is marked okay to delete, otherwise if the node is a shared prefix node, it is
marked not okay to delete. The recursion then unwinds and deletes the nodes marked as okay to delete
and does not delete the rest. TL;DR: postorder recursion to non-lazy delete unshared nodes.

The clear function is also a recursive function. It calls the public clear on the root of the Trie
and sets the number of words to zero. The overloaded helper clear function iterates through the 
current node’s map, calling clear on each section of the map, then postorder deleting the individual
nodes and finally clearing the map.

The countNodes function is also a recursive function. The public function calls the private helper
function countNodes on the root node’s map. The helper countNodes function then returns 0 nodes if
map is empty, otherwise iterates through the map then recursively increments the total count.

The find function takes a string as input and returns the node with the final character of the word
as a key, or returns NULL if the word is not found in the Trie. It iterates through the characters of 
the word, matching them to the node with the character as the key until the end of the word is
reached. If all nodes are matched to characters, the node containing the final character of the word
is returned, otherwise the function returns NULL.


The Dictionary class has a Trie as its single private data member. Most of the functions in the
dictionary class just call their Trie counterparts on the private Trie data object. The notable
function in the Dictionary class is suggest.

The suggest function takes in a string s and an integer n and returns n words from the dictionary
that contain s as a prefix, sorted first by smallest number of characters and then alphabetically.
The function uses level order traversal to store pairs of strings and nodes in a queue, which are
then popped off the front of the queue. The strings stored in the pairs are the prefix of that
“level” of the Trie. When the end of a word marker is reached, the prefix of the pair is
concatenated with the character key of the pair’s node and the resulting word is pushed to a vector.
When n words have been pushed to the vector, the vector is returned.

The main class takes in the name of a text file as an argument. The program checks that only one
argument was given, then opens the file. If the file did not open properly, an error message outputs
to the console and the program terminates. The program then creates a Dictionary object and loads it
with the words from the given file. The program then continually prompts for the user to enter a
string s and an integer n and calls the suggest function on the Dictionary object using the inputs.
A list of n words is output to the screen and the user is prompted for another string and number.

The program will never terminate on it’s own. That was my interpretation of the directions for the 
project.




