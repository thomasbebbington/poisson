#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <time.h>

#include <pthread.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include "poiss.h"

// Struct containing arguments for simEvents function
struct sim_args{
	double avg;
	double window;
	double* cumProbs;
	int probCount;
	int* pointCount;
	double** points;
};

// Calcualtes a point count for a time window
int numOfPoint(double l, double sig, double* cumProbs, int probCount){
	double prob = 0;
	int i = 0;		
	while(sig < cumProbs[i]){
		i++;
		if(!(i < probCount)){
			return i;
		}
	}
	return i;
}

// Places k points uniformly at random inside a time wnidow
void placePoints(int k, double window, double* arr){
	if(k == 0){
		return;
	}
	for(int i = 0; i < k; i++){
		arr[i] = window * ranflt(1);
	}
}

// Simulates points inside a time window
void* simEvents(void* args){
	sim_args arguments = *((sim_args*) args);
	
	*arguments.pointCount = numOfPoint(arguments.avg, ranflt(1), arguments.cumProbs, arguments.probCount);
	*arguments.points = (double*) malloc(sizeof(double) * *arguments.pointCount);

	placePoints(*arguments.pointCount, arguments.window, *arguments.points);
	free(args);

	return 0;
}

// Sorts points by time to be printed out in order
void sortEvents(double* arr, int length){
	if(length < 2){
		return;
	}
	qsort((void*) arr, length, sizeof(double), compDouble);
}

// Prints out points as an event in time
void printEvents(double* arr, double window, int pointCount, double* time){
	sortEvents(arr, pointCount);

	double t = 0;
	int current = 0;
	double interval = 0.05f;
	
	if(pointCount == 0){
		goto done;
	}

	while(t <= window){
		while(arr[current] < t){
			std::cout << "Event: " << (*time + arr[current]) << std::endl;
			current++;
			if(current == pointCount){
				goto done;
			}
		}
		
		t += interval;
		usleep(interval * 1000000);
	}
done:
	while(t <= window){
		t += interval;
		usleep(interval * 1000000);
	}
	*time = *time + window;
}

void run(int* currPointCount, double* currPoints, double* cumProbs, int probCount, double avg, double window, int windows){
	double* t = (double*) malloc(sizeof(double));
	*t = 0;

	int iterations = 0;
	std::cout << "Starting" << std::endl;
	
	int* nextPointCount;
	double* nextPoints;
	if(windows>1){
		//Simulate next points
		struct sim_args* args = (sim_args*) malloc(sizeof(sim_args));
		args->avg = avg;
		args->window = window;
		args->cumProbs = cumProbs;
		args->probCount = probCount;

		nextPointCount = (int*) malloc(sizeof(int));
		args->pointCount = nextPointCount;
		args->points = &nextPoints;
		simEvents(args);
	}

	while(iterations < windows){
		printEvents(currPoints, window, *currPointCount, t);

		free(currPoints);
		currPointCount = nextPointCount;
		currPoints = nextPoints;

		if(iterations < windows - 2){
			// Simulates more points if needed
			pthread_t simThread;
			
			struct sim_args* args = (sim_args*) malloc(sizeof(sim_args));
			args->avg = avg;
			args->window = window;
			args->cumProbs = cumProbs;
			args->probCount = probCount;

			args->pointCount = nextPointCount;
			args->points = &nextPoints;

			pthread_create(&simThread, NULL, &simEvents, (void*) args);
		}

		iterations++;		
	}
	if(windows > 1){
		free(nextPointCount);

	}
	free(t);	
	std::cout << "Done" << std::endl;
}

int main(){
	// Seed random generator
	srand(time(NULL));

	// Simulation parameters
	double window = 1.0f;
	double avg = 12.0f;
	int windows = 2;
	
	int probCount = probcount(avg);
	double* cumProbs = (double*) malloc(sizeof(double) * probCount);
	cumprobs(avg, probCount, cumProbs);

	int* currPointCount = (int*) malloc(sizeof(int));
	double* currPoints;
	struct sim_args* args = (sim_args*) malloc(sizeof(sim_args));
	args->avg = avg;
	args->window = window;
	args->cumProbs = cumProbs;
	args->probCount = probCount;


	args->pointCount = currPointCount;
	args->points = &currPoints;
	simEvents(args);


	run(currPointCount, currPoints, cumProbs, probCount, avg, window, windows);

	free(cumProbs);
	free(currPointCount);
		
	return 0;
}

