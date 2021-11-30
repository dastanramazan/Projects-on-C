#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define TRUE  1
#define FALSE 0
typedef char bool;

int my_printf(char *fmt, ...);
int args_cases(char* fmt, va_list ap, int* i);
int my_strlen(char* s);
char* my_itoa(int d, int base);
char* itoa_unsign_int(unsigned int d, int base);
char* itoa_unsign_long(unsigned long d, int base);

/*----- my printf function---------*/


int my_printf(char* fmt, ...) {
  va_list ap;
  
  bool    flag_spotted  = FALSE;
  int     size           = 0;
  

  va_start(ap, fmt); 
  for(int i = 0; fmt[i] !='\0'; i++)
  {
    if (flag_spotted) {
      size += args_cases(fmt, ap, &i);
      flag_spotted = FALSE;
    }
    else if (fmt[i] == '%') 
    {
      flag_spotted = TRUE;
    }
    else {
      write(1, &fmt[i], 1);
            size++;
    }
    
  }
  va_end(ap);
  return size;
}

/*----- Cases---------*/
int args_cases(char* fmt, va_list ap, int* i)
{
    int d;
    unsigned int o, x, u;
    void* p;
    char c;
    char *s;
    int size = 0;
    char* res;
    switch (fmt[*i++])
    {
        case 'd': /*The int (or appropriate variant) argument is converted to signed decimal (d)*/
            d = va_arg(ap, int);
            if (d < 0)
            {
                write(1, "-", 1);
                d = -d;
            }
            s = my_itoa(d, 10);
            size += write(1, s, my_strlen(s));
            free(s);
            break;
        case 'o': /*The int (or appropriate variant) argument is converted to unsigned octal (o)*/
            o = va_arg(ap, unsigned int);
            s = itoa_unsign_int(o, 8);
            size += write(1, s, my_strlen(s));
            free(s);
            break;
        case 'u': /* The int (or appropriate variant) argument is converted to unsigned decimal (u)*/
            u = va_arg(ap, unsigned int);
            s = itoa_unsign_int(u, 10);
            size += write(1, s, my_strlen(s));
            free(s);
            break;
        case 'x': /*The int (or appropriate variant) argument is converted to unsigned hexadecimal (x)*/
            x = va_arg(ap, unsigned int);
            s = itoa_unsign_int(x, 16);
            size += write(1, s, my_strlen(s));
            free(s);
            break;
        case 'c':  /* char  The int argument is converted to an unsigned char*/
            /* need a cast here since va_arg only takes fully promoted types */
            c = (char) va_arg(ap, int);
            write(1, &c, 1);
            size++;
            break;
        case 's':  /*char * argument is expected to be a pointer to an array of character type (pointer to a string)*/
        s = va_arg(ap, char *);
        if(s == NULL) 
        {
            res = "(null)";
            size += write(1, res, 6);
        } else {
            size += write(1, s, my_strlen(s));
               }
        break;
        case 'p': /*The void * pointer argument is printed in hexadecimal*/
            p = va_arg(ap, void*);
            unsigned long longVal = (unsigned long)p;
            s = itoa_unsign_long(longVal, 16);
            size += write(1, "0x", 2);
            size += write(1, s, my_strlen(s));
            free(s);
            break;
    }
    return size;
}

/*-----my_strlen----*/

int my_strlen(char* s)
{
    int index = 0;
    while (s[index] != '\0') 
    {
	    index++;                    
    }
  return index;
}


/*-----convert decimals----*/
char* my_itoa(int d, int base)
{
    int tmp;
    char* s = malloc(sizeof(char) * 13);
    int i = 0;
    if (d == 0)
    {
        s[0] = '0';
        s[1] = '\0';
        return s;
    }
    for ( ; d > 0; i++)
    {
        tmp = d % base;
        d = d / base;
        if (tmp < 10)
        {
            s[i] = '0' + tmp;
        }
        else
        {
            s[i] = 'a' + tmp - 10;
        }
    }
    s[i] = '\0';
    int len = my_strlen(s);
    i--;
    for ( ; i >= len / 2; i--)
    {
        char c = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = c;
    }
	return s;
}

/*-----convert unsigned int----*/
char* itoa_unsign_int(unsigned int d, int base)
{
    int tmp;
    char* s = malloc(sizeof(char) * 13);
    int i = 0;
    if (d == 0)
    {
        s[0] = '0';
        s[1] = '\0';
        return s;
    }
    for ( ; d > 0; i++)
    {
        tmp = d % base;
        d = d / base;
        if (tmp < 10)
        {
            s[i] = '0' + tmp;
        }
        else
        {
            s[i] = 'a' + tmp - 10;
        }
    }
    s[i] = '\0';
    int len = my_strlen(s);
    i--;
    for ( ; i >= len / 2; i--)
    {
        char c = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = c;
    }
	return s;
}

/*-----convert unsigned long----*/
char* itoa_unsign_long(unsigned long d, int base)
{
    int tmp;
    char* s = malloc(sizeof(char) * 15);
    int i = 0;
    if (d == 0)
    {
        s[0] = '0';
        s[1] = '\0';
        return s;
    }
    for ( ; d > 0; i++)
    {
        tmp = d % base;
        d = d / base;
        if (tmp < 10)
        {
            s[i] = '0' + tmp;
        }
        else
        {
            s[i] = 'a' + tmp - 10;
        }
    }
    s[i] = '\0';
    int len = strlen(s);
    i--;
    for ( ; i >= len / 2; i--)
    {
        char c = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = c;
    }
	return s;
}


// int main()
// {

//     printf("%d\n", my_printf("Hello world!\n")); // The return size should be equal to printf(). Expected result: 13

//     printf("%d\n", my_printf("%c!\n", 'H')); //Expected result: H! The return size should be equal to printf(). Expected result: 3
    
//     printf("%d\n", my_printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o')); // Expected result: Hello! The return size should be equal to printf(). Expected result: 7
    
//     printf("%d\n", my_printf("Hello %s!\n", "QWASAR.IO")); // Expected result: Hello QWASAR.IO! The return size should be equal to printf(). Expected result: 17

//     printf("%d\n", my_printf("Hello %s %s!\n", "Mr", "Gaetan")); // Expected result: Hello Mr Gaetan! Expected result: 17

//     printf("%d\n", my_printf("NULL STRING %s!\n", (char*)NULL)); // Expected result: NULL STRING (null)! (NULL or similar are accepted) equal to printf().

//     printf("%d\n", my_printf("%u!\n", 1337)); // Expected result: 1337! equal to printf() Expected result: 6

//     printf("%d\n", my_printf("%d - %d - %d!\n", 2048, 0, -1337)); // Expected result: 2048 - 0 - -1337!  equal to printf() Expected result: 18

//     printf("%d\n", my_printf("%o!\n", 100)); //Expected result: 144! equal to printf() Expected result: 5

//     printf("%d\n", my_printf("%u!\n", 1337)); // Expected result: 1337! equal to printf() Expected result: 6

//     printf("%d\n", my_printf("%x!\n", 14)); //Expected result: e! (or E!) equal to printf() Expected result:3

//      char* a = "asdfa";
//     printf("%d\n", my_printf("%p!\n", a)); //Expected result: 0x7ffee3b00688 (an address) equal to printf() Expected result:16


//     return 0;
// }