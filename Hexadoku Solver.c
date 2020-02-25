#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 16

const char set[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int check_row(char grid[N][N], int row, char c){
	for(int col = 0; col < 16; col++){
		if(grid[row][col] == c){
			return 1;
		}
	}
	return 0;
}

int check_col(char grid[N][N], int col, char c){
	for(int row = 0; row < 16; row++){
		if(grid[row][col] == c){
			return 1;
		}
	}
	return 0;
}

int check_square(char grid[N][N], int start_row, int start_col, char c){
	for(int row = 0; row < 4; row++){
		for(int col = 0; col < 4; col++){
			if(grid[row+start_row][col+start_col] == c)
				return 1;
		}
	}
	return 0;
}

int valid_entry(char grid[N][N], int row, int col, char c){
	if(check_row(grid, row, c) == 0 && check_col(grid, col, c) == 0 && check_square(grid, row - row % 4 , col - col % 4, c) == 0)
		return 1;
	else
		return 0;
}

void find_other_helper(char grid[N][N], int row, int col){
	for(int i = 0; i < N; i++){
		if(check_col(grid, col, set[i]) == 0){
			grid[row][col] = set[i];
			break;
		}
	}
}

void find_other(char grid[N][N], int row, int col){
	char temp;
	for(int i = 0; i < N; i++){
		if(check_row(grid, row, set[i]) == 0){
			grid[row][col] = set[i];
			temp = set[i];
			break;
		}
	}

	for(int row = 0; row < N; row++){
		if(grid[row][col] == temp){
			find_other_helper(grid, row, col);
		}
	}
}

void solve_grid(char grid[N][N]){
	//go through entire grid
	for(int row = 0; row < N; row++){
		for(int col = 0; col < N; col++){
			//if item at given position is empty test out possible options
			if(grid[row][col] == '-'){
				for(int i = 0; i < N; i++){
					char c = set[i];
					if(valid_entry(grid, row, col, c)){
						grid[row][col] = c;
						return;
					}
				}
			}
		}
	}
}

int main(int argc, char** argv)
{
	FILE *file = fopen(argv[1], "r");

	char c;
	char grid[N][N];

	int count = 0;
	int flag = 0;

	//initialize grid
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf(file, "%c ", &c);
			grid[i][j] = c;
		}
	}

	//count empty spots
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if(grid[i][j] == '-'){
				count++;
			}
		}
	}

	for(int i = 0; i < count; i++){
		solve_grid(grid);
	}

	//check if it is a valid preset grid
	for(int row = 0; row < N; row++){
		for(int col = 0; col < N; col++){
			int k = col+1;
			while(k < N-1){
				if(grid[row][col] == grid[row][k]){
					flag = 1;
				}
				k++;
			}
		}
	}

	//fix wrong values
	for(int row = 0; row < N; row++){
		for(int col = 0; col < N; col++){
			if(grid[row][col] == '-'){
				find_other(grid, row, col);
			}
		}
	}

	//display solved grid
	if(!flag){
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if(j != N-1)
					printf("%c\t", grid[i][j]);
				else
					printf("%c", grid[i][j]);
			}
			if(i != N){
				printf("\n");
			}
		}
	} else {
		printf("no-solution\n");
	}

	return 0;
}



