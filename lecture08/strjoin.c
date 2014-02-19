/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *tracks[] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches",
    "" // '' empty chararcters are illegal
};

/* Returns a heap-allocated string that contains the strings 
   from the given array, joined up with no spaces between.
*/
char *strjoin(char *array[], int n)
{
    char *retstr= malloc(sizeof(char)*sizeof(array)); //? forgot how to malloc
    char *p= retstr;
    int i = 0;
    for (i = 0; i < n; ++i)
    {
        strcpy(p, array[i]);
        p+= strlen(array[i]) ;
        //or we can do this:
        //strcat(retstr, array[i]);
        //but it is less efficeint
    }
    return retstr;
}


int main (int argc, char *argv[])
{
    char *s = strjoin(tracks, 2);
    printf("%s\n", s);
    return 0;
}
