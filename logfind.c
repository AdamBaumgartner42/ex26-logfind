

#include <stdio.h>
#include "dbg.h"


int main (int argc, char *argv[])
{
    // Count number of inputs 
    int val_count = 0;
    for (int i = 0; argv[i] != NULL; i++){
        val_count++;
    }
    debug("val_count: %d", val_count);

    return 0;
}






