#include<stdio.h>
#include<stdlib.h>

int main()
{
	char character_grid[9][9];
	char character_grid_updated[9][9];
	char list_of_words[16][9];
	int i, j, n, h, l, k = 0;

	for (i = 0; i < 8; i++) {
		scanf(" %s", character_grid[i]);
	}
	scanf(" %d", &n);
	for (i = 0; i < n; i++) {
		scanf(" %s", list_of_words[i]);
	}
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			character_grid_updated[i][j] = character_grid[i][j];
		}
	}
	for (h = 0, k = 0; h < n; h++) {
		for (i = 0; i < 8; i++) {
			for (j = 7; j >= 0; j--) {
				if (list_of_words[h][k] == character_grid[i][j]) {
					k++;
					i++;
					if (list_of_words[h][k] == NULL) {
						for (l = 0; list_of_words[h][l] != NULL; l++) {
							character_grid_updated[i - l - 1][j + l] = '#';
						}
					}
				}
				else k = 0;
			}
		}
	}
	for (h = 0, k = 0; h < n; h++) {
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (list_of_words[h][k] == character_grid[i][j]) {
					k++;
					if (list_of_words[h][k] == NULL) {
						for (l = 0; list_of_words[h][l] != NULL; l++) {
							character_grid_updated[i][j - l] = '#';
						}
					}
				}
				else {
					k = 0;
				}
			}
		}
	}
	for (h = 0, k = 0; h < n; h++) {
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (list_of_words[h][k] == character_grid[j][i]) {
					k++;
					if (list_of_words[h][k] == NULL) {
						for (l = 0; list_of_words[h][l] != NULL; l++) {
							character_grid_updated[j - l][i] = '#';
						}
					}
				}
				else k = 0;
			}
		}
	}
	for (h = 0, k = 0; h < n; h++) {
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (list_of_words[h][k] == character_grid[i][j]) {
					k++;
					i++;
					if (list_of_words[h][k] == NULL) {
						for (l = 0; list_of_words[h][l] != NULL; l++) {
							character_grid_updated[i - l - 1][j - l] = '#';
						}
					}
				}
				else k = 0;
			}
		}
	}
	for (i = 0; i < n; i++) {
		printf("%s \n", list_of_words[i]);
	}

	for (i = 0; i < 8; i++) {
		printf("%s \n", character_grid_updated[i]);
	}
	return 0;
}