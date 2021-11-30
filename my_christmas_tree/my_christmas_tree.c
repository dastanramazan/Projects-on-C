#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SPACE ' '

int main(int ac, char **av) 
{
    /* Get the integer value of the number using atoi */
    
    int l = atoi(av[1]); 
    int m = 1; 
    
    int i; 
    for(i = 1; i < l; i++)
    {
        m += 2 * (i/2) + 4; // increment m by 2* (i/2) + 4 = 5
    }
    m += 2 * (l - 1) + 6; // increment m by 

   
    for(int i = 0, n_layer = 1; i < l; i++)
    {
        int j_layer = n_layer;
       
        for(int j = 0; j < i + 4; j++)  
        {
            int left = (m - j_layer) / 2; 
            int right = left + j_layer;
            
            for(int k = 0; k < m; k++) 
            {   
                
                if(k < left) // || k >= right
                { 
                    putchar(SPACE);
                }
                    
                else if (k < right) {
                         
                        putchar('*');
                   
                        }
       
            }
            
            putchar('\n');
            j_layer +=2;             
        }   
            n_layer +=2 * ((i + 1) / 2) + 4; 
    }

// Tree trunk

    for(int i = 0; i < l; i++) 
    {
        for(int j = 0; j < m; j++)
        {
            int tree_trunk_left = (m - l + 1) / 2;

            if( j < tree_trunk_left ) //|| j >= tree_trunk_left + l
            {
                putchar(SPACE);
            }
            else if(j < tree_trunk_left + l) {
                    putchar('|');
                 } 
        }
        putchar('\n');       
    }

    return 0;
}





