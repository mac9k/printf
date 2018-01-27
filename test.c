#include "prtfmt.h"

int main()
{
/////////////////////////////////////////////////////////Test Case 
    mini_printf ("0.[12345678901234567890]\n");
    mini_printf ("1.[hello, world]\n");
    mini_printf ("2.[%d %x %X %b]\n", 15, 15, 15, 15);
    mini_printf ("3.[%+010ld]\n", 999l);
    mini_printf ("4.[%+010.005ld]\n", -999l);
    mini_printf ("5.[%10.6b]\n", 16);
    mini_printf ("6.[%.6s]\n", "hello, world");
    mini_printf ("7.[%10.6s]\n", "hello, world");
    mini_printf ("8.[%4.6s]\n", "hello, world");
    mini_printf ("9.[%4.0s]\n", "hello, world");
    mini_printf ("10.[%9s]\n", "hello, world");
    mini_printf ("11.[%-20s]\n", "hello, world");
    mini_printf ("12.[%20s]\n", "hello, world");
    mini_printf ("13.[%~s]\n", "hello");
    mini_printf ("14.[%~20s]\n", "hello");
    mini_printf ("15.[%~-20s]\n", "hello");
    mini_printf ("16.[%~-20.3s]\n", "hello");
    mini_printf ("17.[%4.6c]\n", 'A');
    mini_printf ("18.[%4.0c]\n", 'A');
    mini_printf ("19.[%-20c]\n", 'A');
    mini_printf ("20.[%+10x]\n", -1);
    mini_printf ("21.[%99% %T %d]\n", 20);

    return 0;
}
