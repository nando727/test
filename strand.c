/* [Code Description]
Author: Fernando Tello
CPSC1070 - Spring 2024
Project 01: Strands */

#include "strand.h"

char** readDictionary(FILE* dictFP, int* dictSize) {
    char** dict = malloc(500000 * sizeof(char*));
    char wordBuffer[100];
    *dictSize = 0;

   while (fscanf(dictFP, "%99s", wordBuffer) == 1) {
        if (islower(wordBuffer[0])) {
            for (int i = 0; wordBuffer[i]; i++) {
                wordBuffer[i] = tolower(wordBuffer[i]);
            }
            
            dict[*dictSize] = strdup(wordBuffer);
            (*dictSize)++;

            if (*dictSize == 500000) {
                break;
            }
        }
    }

    return dict;
}

bool isValidCell(int row, int col, int rows, int cols) {
    return (row >= 0) && (row < rows) && (col >= 0) && (col < cols);
}

bool isWordInDictionary(const char* word, char** dictionary, int dictSize) {
    for (int i = 0; i < dictSize; i++) {
        if (strcmp(word, dictionary[i]) == 0) {
            return true;
        }
    }
    return false;
}

void addWordToStrand(strand_t* strand, const char* word) {
    for (int i = 0; i < strand->numWords; i++) {
        if (strcmp(strand->words[i], word) == 0) {
            return;
        }
    }
    strand->words = realloc(strand->words, (strand->numWords + 1) * sizeof(char*));
    strand->words[strand->numWords] = strdup(word);
    strand->numWords++;
}

void findWordsFromCell(int row, int col, char* path, int index, strand_t* strand, char** dictionary, int dictSize, int wordLen) {
    if (!isValidCell(row, col, strand->rows, strand->cols)) return;
    path[index] = strand->letters[row][col];
    path[index + 1] = '\0'; // Null-terminate the string

   

    if (index + 1 == wordLen) { 
       if (isWordInDictionary(path, dictionary, dictSize)) { // diff arguments needed for your new implementation
            addWordToStrand(strand, path);
        }
        return;
    }

    // Explore all 8 directions, including the possibility of staying in the current cell
    for (int dRow = -1; dRow <= 1; dRow++) {
        for (int dCol = -1; dCol <= 1; dCol++) {
            if (!(dRow == 0 && dCol == 0)) { 
                int newRow = row + dRow;
                int newCol = col + dCol;
                findWordsFromCell(newRow, newCol, path, index + 1, strand, dictionary, dictSize, wordLen);
            }
        }
    }
}

void generateAndCheckWords(strand_t* strand, char** dictionary, int dictSize) {
    char path[strand->wordLen + 1]; // +1 for null terminator

    for (int i = 0; i < strand->rows; i++) {
        for (int j = 0; j < strand->cols; j++) {
            memset(path, 0, sizeof(path)); // Clear path for each new start
            // Now pass the dictionary array and its size to findWordsFromCell
            findWordsFromCell(i, j, path, 0, strand, dictionary, dictSize, strand->wordLen); // changed arguments
        }
    }
}

strand_t * create_strand(FILE * dataFP, FILE * dictFP) {
    int dictSize = 0;
    char** dictionary = readDictionary(dictFP, &dictSize);

    strand_t *strand = malloc(sizeof(strand_t));
    if (!strand) {
        perror("Failed to allocate memory for strand");
        return NULL;
    }

    if (fscanf(dataFP, "%d %d %d", &strand->rows, &strand->cols, &strand->wordLen) != 3) {
        free(strand);
        return NULL;
    }

    strand->letters = malloc(strand->rows * sizeof(char*));

    for (int i = 0; i < strand->rows; i++) {
        strand->letters[i] = malloc((strand->cols + 1) * sizeof(char));
        for (int j = 0; j < strand->cols; j++) {
            //char temp;
            fscanf(dataFP, " %c", &strand->letters[i][j]);
            strand->letters[i][j] = tolower(strand->letters[i][j]);
        }
        strand->letters[i][strand->cols] = '\0';
    }

    strand->words = NULL;
    strand->numWords = 0;

    generateAndCheckWords(strand, dictionary, dictSize);

    for (int i = 0; i < dictSize; i++) {
        free(dictionary[i]);
    }
    free(dictionary);
    return strand;
}

// REQUIRED
bool is_word_in_strand(strand_t * strand, char * word) {
    for (int i = 0; i < strand->numWords; i++) {
        if (strcmp(strand->words[i], word) == 0) {
            return true;
        }
    }
    return false;
}

// REQUIRED
void print_strand_matrix(strand_t * strand) {
    for (int i = 0; i < strand->rows; i++) {
        for (int j = 0; j < strand->cols; j++) {
            printf("+---");
        }
        printf("+\n");
        for (int j = 0; j < strand->cols; j++) {
            printf("| %c ", strand->letters[i][j]);
        }
        printf("|\n");
    }
    for (int i = 0; i < strand->cols; i++) { // ROWS TO COLS NEW
            printf("+---");
    }   
    printf("+\n");
}   


// REQUIRED
void free_strand(strand_t * strand) {
    for (int i = 0; i < strand->rows; i++) {
        free(strand->letters[i]);
    }
    free(strand->letters);
    for (int i = 0; i < strand->numWords; i++) {
        free(strand->words[i]);
    }
    free(strand->words);
    free(strand);
}