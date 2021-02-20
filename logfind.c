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
    while(fgets(line, MAX_LINE, file) != NULL){  
        if (strcasestr(line, "international") != NULL){
            printf("%s",line);
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

















