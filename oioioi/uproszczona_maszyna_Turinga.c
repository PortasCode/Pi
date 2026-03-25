#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 100

// Z0, S0 -> Z0, S0, L
// Z1, S0 -> Z0, S1, R
// Z0, S1 -> Z1, S0, -
// Z1, S1 -> Z1, S1, stop

enum states { S0, S1 };
enum symbols { Z0, Z1 };
enum symbols memory[N];

bool step(int *position, enum states *state, const int n) {
	switch (*state) {
		case S0:
			if (memory[*position]==Z0){
				*position = (*position > 0) ? *position - 1 : n -1;	
			}
			else {
				memory[*position] = Z0;
				*state = S1;
				*position = (*position == n - 1) ? 0 : *position + 1;
			}	
			break;

		case S1:
			if (memory[*position] == Z0){
				memory[*position] = Z1;
				*state = S0;	
			}
			else {
				return false;
			}
			break;
	}
	return true;
}

int main(void) {
	unsigned int seed;
	int n, position;
	enum states state = S0;
	scanf("%u %d %d", &seed, &n, &position);
	srand(seed);
	for (int i = 0; i < N; ++i) {
		int s = rand() % 2;
        	if (s == 0) memory[i] = Z0;
       		else memory[i] = Z1;
    	}	
	int count=0;
	while (step(&position,&state,n)==true){
		count++;
	}
	printf("%d %d\n", count, position);
	return 0;
}
