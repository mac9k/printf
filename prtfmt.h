#ifndef __PRTFMT_H__
#define __PRTFMT_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

#define DECIMAL 10
#define HEX     16
#define OCT     8   //N/A
#define BINARY  2
#define MAX     10 //int max value

#define FALSE 0
#define TRUE  1

#define POSITIVE 1
#define NEGATIVE -1

typedef struct format{
    int indent;     //space  ex) %10d
    int sign;       //positive, negative
    int reverse;    //reverse print
    int lenth;      //string field  %.10d
    int zero;       //print zero
    char mark;      //print +,-
}Format;


void mini_printf( char* , ...);
int mini_atoi( char*, int);
int mini_strlen( char* );
void reverse_string(char*);
//plus sizeof func
int mini_sizeof(void*);
void indent_print(int);
void zero_print(int );
void decimal_print(Format, void*);
void hex_print(Format, void*);
void char_print(Format, void*);
#endif // __PRTFMT_H__
