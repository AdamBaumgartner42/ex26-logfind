#include <stdio.h>
#include <stdlib.h>

int edit_array ( int update_index, int update_value, int *array )
{
    array[update_index] = update_value;

    return 0;
}

int print_array (int *array, int len)
{
    for (int i = 0; i < len; i++){
        printf("%d, ", array[i]);
    }
    printf("\n");

    return 0;
}


int duplicate_array ( char **data_array, int *int_array, int length_argc)
{
    for (int i = 0; i < length_argc; i++){
        int_array[i] = atoi(data_array[i]);
    }
    
    return 0;
}

int main (int argc, char *argv[])
{
    int numbers [argc];

    duplicate_array(argv, numbers, argc);

    print_array(numbers, argc); 

    edit_array(2, 42, numbers);

    print_array(numbers, argc);  

    return 0;

}




