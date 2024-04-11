/* Required functions declared in strand.h & helper function implementations
Author: Fernando Tello
CPSC1070 - Spring 2024
Project 01: Strands */

#include "strand.h"

char** readDictionary(FILE* dictFP, int* dictSize) {
    char** dict = malloc(500000 * sizeof(char*)); // allocate unreal amount of memory
    char word[100]; // 100 bytes allocated for each word
    *dictSize = 0; // initialize dictSize to 0

   while (fscanf(dictFP, "%s", word) == 1) { // read words from file, each one sepearated by newlines
        if (islower(word[0])) { // ignore uppercase proper nouns
            // is this needed?
            for (int i = 0; word[i]; i++) { 
                word[i] = tolower(word[i]);
            }
            
            dict[*dictSize] = strdup(word); // copy word to dict & allcate memory for word copy
            (*dictSize)++; // increment dictSize

            if (*dictSize == 500000) { // if dictSize reaches 500000, break loop
                break; // remove?
            }
        }
    }

    return dict; // returns dictionary
}

bool isValidCell(int row, int col, int rows, int cols) { 
    return (row >= 0) && (row < rows) && (col >= 0) && (col < cols); // check if cell is within bounds
}

bool isWordInDictionary(const char* word, char** dictionary, int dictSize) {
    for (int i = 0; i < dictSize; i++) { // loop through dictionary
        if (strcmp(word, dictionary[i]) == 0) { // compare word against dictionary 
            return true;
        }
    }
    return false; // return false if word not found in dictionary
}

void addWordToStrand(strand_t* strand, const char* word) {
    for (int i = 0; i < strand->numWords; i++) { // loop through words in strand
        if (strcmp(strand->words[i], word) == 0) { // checks if word is already in strand
            return;
        }
    }
    strand->words = realloc(strand->words, (strand->numWords + 1) * sizeof(char*)); // reallocate memory for new word
    strand->words[strand->numWords] = strdup(word); // copy word to strand & allocate memory for word copy
    strand->numWords++; // increment number of words in strand
}

void findWordsFromCell(int row, int col, char* path, int index, strand_t* strand, char** dictionary, int dictSize, int wordLen) {
    if (!isValidCell(row, col, strand->rows, strand->cols)) return; // check if cell is within bounds
    path[index] = strand->letters[row][col]; // add letter to path
    path[index + 1] = '\0'; // null-terminate string

    if (index + 1 == wordLen) { // check if word matches length
       if (isWordInDictionary(path, dictionary, dictSize)) { // check if word is in dictionary
            addWordToStrand(strand, path); // add word to strand if found & matches length
        }
        return;
    }
    // explore all 8 directions
    for (int dRow = -1; dRow <= 1; dRow++) { // loop through rows
        for (int dCol = -1; dCol <= 1; dCol++) { // loop through columns
            if (!(dRow == 0 && dCol == 0)) { // check if cell is not the same
                int newRow = row + dRow; // new row
                int newCol = col + dCol; // new column
                findWordsFromCell(newRow, newCol, path, index + 1, strand, dictionary, dictSize, wordLen); // recursively call function with new cell
            }
        }
    }
}

void generateAndCheckWords(strand_t* strand, char** dictionary, int dictSize) {
    char path[strand->wordLen + 1]; // allocate memory for path, +1 for null-terminator
    for (int i = 0; i < strand->rows; i++) { // loop through rows
        for (int j = 0; j < strand->cols; j++) { // loop through columns
            memset(path, 0, sizeof(path)); // clear path

            // pass in the strand, dictionary, and dictSize
            findWordsFromCell(i, j, path, 0, strand, dictionary, dictSize, strand->wordLen); // find words from current cell
        }
    }
}

strand_t * create_strand(FILE * dataFP, FILE * dictFP) {
    int dictSize = 0; // initialize dictionary size
    char** dictionary = readDictionary(dictFP, &dictSize); // read dictionary from file

    strand_t *strand = malloc(sizeof(strand_t)); // allocate memory for strand

    if (fscanf(dataFP, "%d %d %d", &strand->rows, &strand->cols, &strand->wordLen) != 3) { // initialize strand rows, cols, & wordLen from file
        free(strand); 
        return NULL;
    }

    strand->letters = malloc(strand->rows * sizeof(char*)); // allocate memory for letters in strand

    for (int i = 0; i < strand->rows; i++) { // loop through rows
        strand->letters[i] = malloc((strand->cols + 1) * sizeof(char)); // allocate memory for each row
        for (int j = 0; j < strand->cols; j++) { // loop through columns
            fscanf(dataFP, " %c", &strand->letters[i][j]); // read letters from file
            strand->letters[i][j] = tolower(strand->letters[i][j]); // convert to lowercase
        }
        strand->letters[i][strand->cols] = '\0'; // null-terminate string
    }

    strand->words = NULL; // initialize words in strand
    strand->numWords = 0; // initialize number of words in strand

    generateAndCheckWords(strand, dictionary, dictSize); // generate & check words in strand

    for (int i = 0; i < dictSize; i++) { // loop through dictionary
        free(dictionary[i]); // free memory for each word in dictionary
    }
    free(dictionary); // free dictionary itself
    return strand; // return strand struct
}

// REQUIRED
bool is_word_in_strand(strand_t * strand, char * word) { 
    for (int i = 0; i < strand->numWords; i++) { // loop through words in strand
        if (strcmp(strand->words[i], word) == 0) { // compare word against words in strand
            return true;
        }
    }
    return false; // return false if word not found in strand
}

// REQUIRED
void print_strand_matrix(strand_t * strand) {
    for (int i = 0; i < strand->rows; i++) { // loop through rows
        for (int j = 0; j < strand->cols; j++) { // loop through columns
            printf("+---"); // top-mid borders
        }
        printf("+\n"); // end border
        for (int j = 0; j < strand->cols; j++) { // loop through columns
            printf("| %c ", strand->letters[i][j]); // print letter in strand w/ left border
        }
        printf("|\n"); // end row
    }
    // print bottom border
    for (int i = 0; i < strand->cols; i++) {
            printf("+---");
    }   
    printf("+\n"); // end border
}   


// REQUIRED
void free_strand(strand_t * strand) {
    for (int i = 0; i < strand->rows; i++) { // loop through and free memory for each row
        free(strand->letters[i]);
    }
    free(strand->letters); // free memory for letters
    for (int i = 0; i < strand->numWords; i++) { // loop through and free memory for each word
        free(strand->words[i]);
    }
    free(strand->words); // free memory for words
    free(strand); // free memory for strand itself
}