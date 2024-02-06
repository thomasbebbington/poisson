#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <time.h>

#include <pthread.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include "poiss.h"


int numOfPoint(double l, double sig, double* cumProbs){
	double prob = 0;
	printf("Sig: %f\n", sig);
	int i = 0;	
	
	while(sig < cumProbs[i]){
		i++;
	}
	return i;
}

double* placePoints(int k, double window){
	double* arr = (double*) malloc((k * sizeof(double)));
	for(int i = 0; i < k; i++){
		arr[i] = window * ranflt(1);
	}

	return arr;
}

double* simEvents(double avg, double window, double* cumProbs, int* pointCount){
	*pointCount = numOfPoint(avg, ranflt(1), cumProbs);

	double* arr = placePoints(*pointCount, window);

	return arr;
}

void sortEvents(double* arr, int length){
	qsort((void*) arr, length, sizeof(double), compDouble);
}

void printEvents(double *arr, double window, int pointCount){
	sortEvents(arr, pointCount);

	double t = 0.0f;
	int current = 0;
	double interval = 0.05f;
	
	while(t <= window){
		while(arr[current] < t){
			std::cout << "Event " << arr[current] << std::endl;
			current++;
			if(current == pointCount){
				return;
			}
		}
		t += interval;
		usleep(interval * 1000000);
	}
}




int main(){
	srand(time(NULL));
	double window = 5.0f;
	double avg = 12.0f;
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
	
	for(int n = 0; n < probCount; n++){
		std::cout << n << " " << cumProbs[n] << std::endl;

	}
	
	int* pointCount = (int*) malloc(sizeof(int));
	double* points = simEvents(avg, window, cumProbs, pointCount);

	std::cout << *pointCount << std::endl;

	for(int n = 0; n < *pointCount; n++){
		std::cout << points[n] << std::endl;
	}	

	std::cout << std::endl;

	printEvents(points, window, *pointCount);

	free(cumProbs);
	free(pointCount);
	free(points);
}

