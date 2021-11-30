
#include <stdlib.h>
#include <stdio.h>

void my_square (int x, int y) {

    for (int i = 1; i <= x; i++) { 
        for (int j = 1; j <= y; j++) { 
           if (i == 1 || i == x) { 
               if (j == 1 || j == y){ 
               printf("o");
               }
           
           else {
               printf("-"); 
           }
           }
           else if (j == 1 || j == y) { 
               printf("|"); 
           }
          else {
              printf(" "); 
          }
        }
        printf("\n");
    }
    
}

int main(int ac, char **av) {
    if (ac != 3) { 
     return 0;
    }
    int rows = atoi(av[1]);
    int columns = atoi(av[2]);
    
    my_square(rows, columns);
    
   
return 0;
}