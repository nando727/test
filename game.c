/* [Code Description]
Author: Fernando Tello
CPSC1070 - Spring 2024
Project 01: Strands */

#include "game.h"

// REQUIRED
FILE * open_data_file(int argc, char** argv) {
    if (argc > 1) {
        FILE * file = fopen(argv[1], "r");
        return file;
    }
    else {
        char filename[100];
        scanf("%s", filename);
        FILE * file = fopen(filename, "r");
        return file;
    }
}


// REQUIRED
FILE * open_dict_file(int argc, char** argv) {
    if (argc > 2) {
        FILE * file = fopen(argv[2], "r");
        return file;
    }
    else {
        FILE * file = fopen(DICT_PATH, "r");
        return file;
    }
}

// REQUIRED - DO NOT EDIT
void print_instructions(strand_t * strand) {
    printf("\n  +-- Welcome to Strands! --+\n");
    printf("\nInstructions:\n");
    printf("\tFind all %d %d-letter words\n", strand->numWords, strand->wordLen);
    printf("\tEach word's letters must touch\n");
    printf("\tA letter can be repeated in a word\n");
    printf("\tType a word then press 'Enter'\n");
    printf("\tType 'quit' when done\n");
}

// REQUIRED
void play_game(strand_t * strand) {
    int found = 0;
    int total = strand->numWords;
    char word[100];

    char guessedWords[strand->numWords][100];
    int guessedCount = 0;

    while (found < total) {
        printf("Guess a word or 'quit': \n");
        scanf("%s", word);
        for (int i = 0; word[i]; i++) {
            word[i] = tolower(word[i]);
        }
        if (strcmp(word, "quit") == 0) {
            printf("You found %d out of %d %d-letter words.\nThanks for playing!\n", found, total, strand->wordLen);
            break;
        }
        bool alreadyGuessed = false;
        for (int i = 0; i < guessedCount; i++) {
            if (strcmp(guessedWords[i], word) == 0) {
                alreadyGuessed = true;
                printf("You have already guessed %s!\n", word);
                if (found < total) { // Only print if not all words found
                    printf("You have found %d of %d %d-letter words in the strand so far.\n\n", found, total, strand->wordLen);
                }
                break;
            }
        }

        if (!alreadyGuessed && is_word_in_strand(strand, word)) {
            strcpy(guessedWords[guessedCount++], word); // Safe because of the %99s limit above
            found++;
            if (found < total) { // Check if this condition meets before printing
                printf("%s is a valid word in the strand!\nYou have found %d of %d %d-letter words in the strand so far.\n\n", word, found, total, strand->wordLen);
            } else {
                printf("%s is a valid word in the strand!\n", word);
            }
        } else if (!alreadyGuessed) {
            printf("%s is not a valid word in the strand.\nYou have found %d of %d %d-letter words in the strand so far.\n\n", word, found, total, strand->wordLen);
        }
    }

    if (found == total) {
        printf("You found all %d %d-letter words!\nGreat job! Thanks for playing!\n", total, strand->wordLen);
    }
}