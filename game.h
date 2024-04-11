/* [Code Description]
Author: Fernando Tello
CPSC1070 - Spring 2024
Project 01: Strands */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

#include "strand.h"

#define DICT_PATH "/usr/share/dict/american-english"

// REQUIRED FUNCTIONS
FILE * open_data_file(int argc, char** argv);
FILE * open_dict_file(int argc, char** argv);
void print_instructions(strand_t * strand);
void play_game(strand_t * strand);

#endif