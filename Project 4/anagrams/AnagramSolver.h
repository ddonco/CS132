/*
Dillon Donohue, CS 132, Winter 2023
Programming Assignment #4, 02/06/23

AnagramSolver is a class intended find anagram phrases/words given an input
word or phrase. An AnagramSolver object is instantiated by passing in a vector of
words to serve as a dictionary of all words to search when generating anagram words.
The user can specify the number of anagram words returned which will in turn
determine how many distinct anagrams can be found.
*/

#ifndef _AnagramSolver_H_
#define _AnagramSolver_H_

#include <string>
#include <vector>

#include "LetterInventory.h"

using namespace std;

class AnagramSolver {
public:
    /*
    The AnagramSolver constuctor takes in a vector of strings to serve as dictionary
    from which all anagram words will be selected.
    Parameters:
        dictionary  vector<string>  A dictionary of words used to generate anagram words.
    Returns:
        solver      AnagramSolver   An AnagramSolver object.
    */
    AnagramSolver(const vector<string> &dictionary);
    /*
    getWords is used to take in a user phrase, search the dictionary for all words contained
    within the phrase, and return these selected words as potential candidates that could be
    anagrams themselves or be used in combinations to make an anagram phrase.
    Parameters:
        phrase      string          A user phrase.
    Returns:
        words       vector<string>  A vector of words that are contained within the phrase,
                                    i.e. the letters of the phase can be used to make these words.
    */
    vector<string> getWords(const string &phrase);
    /*
    printHelper is a recursive helper function used to output anagram words based on the
    letters within the user entered phrase. The function will only output individual words that
    are anagrams or a list of words that make up an anagram. This function takes a max words
    parameter to specify how many words can be used to make up an anagram; 0 can be passed
    in to specify that there is no limit.
    Parameters:
        currentInventory    LetterInventory     A LetterInventory storing the letters of the
                                                input phrase.
        words               vector<string>      A vector of words that are contained within
                                                the currentInventory (input phrase).
        chosen              vector<string>      A vector of words holding the currently
                                                selected words from the 'words' vector
                                                as potential candidates for an anagram.
        maxWords            int                 The max number of words allowed to make up
                                                an anagram, 0 = no max.
    Returns:
        none
    */
    void printHelper(
        LetterInventory &currentInventory,
        vector<string> &words,
        vector<string> &chosen,
        int maxWords);
    /*
    This print function is used to output a series of all anagram word lists that can be found
    within the passed in phrase. print calls printHelper to recursively search all words
    contained within the phrase to find anagrams.
    Parameters:
        phrase      string      A phrase for which a series of anagrams will be found.
    Returns:
        none
    */
    void print(const string &phrase);
    /*
    This print function is used to output a series of all anagram word lists that can be found
    within the passed in phrase and which meet the specified max words requirement. print calls
    printHelper to recursively search all words contained within the phrase to find anagrams.
    Only anagram word lists which have up to max words will be output. If a zero is passed in
    for max words, no maximum is applied.
    Parameters:
        phrase      string      A phrase for which a series of anagrams will be found.
        maxWords    int         The maximum number of words which can make up the anagram
                                words list; 0 = no maximum.
    Returns:
        none
    */
    void print(const string &phrase, int max);

private:
    // dictionary holds the list of words passed in when instantiating an AnagramSolver object.
    vector<string> dictionary;
};

#endif