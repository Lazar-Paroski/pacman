// APSC 143 Engineering Programming Project Starter Code
// Feel free to change anything about this file, but do not remove "#include "colours.h".

// Make sure to include all relevant libraries
#include <stdio.h>
#include "colours.h"
#include <stdlib.h>
#include <time.h>


// You don't need to use these, but they help make your code look more organized
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'


// Below are the required functions for this program, but you will need to create your own as well.
// Make sure to specify the required parameters, if any.



void printpacman(char** pacman, int pX, int pY, int g1X, int g1Y, int g2X, int g2Y){
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if(j == g1X && i == g1Y){
                colourChange(13);
                printf("G  ");
            }
            else if(j == g2X && i == g2Y){
                colourChange(13);
                printf("G  ");
            }
            else if(j == pX && i == pY){
                colourChange(6);
                printf("P  ");
            }
            else if(pacman[i][j] == '.'){
                colourChange(15);
                printf("%c  ", pacman[i][j]);
            }
            else{
                colourChange(1);
                printf("%c  ", pacman[i][j]);
            }
        }
        printf("\n");
    }
}

int winCheck(int score){
    if(score == 54){
        return 1;
    }
    return 0;
}
int loseCheck(int pacmanX, int pacmanY, int ghost1X, int ghost1Y, int ghost2X, int ghost2Y){
    if( (pacmanX == ghost1X && pacmanY == ghost1Y) || (pacmanX == ghost2X && pacmanY == ghost2Y) )
    {
        return 1;
    }
    return 0;
}

//checking if pacman will run into a wall
//note: I added surrounding walls to the pacman.txt file, so I only check if it is a wall and don't check for out of bounds
int isWall(char** map, int xMove, int yMove, char d){

    if( d == UP && map[yMove-1][xMove] != 'W' )
    {
        return 1;
    }
    else if( d == LEFT && map[yMove][xMove-1] != 'W' )
    {
        return 1;
    }
    else if( d == DOWN && map[yMove+1][xMove] != 'W'  )
    {
        return 1;
    }
    else if( d == RIGHT && map[yMove][xMove+1] != 'W'  )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char ghostScan1(char** map, int ghostX, int ghostY, int pacmanX, int pacmanY) {
    //checks if ghost and are on the same row and scans its left side for pacman until a wall
    if (pacmanY == ghostY && ghostX > pacmanX) {
        //Checks left
        for (int i = ghostX; i > 0; i--) {
            if (map[ghostY][i] == 'W') {
                break;
            } else if (pacmanX == i) {
                return 'a';
            }
        }
    }
        //Checks if ghost are on same row and scans its right side for pacman until a wall
    else if (pacmanY == ghostY && ghostX < pacmanX) {
        //Checks right
        for (int i = ghostX; i < 10; i++) {
            if (map[ghostY][i] == 'W') {
                break;
            } else if (pacmanX == i) {
                return 'd';
            }
        }
    }
        //Checks if ghost are on the same column and scans above for pacman until a wall
    else if (pacmanX == ghostX && ghostY > pacmanY) {
        //Checks above
        for (int i = ghostY; i > 0; i--) {
            if (map[i][ghostX] == 'W') {
                break;
            } else if (pacmanY == i) {
                return 'w';
            }
        }
    }
        //Checks if ghost are on the same column and scans below for pacman until a wall
    else if (pacmanX == ghostX && ghostY < pacmanY) {
        //Checks below
        for (int i = ghostY; i < 10; i++) {
            if (map[i][ghostX] == 'W') {
                break;
            } else if (pacmanY == i) {
                return 's';
            }
        }
    }
        //If it does not see pacman, it checks for walls and sees if its still able to move in that direction. If not, it will switch to random direction and check again.
    else {
        int num;
        srand(time(NULL));
        while (1) {
            num = rand() % 4;
            if (num == 0 && isWall(map, ghostX, ghostY, 'w') == 1) {
                return 'w';
            } else if (num == 1 && isWall(map, ghostX, ghostY, 'a') == 1) {
                return 'a';
            } else if (num == 2 && isWall(map, ghostX, ghostY, 's') == 1) {
                return 's';
            } else if (num == 3 && isWall(map, ghostX, ghostY, 'd') == 1) {
                return 'd';
            }
        }
    }
}
    char ghostScan2(char **map, int ghostX, int ghostY, int pacmanX, int pacmanY) {
        //checks if ghost and are on the same row and scans its left side for pacman until a wall
        if (pacmanY == ghostY && ghostX > pacmanX) {
            //Checks left
            for (int i = ghostX; i > 0; i--) {
                if (map[ghostY][i] == 'W') {
                    break;
                } else if (pacmanX == i) {
                    return 'a';
                }
            }
        }
            //Checks if ghost are on same row and scans its right side for pacman until a wall
        else if (pacmanY == ghostY && ghostX < pacmanX) {
            //Checks right
            for (int i = ghostX; i < 10; i++) {
                if (map[ghostY][i] == 'W') {
                    break;
                } else if (pacmanX == i) {
                    return 'd';
                }
            }
        }
            //Checks if ghost are on the same column and scans above for pacman until a wall
        else if (pacmanX == ghostX && ghostY > pacmanY) {
            //Checks above
            for (int i = ghostY; i > 0; i--) {
                if (map[i][ghostX] == 'W') {
                    break;
                } else if (pacmanY == i) {
                    return 'w';
                }
            }
        }
            //Checks if ghost are on the same column and scans below for pacman until a wall
        else if (pacmanX == ghostX && ghostY < pacmanY) {
            //Checks below
            for (int i = ghostY; i < 10; i++) {
                if (map[i][ghostX] == 'W') {
                    break;
                } else if (pacmanY == i) {
                    return 's';
                }
            }
        }
            //If it does not see pacman, it checks for walls and sees if its still able to move in that direction. If not, it will switch to random direction and check again.
        else {
            int num;
            srand(time(NULL));
            while (1) {
                num = rand() % 4;
                if (num == 1 && isWall(map, ghostX, ghostY, 'w') == 1) {
                    return 'w';
                } else if (num == 0 && isWall(map, ghostX, ghostY, 'a') == 1) {
                    return 'a';
                } else if (num == 3 && isWall(map, ghostX, ghostY, 's') == 1) {
                    return 's';
                } else if (num == 2 && isWall(map, ghostX, ghostY, 'd') == 1) {
                    return 'd';
                }
            }
        }
}
    int main() {

        FILE *fptr = fopen("C:\\Users\\lazar\\CLionProjects\\EngProj\\map.txt", "r");
        if (fptr == NULL) {
            printf("File not found.\n");
        } else {
            char **pacman = (char **) malloc(11 * sizeof(char *));

            for (int i = 0; i < 11; i++) {

                //Setup column of pointer array & grab all elements from text file:
                pacman[i] = (char *) malloc(11 * sizeof(char));

                fscanf(fptr, "%c  %c  %c  %c  %c  %c  %c  %c  %c  %c  %c\n", &pacman[i][0], &pacman[i][1],
                       &pacman[i][2],
                       &pacman[i][3], &pacman[i][4], &pacman[i][5], &pacman[i][6], &pacman[i][7], &pacman[i][8],
                       &pacman[i][9], &pacman[i][10]);
            }


            pacman[1][1] = '.';
            pacman[9][9] = '.';
            pacman[5][5] = ' ';

            int pacmanX = 5;
            int pacmanY = 5;
            int ghost1X = 1;
            int ghost1Y = 1;
            int ghost2X = 9;
            int ghost2Y = 9;
            int points = 0;
            char g1Move = 's';
            char g2Move = 'w';
            char userInput;

            printpacman(pacman, pacmanX, pacmanY, ghost1X, ghost1Y, ghost2X, ghost2Y);

            while (true) {
                userInput = getch();
                if (userInput == UP && isWall(pacman, pacmanX, pacmanY, UP) == 1) {
                    pacmanY -= 1;
                    if (pacman[pacmanY][pacmanX] == '.') {
                        pacman[pacmanY][pacmanX] = ' ';
                        points += 1;
                    }
                } else if (userInput == LEFT && isWall(pacman, pacmanX, pacmanY, LEFT) == 1) {
                    pacmanX -= 1;
                    if (pacman[pacmanY][pacmanX] == '.') {
                        pacman[pacmanY][pacmanX] = ' ';
                        points += 1;
                    }
                } else if (userInput == DOWN && isWall(pacman, pacmanX, pacmanY, DOWN) == 1) {
                    pacmanY += 1;
                    if (pacman[pacmanY][pacmanX] == '.') {
                        pacman[pacmanY][pacmanX] = ' ';
                        points += 1;
                    }
                } else if (userInput == RIGHT && isWall(pacman, pacmanX, pacmanY, RIGHT) == 1) {
                    pacmanX += 1;
                    if (pacman[pacmanY][pacmanX] == '.') {
                        pacman[pacmanY][pacmanX] = ' ';
                        points += 1;
                    }
                }

                if (loseCheck(pacmanX, pacmanY, ghost1X, ghost1Y, ghost2X, ghost2Y) == 1) {
                    system("CLS");
                    printpacman(pacman, pacmanX, pacmanY, ghost1X, ghost1Y, ghost2X, ghost2Y);
                    printf("Sorry, you lose. Press any key to exit the game\n");
                    system("pause");
                    break;
                }

                //ghost movement returned based on ghostScan()
                g1Move = ghostScan1(pacman, ghost1X, ghost1Y, pacmanX, pacmanY);
                g2Move = ghostScan2(pacman, ghost2X, ghost2Y, pacmanX, pacmanY);

                //Statements for moving ghost and keeping track of points:
                //first ghost:
                if (g1Move == UP) {
                    ghost1Y -= 1;
                } else if (g1Move == LEFT) {
                    ghost1X -= 1;
                } else if (g1Move == DOWN) {
                    ghost1Y += 1;
                } else if (g1Move == RIGHT) {
                    ghost1X += 1;
                }
                //second ghost
                if (g2Move == UP) {
                    ghost2Y -= 1;
                } else if (g2Move == LEFT) {
                    ghost2X -= 1;
                } else if (g2Move == DOWN) {
                    ghost2Y += 1;
                } else if (g2Move == RIGHT) {
                    ghost2X += 1;
                }

                system("CLS");
                printpacman(pacman, pacmanX, pacmanY, ghost1X, ghost1Y, ghost2X, ghost2Y);

                if (winCheck(points) == 1) {
                    printf("Congratulations! You win! Press any key to exit the game\n");
                    system("pause");
                    break;
                }
                if (loseCheck(pacmanX, pacmanY, ghost1X, ghost1Y, ghost2X, ghost2Y) == 1) {
                    printf("Sorry, you lose. Press any key to exit the game\n");
                    system("pause");
                    break;
                }

            }
        }
    }