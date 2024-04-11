/* [Code Description]
Author: Fernando Tello
CPSC1070 - Spring 2024
Project 01: Strands */

#ifndef STRAND_H
#define STRAND_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// REQUIRED STRUCT - DO NOT REMOVE STRUCT MEMBERS
typedef struct strand
{
    char** words; // array of words found in strand
    char** letters; // 2D array of letters in strand
    int rows, cols; // dimensions of strand
    int numWords; // number of words in strand
    int wordLen; // length of words in strand
} strand_t;

// REQUIRED FUNCTIONS
char** readDictionary(FILE* dictFP, int* dictSize); // reads dictionary file and returns array of words
bool isValidCell(int row, int col, int rows, int cols); // checks if cell is within bounds
bool isWordInDictionary(const char* word, char** dictionary, int dictSize); // checks if word is in dictionary
void addWordToStrand(strand_t* strand, const char* word); // adds word to strand
void findWordsFromCell(int row, int col, char* path, int index, strand_t* strand, char** dictionary, int dictSize, int wordLen); // recursively function to find words from cell
void generateAndCheckWords(strand_t* strand, char** dictionary, int dictSize); // generates and checks words from each cell in strand

strand_t * create_strand(FILE * dataFP, FILE * dictFP); // creates and populates strand struct
bool is_word_in_strand(strand_t * strand, char * word); // checks if word is in strand
void print_strand_matrix(strand_t * strand); // prints strand matrix
void free_strand(strand_t * strand); // frees all memory allocated for strand

#endif
