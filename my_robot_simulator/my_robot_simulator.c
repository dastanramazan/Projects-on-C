// X and Y with last coordinates of the robot.
// DIRECTION will be the orientation (north, west, south, east)

// Robot always starts in 0, 0 facing north.

// Going south will increase Y.
// Going west will decrease X.

// The grid is unlimited, positions can be negative.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* my_robot_simulator(char* param)
{   int x = 0;
    int y = 0;
    int direction = 0;
    char* bearing[4];
    bearing[0] = "north";
    bearing[1] = "south";
    bearing[2] = "west";
    bearing[3] = "east";
    char* answer = malloc(40*sizeof(char));

    if (strlen(param)==0) {
        sprintf( answer, "{x: %d, y: %d, bearing: '%s'}", x,y,bearing[0]);
    } 

    int k;
    for (k=0; k<strlen(param); k++) {
         if (param[k] != 'A' || param[k] != 'L' || param[k] != 'R') {
             break;
            return 0;
        }
    }
    int i;
    for (i=0; i < strlen(param); i++) {

        if (param[i] == 'R') {
            direction = direction +90;
        }
        else if (param[i]=='L') {
            direction = direction -90;
        }
        else if (param[i]=='A') {
            if (direction%360==90 || direction%360==-270){
                x++;
            }
            else if (direction%360==180 || direction%360==-180){
                y++;
            }
            else if (direction%360==0) {
                y--;
            }
            else if (direction%360==270 || direction%360==-90) {
                x--;
            }
        }

        if (direction%360==0) {
            sprintf( answer, "{x: %d, y: %d, bearing: '%s'}", x,y,bearing[0]);
        }
        else if (direction%360==90 || direction%360==-270) {
            sprintf( answer,"{x: %d, y: %d, bearing: '%s'}", x, y, bearing[3]);
        }
        else if (direction%360==180 || direction%360==-180) {
            sprintf(answer, "{x: %d, y: %d, bearing: '%s'}", x,y,bearing[1]);
        }
        else if (direction%360==270 || direction%360==-90) {
            sprintf(answer, "{x: %d, y: %d, bearing: '%s'}", x,y,bearing[2]);
        } 

    }
    return answer;

}

//  int main () {
//     printf("%s", my_robot_simulator("RAALALL"));
//     return 0; 
//  }



