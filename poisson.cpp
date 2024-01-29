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

double* placePoints(int k){
	double* arr = (double*) malloc((k * sizeof(double)) + 1);
	arr[0] = (double) k;
	for(int i = 1; i < (k + 1); i++){
		arr[i] = ranflt(1);
	}

	return arr;
}

int main(){
	srand(time(NULL));

	int k = numOfPoint(3,ranflt(1));

	double* arr = placePoints(k);
	
	printf("%d\n", (int) arr[0]);

	for(int j = 1; j < (k + 1); j++){
		printf("%f\n", arr[j]);
	}

	free(arr);
	
}

