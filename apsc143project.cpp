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


//Prints out pacman and the ghosts
//Has pacman eat the dots
//changes the colors
void printpacman(char** pacman, int pacmanX, int pacmanY, int firstGhostX, int firstGhostY, int secondGhostX, int secondGhostY){
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if(j == firstGhostX && i == firstGhostY){
                colourChange(13);
                printf("G  ");
            }
            else if(j == secondGhostX && i == secondGhostY){
                colourChange(13);
                printf("G  ");
            }
            else if(j == pacmanX && i == pacmanY){
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

//Checks to see if you won the game by checking if all the dots are eaten
int winCheck(int score){
    if(score == 54){
        return 1;
    }
    return 0;
}

//Checks to see if you lost the game by checking if the pac man is touching a ghost
int loseCheck(int pacmanX, int pacmanY, int firstGhostX, int firstGhostY, int secondGhostX, int secondGhostY){
    if( (pacmanX == firstGhostX && pacmanY == firstGhostY)  )
    {
        return 1;
    }else if(pacmanX == secondGhostX && pacmanY == secondGhostY){
        return 1;
    }
    return 0;
}

// Sees if there is a wall beside the pacman depending on the keyboard input
int isWall(char** map, int xMove, int yMove, char d){
    if( d == UP && map[yMove-1][xMove] != 'W'){
        return 1;
    }
    else if( d == DOWN && map[yMove+1][xMove] != 'W'){
        return 1;
    }
    else if( d == LEFT && map[yMove][xMove-1] != 'W'){
        return 1;
    }
    else if( d == RIGHT && map[yMove][xMove+1] != 'W'){
        return 1;
    }

    return 0;
}

// Scans any clear lines of view until the wall to see if it can see pacman
char ghostScan1(char** map, int ghostX, int ghostY, int pacmanX, int pacmanY) {
    if (pacmanY == ghostY && ghostX > pacmanX) {
        //Looks to its left
        for (int i = ghostX; i > 0; i--) {
            if (map[ghostY][i] == 'W') {
                break;
            } else if (pacmanX == i) {
                return 'a';
            }
        }
    }
    else if (pacmanY == ghostY && ghostX < pacmanX) {
        //Looks to its right
        for (int i = ghostX; i < 10; i++) {
            if (map[ghostY][i] == 'W') {
                break;
            } else if (pacmanX == i) {
                return 'd';
            }
        }
    }
    else if (pacmanX == ghostX && ghostY > pacmanY) {
        //Looks to the top
        for (int i = ghostY; i > 0; i--) {
            if (map[i][ghostX] == 'W') {
                break;
            } else if (pacmanY == i) {
                return 'w';
            }
        }
    }
    else if (pacmanX == ghostX && ghostY < pacmanY) {
        //Looks to the bottom
        for (int i = ghostY; i < 10; i++) {
            if (map[i][ghostX] == 'W') {
                break;
            } else if (pacmanY == i) {
                return 's';
            }
        }
    }
    //If can't find pacman it will switch to a random direction and look. Looks for walls before it does this to see if it can keep moving where it is going.
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
    // Does the same thing as the first ghost scan but now with the second ghost
    char ghostScan2(char **map, int ghostX, int ghostY, int pacmanX, int pacmanY) {
        if (pacmanY == ghostY && ghostX > pacmanX) {
            // Looks to its left
            for (int i = ghostX; i > 0; i--) {
                if (map[ghostY][i] == 'W') {
                    break;
                } else if (pacmanX == i) {
                    return 'a';
                }
            }
        }
        else if (pacmanY == ghostY && ghostX < pacmanX) {
            //Looks to its right
            for (int i = ghostX; i < 10; i++) {
                if (map[ghostY][i] == 'W') {
                    break;
                } else if (pacmanX == i) {
                    return 'd';
                }
            }
        }
        else if (pacmanX == ghostX && ghostY > pacmanY) {
            //Looks to the top
            for (int i = ghostY; i > 0; i--) {
                if (map[i][ghostX] == 'W') {
                    break;
                } else if (pacmanY == i) {
                    return 'w';
                }
            }
        }
        else if (pacmanX == ghostX && ghostY < pacmanY) {
            //Looks to the bottom
            for (int i = ghostY; i < 10; i++) {
                if (map[i][ghostX] == 'W') {
                    break;
                } else if (pacmanY == i) {
                    return 's';
                }
            }
        }
        //If can't find pacman it will switch to a random direction and look. Looks for walls before it does this to see if it can keep moving where it is going.
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

        // Opening the given file
        FILE *fptr = fopen("C:\\Users\\lazar\\CLionProjects\\EngProj\\map.txt", "r");
        if (fptr == NULL) {
            printf("File not found.\n");
        } else {
            // Allocating memory
            char **pacman = (char **) malloc(11 * sizeof(char *));

            for (int i = 0; i < 11; i++) {
                // Making pointer array to get elements from the text file
                pacman[i] = (char *) malloc(11 * sizeof(char));

                // Making the array
                fscanf(fptr, "%c  %c  %c  %c  %c  %c  %c  %c  %c  %c  %c\n", &pacman[i][0], &pacman[i][1],
                       &pacman[i][2],
                       &pacman[i][3], &pacman[i][4], &pacman[i][5], &pacman[i][6], &pacman[i][7], &pacman[i][8],
                       &pacman[i][9], &pacman[i][10]);
            }


            pacman[1][1] = '.';
            pacman[9][9] = '.';
            pacman[5][5] = ' ';

            // Assigning variables values
            int pacmanX = 5;
            int pacmanY = 5;
            int firstGhostX = 1;
            int firstGhostY = 1;
            int secondGhostX = 9;
            int secondGhostY = 9;
            int points = 0;
            char firstGhostMove = 's';
            char secondGhostMove = 'w';
            char userInput;

            //Printing all the characters on the map
            printpacman(pacman, pacmanX, pacmanY, firstGhostX, firstGhostY, secondGhostX, secondGhostY);

            // Taking the user input from the keyboard
            while (true) {
                userInput = getch();
                // What happens if user clicks 'w'
                if (userInput == UP){
                    if(isWall(pacman, pacmanX, pacmanY, UP) == 1) {
                        pacmanY -= 1;
                        if (pacman[pacmanY][pacmanX] == '.') {
                            pacman[pacmanY][pacmanX] = ' ';
                            points += 1;
                        }
                    }
                }
                // What happens if user clicks 'a'
                else if (userInput == LEFT){
                    if (isWall(pacman, pacmanX, pacmanY, LEFT) == 1) {
                        pacmanX -= 1;
                        if (pacman[pacmanY][pacmanX] == '.') {
                            pacman[pacmanY][pacmanX] = ' ';
                            points += 1;
                        }
                    }
                }
                // What happens if user clicks 's'
                else if (userInput == DOWN){
                    if(isWall(pacman, pacmanX, pacmanY, DOWN) == 1) {
                        pacmanY += 1;
                        if (pacman[pacmanY][pacmanX] == '.') {
                            pacman[pacmanY][pacmanX] = ' ';
                            points += 1;
                        }
                    }
                }
                // What happens if user clicks 'd'
                else if (userInput == RIGHT){
                    if(isWall(pacman, pacmanX, pacmanY, RIGHT) == 1) {
                        pacmanX += 1;
                        if (pacman[pacmanY][pacmanX] == '.') {
                            pacman[pacmanY][pacmanX] = ' ';
                            points += 1;
                        }
                    }
                }
                // what happens if you lose the game
                if (loseCheck(pacmanX, pacmanY, firstGhostX, firstGhostY, secondGhostX, secondGhostY) == 1) {
                    system("CLS");
                    printpacman(pacman, pacmanX, pacmanY, firstGhostX, firstGhostY, secondGhostX, secondGhostY);
                    printf("Sorry, you lose. Press any key to exit the game\n");
                    system("pause");
                    break;
                }

                //Defining variables based on the ghostScan functions
                firstGhostMove = ghostScan1(pacman, firstGhostX, firstGhostY, pacmanX, pacmanY);
                secondGhostMove = ghostScan2(pacman, secondGhostX, secondGhostY, pacmanX, pacmanY);

                //Changing the first ghosts x and y coordinates based on where they are going
                if (firstGhostMove == UP) {
                    firstGhostY -= 1;
                } else if (firstGhostMove == LEFT) {
                    firstGhostX -= 1;
                } else if (firstGhostMove == DOWN) {
                    firstGhostY += 1;
                } else if (firstGhostMove == RIGHT) {
                    firstGhostX += 1;
                }
                //Changing the second ghosts x and y coordinates based on where they are going
                if (secondGhostMove == UP) {
                    secondGhostY -= 1;
                } else if (secondGhostMove == LEFT) {
                    secondGhostX -= 1;
                } else if (secondGhostMove == DOWN) {
                    secondGhostY += 1;
                } else if (secondGhostMove == RIGHT) {
                    secondGhostX += 1;
                }

                //Printing all the characters
                system("CLS");
                printpacman(pacman, pacmanX, pacmanY, firstGhostX, firstGhostY, secondGhostX, secondGhostY);

                // Checking if the game is won
                if (winCheck(points) == 1) {
                    printf("Congratulations! You win! Press any key to exit the game\n");
                    system("pause");
                    break;
                }
                // Checking if the game is lost
                if (loseCheck(pacmanX, pacmanY, firstGhostX, firstGhostY, secondGhostX, secondGhostY) == 1) {
                    printf("Sorry, you lose. Press any key to exit the game\n");
                    system("pause");
                    break;
                }

            }
        }
    }
// Yay the code is done!!