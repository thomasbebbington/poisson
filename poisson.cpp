#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <time.h>

#include <pthread.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include "poiss.h"


int numOfPoint(double l, double p){
	int i = -1;
	long double cumprob = 0;
	long double prob = 0;
	printf("Sig: %f\n", p);

	while(cumprob < p){
		i++;
		prob = P(i, l);
		cumprob += prob;
		printf("%d cum: %Lf, prob: %Lf\n", i, cumprob, prob);

	}
	return i;
}

double* placePoints(int k, double window){
	double* arr = (double*) malloc((k * sizeof(double)) + 1);
	arr[0] = (double) k;
	for(int i = 1; i < (k + 1); i++){
		arr[i] = window * ranflt(1);
	}

	return arr;
}

double* simEvents(double avg, double window){
	int k = numOfPoint(avg, ranflt(1));

	double* arr = placePoints(k, window);

	return arr;
}

void printEvents(double *arr, double window){
	double t = 0.0f;
	int current = 1;
	double interval = 0.05f;
	
	while(t <= window){
		while(arr[current] < t){
			printf("Event %f\n", arr[current]);
			current += 1;
			if (current > ((int) arr[0])) {
				printf("Exiting...\n");
				return;
			}

		}
		t += interval;
		usleep(interval * 1000000);
	}
}

int compDouble(const void* fst, const void* snd){
	double arg1 = *(double*) fst;
	double arg2 = *(double*) snd;

	double diff = arg1 - arg2;

	if (diff < 0) return -1;
	if (diff > 0) return 1;
	return 0;
}

void sortEvents(double* arr){
qsort((void*) &arr[1], (int) arr[0], sizeof(double), compDouble);
}

int main(){
	srand(time(NULL));
	double window = 5.0f;
	double avg = 30.0f;
	/*
	double* currentPoints = simEvents(window);
	double* nextPoints;
	
	pthread_t printThread;
	pthread_t simThread;

	pthread_create(&printThread, NULL, printEvents, NULL);
	*/
	int probCount = probcount(avg);

	double* cumProbs = (double*) malloc(sizeof(double) * probCount);
	cumprobs(avg, probCount, cumProbs);

	
	for(int i = 0; i < probCount; i++){
		std::cout << i << " " << cumProbs[i] << std::endl;

	}
	
	free(cumProbs);
}

