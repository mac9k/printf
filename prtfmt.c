#include "prtfmt.h"


/*
char* mini_itoa(int value,char radix)
    function:
        switch integer value to char* value

    parameter:
        int value - initial integer data
        char radix - radix data (c.f d,x,X,b)

    return:
        ex "1234", "ffffffff"

*/
char* mini_itoa(int value, char radix)
{
    static char buf[MAX];   // start array
    char *dest=buf;         
    int base;               // decimal, hex, binary (octo)

    switch(radix){
        case 'd': base=DECIMAL; break;
        case 'x':
        case 'X': base=HEX; break;
        case 'b': base=BINARY; break;

    }
    static char lo_num[]="0123456789abcdef";
    static char up_num[]="0123456789ABCDEF";

    if(base==DECIMAL && value < 0){ // check value +/- only for DECIMAL
        *dest++='-';
        value= value*-1;
    }

    if(base ==HEX && value < 0 ){ // check value +/- only for hex. (only 32bit) '0xf' value match per 4bit
        *dest++=lo_num[(unsigned)(value & (0xf<<28)) >>28];
        *dest++=lo_num[(unsigned)(value & (0xf<<24)) >>24];
        *dest++=lo_num[(unsigned)(value & (0xf<<20)) >>20];
        *dest++=lo_num[(unsigned)(value & (0xf<<16)) >>16];
        *dest++=lo_num[(unsigned)(value & (0xf<<12)) >>12];
        *dest++=lo_num[(unsigned)(value & (0xf<<8) ) >>8];
        *dest++=lo_num[(unsigned)(value & (0xf<<4) ) >>4];
        *dest++=lo_num[(unsigned)(value & (0xf<<0) ) >>0];
    }
    else{ // No negative 
        do{//decimal data stack up array
            if(radix=='X')//an upper case.
                *dest++=up_num[value%base];
            else//a lower case.
                *dest++=lo_num[value%base];
        }while(value/=base);
    }
    *dest='\0';

    if(base ==HEX && value < 0)
        return buf;
    reverse_string(buf);
    return buf;
}

/*
int mini_atoi(char* target, int size)
    function:
        switch char* value to integer value

    parameter:
        char* target - initial char* data
        int size - char* lenth

    return:
        ex 1234, 100000

*/
int mini_atoi(char* target, int size)
{
    int temp,res=0;
    if(size < 0 )
        return -1;


    for(size--,temp=1;size>=0;size--,temp*=10){
        if(*(target+size) - '0' >=0 && *(target+size) - '0' <=9)
            res+= (*(target + size) -'0') * temp;
    }
    return res;
}

/*
int mini_strlen(char* string)
    function:
        calculate string lenth

    parameter:
        char* string: source

    return:
        ex string lenth value

*/
int mini_strlen(char* string)
{
    int i=0;
    while(*string++!=NULL)i++;
    return i;
}

/*
int mini_sizeof(void* string)
    function:
        calculate array size


    return:
        ex  lenth array

*/
int mini_sizeof(void* string)
{


}

/*
void reverse_string(char* data)
    function:
        reverse string(c.f "ABC" -> "CBA")

    parameter: 
        char* data - initial data

*/
void reverse_string(char* data)
{
    char temp; //swap
    char* start=data, *end=data+mini_strlen(data)-1;
    if( '-' == *start)start++;
    while(start<end){
        temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
}

/*
void indent_print(int indent)
    function:
        print space

    parameter:
        int indent - number of indent

*/
void indent_print(int indent)
{
    int i;
    char temp = ' ';
    for(i=0;i<indent;i++)
        write(STDOUT_FILENO,&temp,sizeof(temp));
}

/*
void zero_print(int count)
    function:
        print zero

    parameter:
        int count - number of count

*/

void zero_print(int count)
{
    int i;
    char temp = '0';
    for(i=0;i<count;i++)
        write(STDOUT_FILENO,&temp,sizeof(temp));
}

/*
void mini_printf(char* string, ...)
    function:
        print by format

    parameter:
        char* string - string with format

*/
void mini_printf(char* string, ...)
{
    va_list args;
    va_start(args,string);
    Format form = {POSITIVE,0,0,NEGATIVE,0,'\0'};   //indent, sign, reverse, lenth, zero, mark
    void* data;
    char* addr;//fixed address.
    char* buf;//buf address changed.
    int i=0;
    buf=(char*)malloc(mini_strlen(string) * sizeof(char));
    addr=buf;
    strcpy(buf,string);
    while(*buf!= NULL){
        if(*buf == '%'){
            switch(*++buf){ //format specifier := %[flags][width][.precision][type-prefix]typeflag, width, precision, type
            case '+':
                      form.indent=POSITIVE;
                      *buf='%';
                      form.mark='+';
                      break;
            case '-':
                      form.indent=NEGATIVE;
                      *buf='%';
                      break;
            case '~':
                      form.reverse=TRUE;
                      *buf='%';
                      break;

            case '.':
                      form.lenth=TRUE;
                      buf++;
                      if(*buf >= '0' && *buf <= '9'){
                        i=0;
                        while(*(buf+i) >= '0' && *(buf+i) <= '9')
                            i++;
                        form.lenth = form.lenth * mini_atoi(buf,i);     // caculate lenth value (c.f 005  => 5)
                        buf=buf+i-1;
                        *buf='%';
                       }

                      *buf='%';
                      break;
            case '0':
                      form.zero=TRUE;
                      *buf='%';
                      break;
            break;


            case 'c':
                        data=va_arg(args,char *);
                        if(form.indent > 1){//pre indent
                            indent_print(form.indent-1);
                        }
                        if(form.lenth >= 0){
                            write(STDOUT_FILENO,&data,sizeof(char));
                        }
                        else{//DEL
                            write(STDOUT_FILENO,&data,sizeof(char));
                        }
                        if(form.indent < 1){//post indent
                            indent_print(-1 * form.indent-1);
                        }
                        buf++;
                        break;


            case 's':
                        data=va_arg(args,char *);
                        if(form.indent > 1){ //pre indent
                            if(form.lenth == 0)
                                indent_print(form.indent);// print full indent
                            else
                                indent_print(form.indent-(mini_strlen(data)-form.lenth));   // print partital indent
                        }

                        if(form.reverse==TRUE){ // %~s
                            char *array = (char*)malloc(mini_strlen(data) * sizeof(char));
                            strcpy(array,data);
                            reverse_string(array);
                            if(form.lenth >= 0){ 
                                write(STDOUT_FILENO,array,form.lenth);
                            }
                            else{
                                write(STDOUT_FILENO,array,mini_strlen(array));
                            }
                            form.reverse=FALSE;
                            free(array);
                        }else{ // %s
                            if(form.lenth >= 0){
                                write(STDOUT_FILENO,data,form.lenth);
                            }
                            else
                                write(STDOUT_FILENO,data,mini_strlen(data));
                        }
                        if(form.indent < 1) //post indent
                            indent_print(-1 * form.indent-mini_strlen(data));
                        buf++;
                        break;

            case 'b':
                        data=va_arg(args,int );
                        data=mini_itoa(data,'b');
                        hex_print(form,data);
                        buf++;
                        break;
            case 'd':
                        data=va_arg(args,int );
                        data=mini_itoa(data,'d');
                        // if('-' == *(char*)data){//if value is negative, 
                        //     int temp = mini_atoi(data, mini_strlen(data));
                        //     data = mini_itoa(temp,'d');
                        //     form.mark = '-';
                        // }
                        // if(form.indent > 1){ //pre indent
                        //     if(form.lenth >= 0){
                        //         if(form.zero == TRUE){
                        //             indent_print(form.indent-form.lenth-1);
                        //             if(form.mark =='-'){
                        //                 write(STDOUT_FILENO,&form.mark,1);
                        //             }
                        //             else if(form.mark == '+'){
                        //                 write(STDOUT_FILENO,&form.mark,1);
                        //             }
                        //             zero_print(form.indent-mini_strlen(data)-form.lenth);
                        //         }
                        //         else{
                        //             indent_print(form.indent-form.lenth);
                        //             if(form.mark =='-'){
                        //                 write(STDOUT_FILENO,&form.mark,1);
                        //             }
                        //             else if(form.mark == '+'){
                        //                 write(STDOUT_FILENO,&form.mark,1);
                        //             }
                        //         }
                        //     }
                        //     else{//form.lenth not used
                        //         if(form.zero == TRUE){//fill indent
                        //             if(form.mark =='-'){
                        //                 write(STDOUT_FILENO,&form.mark,1);
                        //             }
                        //             else if(form.mark == '+'){
                        //                 write(STDOUT_FILENO,&form.mark,1);
                        //             }
                        //             else{//fill zero
                        //                 zero_print(form.indent-mini_strlen(data));
                        //             }
                        //             zero_print(form.indent-mini_strlen(data)-1);
                        //         }
                        //         else{//No zero, filled indent
                        //             if(form.mark != NULL){
                        //                 if(form.mark =='-'){
                        //                     write(STDOUT_FILENO,&form.mark,1);
                        //                 }
                        //                 else if(form.mark == '+'){
                        //                     write(STDOUT_FILENO,&form.mark,1);
                        //                 }
                        //             }
                        //             else{
                        //                 indent_print(form.indent-mini_strlen(data));
                        //             }
                        //             indent_print(form.indent-mini_strlen(data)-1);
                        //         }
                        //     }
                        // }
                        // if(form.lenth >= 0){
                        //     write(STDOUT_FILENO,data,form.lenth);
                        // }
                        // else{
                        //     write(STDOUT_FILENO,data,mini_strlen(data));
                        // }
                        // if(form.indent < 1){ //post indent
                        //     indent_print(-1 * form.indent-mini_strlen(data));
                        // }

                        decimal_print(form,data);
                        buf++;
                        break;

                        
            case 'l': //long
                      if(*++buf == 'd'){
                        data=va_arg(args,long);
                        data=mini_itoa(data,'d');// +/-
                        // if('-' == *(char*)data){
                        //     //write(STDOUT_FILENO,data,1);
                        //     int temp = mini_atoi(data, mini_strlen(data));
                        //     data = mini_itoa(temp,'d');
                        //     form.mark = '-';
                        // }
                        // if(form.indent > 1){ //pre indent
                        //     if(form.lenth >= 0){
                        //         if(form.zero == TRUE){
                        //             indent_print(form.indent-form.lenth-1);
                        //             if(form.mark =='-'){
                        //                 write(STDOUT_FILENO,&form.mark,1);
                        //             }
                        //             else if(form.mark == '+'){
                        //                 write(STDOUT_FILENO,&form.mark,1);
                        //             }
                        //             zero_print(form.indent-mini_strlen(data)-form.lenth);
                        //         }
                        //         else{
                        //             indent_print(form.indent-form.lenth);
                        //             if(form.mark =='-'){
                        //                 write(STDOUT_FILENO,&form.mark,1);
                        //             }
                        //             else if(form.mark == '+'){
                        //                 write(STDOUT_FILENO,&form.mark,1);
                        //             }
                        //         }
                        //     }
                        //     else{// No lenth 
                        //         if(form.zero == TRUE){
                        //             if(form.mark =='-'){
                        //                 write(STDOUT_FILENO,&form.mark,1);
                        //             }
                        //             else if(form.mark == '+'){
                        //                 write(STDOUT_FILENO,&form.mark,1);
                        //             }
                        //             else
                        //                 zero_print(form.indent-mini_strlen(data));
                        //             zero_print(form.indent-mini_strlen(data)-1);
                        //         }
                        //         else{//No zero, filled indent
                        //             if(form.mark != NULL){
                        //                 if(form.mark =='-'){
                        //                     write(STDOUT_FILENO,&form.mark,1);
                        //                 }
                        //                 else if(form.mark == '+'){
                        //                     write(STDOUT_FILENO,&form.mark,1);
                        //                 }
                        //             }
                        //             else
                        //                 indent_print(form.indent-mini_strlen(data));
                                    
                        //         }
                        //     }
                        // }
                        // if(form.lenth >= 0){
                        //     write(STDOUT_FILENO,data,mini_strlen(data));
                        // }
                        // else{
                        //     write(STDOUT_FILENO,data,mini_strlen(data));
                        // }
                        // if(form.indent < 1){ //post indent
                        //     indent_print(-1 * form.indent-mini_strlen(data));
                        // }
                        decimal_print(form,data);
                        buf++;
                      }
                      break;


            case 'x':
                        data=va_arg(args,int );
                        data=mini_itoa(data,'x');
                        // if(form.indent > 1){ //pre indent
                        //     if(form.lenth >= 0){
                        //         if(form.zero == TRUE)
                        //             zero_print(form.indent-form.lenth);
                        //         else
                        //             indent_print(form.indent-form.lenth);
                        //     }
                        //     else{
                        //         if(form.zero == TRUE)
                        //             zero_print(form.indent-form.lenth);
                        //         else
                        //             indent_print(form.indent-mini_strlen(data));
                        //     }
                        // }
                        // if(form.lenth > mini_strlen(data)){
                        //     zero_print(form.lenth - mini_strlen(data));
                        //     write(STDOUT_FILENO,data,mini_strlen(data));
                        // }
                        // else{
                        //     write(STDOUT_FILENO,data,mini_strlen(data));
                        // }
                        // if(form.indent < 1){//post indent
                        //     indent_print(-1 * form.indent-mini_strlen(data));
                        // }
                        hex_print(form,data);
                        buf++;
                        break;
            case 'X':
                        data=va_arg(args,int );
                        data=mini_itoa(data,'X');
                        // if(form.indent > 1){ //pre indent
                        //     if(form.lenth >= 0){
                        //         if(form.zero == TRUE)
                        //             zero_print(form.indent-form.lenth);
                        //         else
                        //             indent_print(form.indent-form.lenth);
                        //     }
                        //     else{
                        //         if(form.zero == TRUE)
                        //             zero_print(form.indent-form.lenth);
                        //         else
                        //             indent_print(form.indent-mini_strlen(data));
                        //     }
                        // }
                        // if(form.lenth > mini_strlen(data)){
                        //     zero_print(form.lenth - mini_strlen(data));
                        //     write(STDOUT_FILENO,data,mini_strlen(data));
                        // }
                        // else{
                        //     write(STDOUT_FILENO,data,mini_strlen(data));
                        // }
                        // if(form.indent < 1){//post indent
                        //     indent_print(-1 * form.indent-mini_strlen(data));
                        // }
                        hex_print(form,data);
                        buf++;
                        break;

            default:
                    if(*buf >= '1' && *buf <= '9'){
                        i=0;
                        while(*(buf+i) >= '0' && *(buf+i) <= '9')
                            i++;
                        form.indent = form.indent * mini_atoi(buf,i);
                        buf=buf+i-1;
                        *buf='%';
                    }else{
                        *buf='%';
                        write(STDOUT_FILENO,buf++,1);
                        Format temp = {POSITIVE,0,0,NEGATIVE,0,'\0'};
                        form=temp;
                    }


            }//switch state
        }//buf=='%' state
        if(form.reverse==FALSE && *buf != '%')
            write(STDOUT_FILENO,buf++,1);
    }//while state
    //printf("1.%x, 2.%x\n",buf,addr);
    //NEED FREE
    if(addr != NULL)
        free(addr);
    addr=NULL;
    va_end(args);

}

void decimal_print(Format form, void* data)
{

                        if('-' == *(char*)data){//if value is negative, 
                            int temp = mini_atoi(data, mini_strlen(data));
                            data = mini_itoa(temp,'d');
                            form.mark = '-';
                        }
                        if(form.indent > 1){ //pre indent
                            if(form.lenth >= 0){
                                if(form.zero == TRUE){
                                    indent_print(form.indent-form.lenth-1);
                                    if(form.mark =='-'){
                                        write(STDOUT_FILENO,&form.mark,1);
                                    }
                                    else if(form.mark == '+'){
                                        write(STDOUT_FILENO,&form.mark,1);
                                    }
                                    zero_print(form.indent-mini_strlen(data)-form.lenth);
                                }
                                else{
                                    indent_print(form.indent-form.lenth);
                                    if(form.mark =='-'){
                                        write(STDOUT_FILENO,&form.mark,1);
                                    }
                                    else if(form.mark == '+'){
                                        write(STDOUT_FILENO,&form.mark,1);
                                    }
                                }
                            }
                            else{//form.lenth not used
                                if(form.zero == TRUE){//fill indent
                                    if(form.mark =='-'){
                                        write(STDOUT_FILENO,&form.mark,1);
                                    }
                                    else if(form.mark == '+'){
                                        write(STDOUT_FILENO,&form.mark,1);
                                    }
                                    else{//fill zero
                                        zero_print(form.indent-mini_strlen(data));
                                    }
                                    zero_print(form.indent-mini_strlen(data)-1);
                                }
                                else{//No zero, filled indent
                                    if(form.mark != NULL){
                                        if(form.mark =='-'){
                                            write(STDOUT_FILENO,&form.mark,1);
                                        }
                                        else if(form.mark == '+'){
                                            write(STDOUT_FILENO,&form.mark,1);
                                        }
                                    }
                                    else{
                                        indent_print(form.indent-mini_strlen(data));
                                    }
                                    indent_print(form.indent-mini_strlen(data)-1);
                                }
                            }
                        }
                        if(form.lenth >= 0){
                            write(STDOUT_FILENO,data,form.lenth);
                        }
                        else{
                            write(STDOUT_FILENO,data,mini_strlen(data));
                        }
                        if(form.indent < 1){ //post indent
                            indent_print(-1 * form.indent-mini_strlen(data));
                        }

}

void hex_print(Format form, void* data)
{

 if(form.indent > 1){ //pre indent
                            if(form.lenth >= 0){
                                if(form.zero == TRUE)
                                    zero_print(form.indent-form.lenth);
                                else
                                    indent_print(form.indent-form.lenth);
                            }
                            else{
                                if(form.zero == TRUE)
                                    zero_print(form.indent-form.lenth);
                                else
                                    indent_print(form.indent-mini_strlen(data));
                            }
                        }
                        if(form.lenth > mini_strlen(data)){
                            zero_print(form.lenth - mini_strlen(data));
                            write(STDOUT_FILENO,data,mini_strlen(data));
                        }
                        else{
                            write(STDOUT_FILENO,data,mini_strlen(data));
                        }
                        if(form.indent < 1){//post indent
                            indent_print(-1 * form.indent-mini_strlen(data));
                        }



}