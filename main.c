/* Main driver for Project 01: Strands
Author: Fernando Tello
CPSC1070 - Spring 2024
Project 01: Strands */

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "strand.h"

int main(int argc, char** argv) {
    // Open strand data file
    FILE * dataFP = open_data_file(argc, argv);
    if (dataFP == NULL) return 0;

    // Open dictionary file
    FILE * dictFP = open_dict_file(argc, argv);
    if (dictFP == NULL) return 0;  

    // Create strand struct: allocate memory & populate accordingly
    strand_t * strand = create_strand(dataFP, dictFP);
    if (strand == NULL) return 0;

    // Print strand & game instructions
    print_strand_matrix(strand);
    print_instructions(strand);

    // Play the game
    play_game(strand);

    // close files
    //fclose(dataFP); 
    //fclose(dictFP);
    
    // Free all memory
    //free(dataFP);
    //free(dictFP);

    // Free all strand memory
    free_strand(strand, dictFP, dataFP);

    return 0;
}
