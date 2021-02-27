
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
            if(strcmp(search_for[i],"-o") != 0){
                if (strcasestr(line, search_for[i]) != NULL){
                    word_count[i]++; 
                }
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

int judge_results (int *array, int len, char *filename, int or_status)
{
    int i; 
    int found_count = 0;
    int search_count = len - 1;

    for (i = 1; i < len; i++){
        if(array[i] > 0){
            found_count++; 
        }
    }

    if(or_status == 1 && found_count > 0){ 
        printf("%s\n", filename);
        return 0;
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
    char *line = calloc(MAX_LINE, 1);
    FILE *file = fopen(".logfind", "r");
    int glob_flags = GLOB_TILDE;
   
    while(fgets(line, MAX_LINE, file) != NULL){
        line[strlen(line) - 1] = '\0'; 
        glob(line, glob_flags, NULL, pglob); 
    
        if(glob_flags == GLOB_TILDE){
            glob_flags = glob_flags | GLOB_APPEND;
        }
            
    } 
    return 0; 
    
error:
    return -1;
}

// error if or is used and NONE of the words are present. 
// logfind is being selected, every time 

int main (int argc, char *argv[])
{
    int i; 
    int or_flag = 0;
    int word_count[argc]; 
    check(argc > 1, "USAGE: logfind word word word");
    
    // Check for '-o' in argv[]
    for (i = 1; i < argc; i++){
        if (strcmp(argv[i], "-o") == 0){ // always returning true
            or_flag = 1;
        }
    }
    
    glob_t found_files;
    find_files(&found_files);

    // Search across the relevant files 
    for (i = 0; i < found_files.gl_pathc; i++){
        zero_array(word_count, argc);  
        scan_file(found_files.gl_pathv[i], argc, argv, word_count); 
        judge_results(word_count, argc,found_files.gl_pathv[i], or_flag);
    }

    return 0;

error: 
    return 1;
}

















