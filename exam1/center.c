/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//stolen from web
char * test (char * s, char c) 
{ 
    s[0]==c; 
    s[1]=='\0'; 
    return s; 
} 

// Returns a heap-allocated string with length n, with
// the given string in the middle, surrounded by fillchar.
//
// For example, if s is allen, n is 10 and fillchar is .
// the result is ..allen... 

//after I find out how to convert char to string the third arg needs to be 
//changed back to a char instead of char *
char * center(char *s, int n, char * fillchar)
{
    //allocating space for the return string
    char *retstr= (char *) malloc(sizeof(char *)*n +1);
    //pointer variable for return string.
    char *start= retstr;

    //cahracter to string conversion logic
    // uncomment to run the character version of the code.
    // char fillstr[2];
 
    // test(fillstr, fillchar );
    
    //fillining in initail peicec of fillchar to retstr
    int i;
    for (i = 0; i < n/2; ++i)
    {
        //strcpy(start, fillstr);
        strcpy(start, fillchar);
        start+=1;
    }

    //adding s to return string
    strcpy(start, s);
    printf("%s", retstr);

    //filling up rest of retstr with fillchar
    int j;
    for (j = n/2; j < n; ++j)
    {
        //strcpy(start, fillstr);
        strcpy(start, fillchar);
    }
    return retstr;
}


int main (int argc, char *argv[])
{
    //run this if you want characters. THe output is a funny result.
    // char *s = center("Software", 30, '.');
    // printf("%s\n", s);

    // char *s2 = center("Systems", 31, '-');
    // printf("%s\n", s2);

    // char *s3 = center("Spring 2014", 32, '*');
    // printf("%s\n", s3);

    // char *s4 = center("Exam 1", 33, '^');
    // printf("%s\n", s4);

    char *s = center("Software", 30, ".");
    printf("%s\n", s);

    char *s2 = center("Systems", 31, "-");
    printf("%s\n", s2);

    char *s3 = center("Spring 2014", 32, "*");
    printf("%s\n", s3);

    char *s4 = center("Exam 1", 33, "^");
    printf("%s\n", s4);

    return 0;
}
