#include "prtfmt.h"
#define HEX 16

typedef struct test
{
    int a;
    int b;
}TEST;
int main()
{
    printf("%010ld\n", 999l);
    printf("%+010ld\n", 999l);
    printf("%010ld\n", -999l);
    printf("%+010ld\n", -999l);

    printf("%010.005ld\n", 999l);
    printf("%+010.5ld\n", 999l);
    printf("%010.005ld\n", -999l);
    printf("%+010.05ld\n", -999l);

    printf("%010.005x\n", 999);
    printf("%+010.5x\n", 999);
    printf("%010.005x\n", -999);
    printf("%+010.05x\n", -999);

    printf("%10.005d\n", 999l);
    printf("%+10.5d\n", 999l);
    printf("%10d\n", -999l);
    printf("%+10.05d\n", -999l);

    printf("**************************\n");

/////////////////////////////////////////////////////////
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

    /*
0.[12345678901234567890]
1.[hello, world]
2.[15 f F 1111]
3.[+000000999]
4.[    -00999]
5.[    010000]
6.[hello,]
7.[    hello,]
8.[hello,]
9.[    ]
10.[hello, world]
11.[hello, world        ]
12.[       hello, world]
13.[olleh]
14.[              olleh]
15.[olleh               ]
16.[oll               ]
17.[   A]
18.[   A]
19.[A                   ]
20.[  ffffffff]
21.[% % 20]

    */


    return 0;
}
