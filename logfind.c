/*
use scan_file to go line by line 
and use strcasestr to see if the 
line contains the term
*/
#define NDEBUG
#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024


int scan_file (const char *filename, int search_len, char **search_for, int *word_count) 
{
    char *line = calloc(MAX_LINE, 1); 
    FILE *file = fopen(filename, "r");
    

    while(fgets(line, MAX_LINE, file) != NULL){ 
        for (int i = 1; i < search_len; i++){
            if (strcasestr(line, search_for[i]) != NULL){ // does this get multiple items in the line? 
                debug("%s", line); // remove the "\n" from line -A: use fgetc and individually parse

                word_count[i]++; // increment 
                debug("%s: %d\n", search_for[i], word_count[i]);
            } 
        }
    }
    
    return 0;
}

int print_results (char **search_for, int *search_count, int len)
{
    for (int i = 1; i < len; i++){
        printf("%s: %d\n", search_for[i], search_count[i]);
    }

    return 0;
}

int print_int_array (int *array, int len)
{
    for (int i = 0; i < len; i++){
        printf("%d, ", array[i]);
    }
    printf("\n");

    return 0;
}

int zero_array (int *array, int len)
{
    for (int i = 0; i < len; i++){
        array[i] = 0; 
    } 

    return 0;
}

int judge_results (int *array, int len)
{
    int found_count = 0;
    int search_count = len - 1;
    for (int i = 1; i < len; i++){
        if(array[i] > 0){
            found_count++; 
        }
    }
    if(found_count == search_count){
        printf("All Serch Terms Matched. %d out of %d\n", found_count, search_count);
        return 0;
    }
    printf("No Match Found. %d out of %d\n", found_count, search_count); 
    return 0;
}



int main (int argc, char *argv[])
{
     
    int word_count[argc]; //count status
    zero_array(word_count, argc); 
    
    scan_file("logfind.c", argc, argv, word_count);
    print_results(argv, word_count, argc);
    
    judge_results(word_count, argc);
    return 0;
}

















