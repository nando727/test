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
    char** words;
    char** letters;
    int rows, cols;
    int numWords;
    int wordLen;
} strand_t;

// REQUIRED FUNCTIONS
char** readDictionary(FILE* dictFP, int* dictSize);
bool isValidCell(int row, int col, int rows, int cols);
bool isWordInDictionary(const char* word, char** dictionary, int dictSize);
void addWordToStrand(strand_t* strand, const char* word);
void findWordsFromCell(int row, int col, char* path, int index, strand_t* strand, char** dictionary, int dictSize, int wordLen);
void generateAndCheckWords(strand_t* strand, char** dictionary, int dictSize);

strand_t * create_strand(FILE * dataFP, FILE * dictFP);
bool is_word_in_strand(strand_t * strand, char * word);
void print_strand_matrix(strand_t * strand);
void free_strand(strand_t * strand);

#endif
