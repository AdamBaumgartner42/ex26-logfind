/*
use scan_file to go line by line 
and use strcasestr to see if the 
line contains the term
*/

#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int scan_file (const char *filename, int search_len, char *search_for[])
{
    char *line = calloc(MAX_LINE, 1); 
    FILE *file = fopen(filename, "r");
    int match_count = 0;

    //debug("search_len: %d", search_len);

    while(fgets(line, MAX_LINE, file) != NULL){ 
        int match_count = 0; // reset every line
        for (int i = 1; i < search_len; i++){
            if (strcasestr(line, search_for[i]) != NULL){ 
                //debug("%s ", search_for[i]); 
                match_count++;  // 
            } 
            if (match_count == search_len - 1){ // if there is a match, it increments the count 
                printf("%s",line);
            }
            if (match_count > 0){
                //debug("match_count: %d", match_count);
            }
        }
    }
    
    return 0;
}

int main (int argc, char *argv[])
{
    int rc = 0;

    rc = scan_file("un_preamble.txt", argc, argv);
    
    return 0;
}

















