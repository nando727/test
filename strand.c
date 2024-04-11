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
            dict[*dictSize] = strdup(word); // copy word to dict & allcate memory for word copy
            (*dictSize)++; // increment dictSize

            if (*dictSize == 500000) { // if dictSize reaches 500000, break loop
                break; // remove?
            }
        }
    }

    return dict; // returns dictionary
}

bool isValidCell(int currentRow, int currentCol, int rows, int cols) {
    /*            
        0,0  0,1  0,2 ...
        1,0  1,1  1,2 ...
        2,0  2,1  2,2 ...
        ...  ...  ...

    Checks if cell is within bounds of matrix
    Returns true if current row is greater than or equal to 0 & less than rows 
    AND current column is greater than or equal to 0 & less than columns
    */
    return (currentRow >= 0) && (currentRow < rows) && (currentCol >= 0) && (currentCol < cols);
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
    path[index] = strand->letters[row][col]; // add current letter to path
    path[index + 1] = '\0'; // null terminate string

    if (index + 1 == wordLen) { // check if word matches length, +1 for null terminator
       if (isWordInDictionary(path, dictionary, dictSize)) { // check if word is in dictionary
            addWordToStrand(strand, path); // add word to strand if found & matches length
        }
        return;
    }
    
    /*            
    0,0  0,1  0,2 ...
    1,0  1,1  1,2 ...
    2,0  2,1  2,2 ...
    ...  ...  ...

    strands->letters is 2D array of letters in matrix, following for loop operation checks all directions of current index
    -1 goes back up rows or towards left columns
    loops through above, below, and current row ( -1 -> 0 -> 1) */
    for (int rowDr = -1; rowDr <= 1; rowDr++) {
        // loops through left, right, and current column ( -1 -> 0 -> 1)
        for (int colDr = -1; colDr <= 1; colDr++) {
            if (!(rowDr == 0 && colDr == 0)) { // skip current cell (0,0)
                int newRow = row + rowDr; // next row
                int newCol = col + colDr; // next column

                // recursively call using new row & column, index + 1 to move to path's next index
                findWordsFromCell(newRow, newCol, path, index + 1, strand, dictionary, dictSize, wordLen);
            }
        }
    }
}

void generateAndCheckWords(strand_t* strand, char** dictionary, int dictSize) {
    // string that will store letters as findWordsFromCell recursively goes through matrix 
    char path[strand->wordLen + 1]; // allocate memory size of wordLen, +1 for null-terminator

    for (int i = 0; i < strand->rows; i++) { // loop through rows
        for (int j = 0; j < strand->cols; j++) { // loop through columns
            for (int i = 0; i < sizeof(path); i++) { // initialize path as empty string
                path[i] = '\0';
            } 
            // nested for-loop will call findWordsFromCell for each cell in the matrix
            findWordsFromCell(i, j, path, 0, strand, dictionary, dictSize, strand->wordLen);
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
void free_strand(strand_t * strand, FILE * dataFP, FILE * dictFP) {
    for (int i = 0; i < strand->rows; i++) { // loop through and free memory for each row
        free(strand->letters[i]);
    }
    free(strand->letters); // free memory for letters
    for (int i = 0; i < strand->numWords; i++) { // loop through and free memory for each word
        free(strand->words[i]);
    }
    free(strand->words); // free memory for words
    free(strand); // free memory for strand itself

    fclose(dataFP); 
    fclose(dictFP);

    dataFP = NULL;
    dictFP = NULL;

}