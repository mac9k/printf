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
/*
void mini_printf(char* string, ...)
    function:
        print by format

    parameter:
        char* string - string with format

void zero_print(int count)
    function:
        print zero

    parameter:
        int count - number of count

void indent_print(int indent)
    function:
        print space

    parameter:
        int indent - number of indent

void reverse_string(char* data)
    function:
        reverse string(c.f "ABC" -> "CBA")

    parameter: 
        char* data - initial data


void mini_strcpy(char* dest , const char* src)
    function:
        copy string 

    parameter:
        char* dest: destination
        char* src : source 

int mini_strlen(char* string)
    function:
        calculate string lenth

    parameter:
        char* string: source

    return:
        ex string lenth value


int mini_atoi(char* target, int size)
    function:
        switch char* value to integer value

    parameter:
        char* target - initial char* data
        int size - char* lenth

    return:
        ex 1234, 100000


char* mini_itoa(int value,char radix)
    function:
        switch integer value to char* value

    parameter:
        int value - initial integer data
        char radix - radix data (c.f d,x,X,b)

    return:
        ex "1234", "ffffffff"

*/
void mini_printf( char* , ...);
int mini_atoi( char*, int);
int mini_strlen( char* );
void mini_strcpy(char* , const char*);
void reverse_string(char*);
void indent_print(int);

void zero_print(int );
void decimal_print(Format, void*);
void hex_print(Format, void*);
void char_print(Format, void*);
Format string_print(Format, void*);
//sizeof macro
#endif // __PRTFMT_H__
