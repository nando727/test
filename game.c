/* [Code Description]
Author: Fernando Tello
CPSC1070 - Spring 2024
Project 01: Strands */

#include "game.h"

// REQUIRED
FILE * open_data_file(int argc, char** argv) {
    if (argc > 1) { // if file name provided as argument
        FILE * file = fopen(argv[1], "r");
        return file;
    }
    else { // otherwise user input file name
        char filename[100]; 
        scanf("%s", filename);
        FILE * file = fopen(filename, "r");
        return file;
    }
}


// REQUIRED
FILE * open_dict_file(int argc, char** argv) {
    if (argc > 2) { // if file name provided as argument
        FILE * file = fopen(argv[2], "r");
        return file;
    }
    else { // otherwise use default file name set in game.h
        FILE * file = fopen(DICT_PATH, "r");
        return file;
    }
}

// REQUIRED - DO NOT EDIT
void print_instructions(strand_t * strand) {
    // Print instructions
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
    int found = 0; // number of words found
    int total = strand->numWords; // total number of words to find
    char word[100]; // guessed word

    char guessedWords[strand->numWords][100]; // array to store guessed words
    int guessedCount = 0; // number of guessed words

    while (found < total) { // loop until all words found
        printf("Guess a word or 'quit': \n");
        scanf("%s", word); // read user input
        for (int i = 0; word[i]; i++) {
            word[i] = tolower(word[i]); // convert to lowercase
        }
        if (strcmp(word, "quit") == 0) { // check if user quit
            printf("You found %d out of %d %d-letter words.\nThanks for playing!\n", found, total, strand->wordLen);
            break; // remove?
        }
        bool alreadyGuessed = false; // boolean to check if word already guessed
        for (int i = 0; i < guessedCount; i++) { // loop through guessed words array
            if (strcmp(guessedWords[i], word) == 0) { // check if word already guessed
                alreadyGuessed = true;
                printf("You have already guessed %s!\n", word);
                if (found < total) { // only print if not all words found
                    printf("You have found %d of %d %d-letter words in the strand so far.\n\n", found, total, strand->wordLen);
                }
                break; // remove?
            }
        }

        if (!alreadyGuessed && is_word_in_strand(strand, word)) { // check if word is in strand
            strcpy(guessedWords[guessedCount++], word); // add word to guessed words
            found++; // increment found words
            if (found < total) { // only print if not all words found
                printf("%s is a valid word in the strand!\nYou have found %d of %d %d-letter words in the strand so far.\n\n", word, found, total, strand->wordLen);
            } else { // print if all words found
                printf("%s is a valid word in the strand!\n", word);
            }
        } else if (!alreadyGuessed) { // print if word not in strand
            printf("%s is not a valid word in the strand.\nYou have found %d of %d %d-letter words in the strand so far.\n\n", word, found, total, strand->wordLen);
        }
    }

    if (found == total) { // print if all words found
        printf("You found all %d %d-letter words!\nGreat job! Thanks for playing!\n", total, strand->wordLen);
    }
}