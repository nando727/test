/* Definitions & function prototypes for game.c
Author: Fernando Tello
CPSC1070 - Spring 2024
Project 01: Strands */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

#include "strand.h"

#define DICT_PATH "/usr/share/dict/american-english" // default dictionary file path

// function prototypes
FILE * open_data_file(int argc, char** argv); // opens & returns data file if provided as second argument, user input otherwise
FILE * open_dict_file(int argc, char** argv); // opens & returns dictionary file if provided as third argument, default file otherwise
void print_instructions(strand_t * strand); // prints game instructions
void play_game(strand_t * strand); // main game loop, handles correct, incorrect, and repeated guesses, allows user to quit game

#endif