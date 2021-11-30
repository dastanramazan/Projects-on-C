#include<stdio.h>
#include<stdlib.h>
#include <string.h>


int main (int argc, char *argv[]) {

    for(int i = 1; i < argc; i++) {
        FILE *fp;
        fp = fopen(argv[i], "r");

        char s = getc(fp); 
        while(s != EOF) {
            printf("%c", s);
            s = getc(fp);
        }
    }

    return 0;
