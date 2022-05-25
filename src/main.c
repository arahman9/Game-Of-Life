#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "life.h"

/* Be sure to read life.h and the other given source files to understand
 * what they provide and how they fit together.  You don't have to
 * understand all of the code, but you should understand how to call
 * parse_life() and clearterm().
 */

/* This is where your program will start.  You should make sure that it
 * is capable of accepting either one or two arguments; the first
 * argument (which is required) is a starting state in one of the Life
 * formats supported by parse_life(), and the second (which is optional)
 * is a number of generations to run before printing output and stopping.
 *
 * The autograder will always call your program with two arguments.  The
 * one-argument format (as described in the handout) is for your own
 * benefit!
 declaration of ‘grid’ as multidimensional array must have bounds for all dimensions except the first
 */
/*char **grid = parse_life(argv[1]);
	char altGrid[2][GRIDY][GRIDX];
	int gen = atoi(argv[2]);
	int curGen = 1;
	populateGrid(altGrid,grid);
	calcNext(altGrid, 0);

	if(gen == 0 || gen == 1){
		printGrid(altGrid, gen);
	}
	else{
		while(curGen != gen){
			curGen++;
			int n = curGen % 2;
			if(n == 1){
				n = 0; 
			}
			else{
				n = 1;
			}
			calcNext(altGrid, n);
		}
	}
	printGrid(altGrid, (gen % 2));	
    return 0;*/
int amntLife(char grid[][GRIDY][GRIDX], int i, int j, int n);

bool isAlive(int lives, bool alive);

void calcNext(char grid[][GRIDY][GRIDX], int n);

void populateGrid(char altGrid[][GRIDY][GRIDX],char **grid);

void printGrid(char altGrid[][GRIDY][GRIDX], int n);

int main(int argc, char *argv[])
{
	char **grid = parse_life(argv[1]);
	char altGrid[2][GRIDY][GRIDX];
	int gen = atoi(argv[2]);
	int curGen = 0;
	populateGrid(altGrid,grid);
	while(curGen != gen){
		curGen++;
		int n = curGen % 2;
		if(n == 1){
			n = 0; 
		}
		else{
			n = 1;
		}
		calcNext(altGrid, n);
	}
	printGrid(altGrid, (gen % 2));	
    return 0;
}

void printGrid(char altGrid[][GRIDY][GRIDX], int n){
	for(int i = 0; i < GRIDY; i++){
		for(int j = 0; j < GRIDX; j++){
			printf("%c", altGrid[n][i][j]);
		}
		printf("\n");
	}
}
void populateGrid(char altGrid[][GRIDY][GRIDX],char **grid){
	for(int y = 0; y < GRIDY; y++){
		for(int x = 0; x < GRIDX; x++){
			altGrid[0][y][x] = grid[y][x];
			altGrid[1][y][x] = grid[y][x];
		}
	}
}
void calcNext(char grid[][GRIDY][GRIDX], int n){
	int z;
	if(n == 1){
		z = 0; 
	}
	else{
		z = 1;
	}
	for(int i = 0; i < GRIDY; i++){
		for(int j = 0; j < GRIDX; j++){
			int lives = amntLife(grid,i,j,n);
			if(grid[n][i][j] == LIVE){
				if(isAlive(lives,true)){
					grid[z][i][j] = LIVE;
				}
				else{
					grid[z][i][j] = DEAD;
				}
			}
			else{if(grid[n][i][j] == DEAD){
				if(isAlive(lives,false)){
					grid[z][i][j] = LIVE;
				}
				else{
					grid[z][i][j] = DEAD;
				}
			}
			}
		}
	}
}

int amntLife(char grid[][GRIDY][GRIDX], int i, int j, int n){
	int yIndex = i;
	int xIndex = j;

	int life = 0;

	if((yIndex - 1 > 0) && grid[n][yIndex - 1][xIndex] == 'X'){life += 1;}
	if((yIndex + 1 < GRIDY) && grid[n][yIndex + 1][xIndex] == 'X'){life += 1;}
	if((xIndex - 1 > 0)  && grid[n][yIndex][xIndex - 1] == 'X'){life += 1;}
	if((xIndex + 1 < GRIDX) && grid[n][yIndex][xIndex + 1] == 'X'){life += 1;}
	if((yIndex + 1 < GRIDY) && (xIndex + 1 < GRIDX) && grid[n][yIndex + 1][xIndex + 1] == 'X'){life += 1;}
	if((yIndex - 1 > 0) && (xIndex - 1 > 0) && grid[n][yIndex - 1][xIndex - 1] == 'X'){life += 1;}
	if((yIndex + 1 < GRIDY) && (xIndex - 1 > 0) && grid[n][yIndex + 1][xIndex - 1] == 'X'){life += 1;}
	if((yIndex - 1 > 0) && (xIndex + 1 < GRIDX) && grid[n][yIndex - 1][xIndex + 1] == 'X'){life += 1;}

	return life;

}
/*alive && (lives < 2 || lives > 3)*/
bool isAlive(int lives, bool alive){
	if((alive && (lives == 2 || lives == 3)) || (!alive && lives == 3)){return true;}
	return false;
}