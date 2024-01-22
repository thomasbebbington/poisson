#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <time.h>
#include "poiss.h"

int numOfPoint(double l, double p){
	int i = -1;
	double cumprob = 0;
	double prob = 0;

	while(cumprob < p){
		i++;
		prob = P(i, l);
		cumprob += prob;
	}
	return i;
}

int main(){
	srand(time(NULL));

	printf("%d\n", numOfPoint(3,((double) rand()/(double) RAND_MAX)));
	
}

