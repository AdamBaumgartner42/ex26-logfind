
//#define NDEBUG
#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#define MAX_LINE 1024

int scan_file (const char *filename, int search_len, char **search_for, int *word_count) 
{
    char *line = calloc(MAX_LINE, 1); 
    FILE *file = fopen(filename, "r");  


    check_mem(line);
    check(file, "Failed to open file: %s", filename);

    while(fgets(line, MAX_LINE, file) != NULL){ 
        for (int i = 1; i < search_len; i++){
            if (strcasestr(line, search_for[i]) != NULL){
                word_count[i]++; 
            } 
        }
    }

    free(line);
    fclose(file);

    return 0;

error:
    if(line) free(line);
    if(file) fclose(file);

    return -1;
}

int print_results (char **search_for, int *search_count, int len)
{
    for (int i = 1; i < len; i++){
        printf("%s: %d\n", search_for[i], search_count[i]);
    }

    return 0;

error:
    return -1;
}

int print_int_array (int *array, int len)
{
    for (int i = 0; i < len; i++){
        printf("%d, ", array[i]);
    }
    printf("\n");

    return 0;

error:
    return -1;
}

int zero_array (int *array, int len)
{
    for (int i = 0; i < len; i++){
        array[i] = 0; 
    } 

    return 0;

error:
    return -1;
}

int judge_results (int *array, int len, char *filename)
{
    int found_count = 0;
    int search_count = len - 1;
    for (int i = 1; i < len; i++){
        if(array[i] > 0){
            found_count++; 
        }
    }
    if(found_count == search_count){
        printf("%s\n", filename);
        return 0;
    }
    return 0;

error:
    return -1;
}

int find_files(glob_t *pglob)
{
    int glob_flags = GLOB_TILDE;
    // glob_flags =  100000000000 
    glob("*.c", glob_flags, NULL, pglob); //  100000000000
    glob_flags = glob_flags | GLOB_APPEND; // bitwise OR  
    // glob_flags = 100000000001 , see the new '1' at the end? 
    glob("*.h", glob_flags, NULL, pglob); 
    
    return 0; 
    
error:
    return -1;
}



int main (int argc, char *argv[])
{
    int word_count[argc]; //count status
    check(argc > 1, "USAGE: logfind word word word");
    

    // Use glob to find files
    glob_t found_files;
    find_files(&found_files);

    // Search across the relevant files 
    for (int i = 0; i < found_files.gl_pathc; i++){
        zero_array(word_count, argc);  
        scan_file(found_files.gl_pathv[i], argc, argv, word_count); 
        judge_results(word_count, argc,found_files.gl_pathv[i]);
    }

    return 0;

error: 
    return 1;
}

















