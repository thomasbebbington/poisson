// Unused due to potential overflows with large enough k
long long int fact(int k){
	if(k==0){
		return 1;
	} else { 
		return k*fact(k-1);
	}
}

// Calculated the probability of k events hapening from a poisson distribution with mean l
double P(int k, double l){
	double el = exp(-l);
	double pel = (pow(l,k))*el;
	
	int curr = k;
	double r = pel;


	if(k == 0){
		return pel;
	}

	while(curr > 1){
		r = (double) r/((double) curr);
		curr--;
	}

	return r;
}

// Calculates the number of probabilities to be stored
int probcount(double l){
	int j = ceil(l);
	double prob = 0;
	do{
		j++;
		prob = P(j, l);

	}while (prob > 0.001);
	j--;
	return j;
}

// Calculates cumulative probabilities from a poisson distribution with mean l
void cumprobs(double l, int probCount, double* cumProbs){
	int j = probCount - 1;
	double prob = 0;

	cumProbs[j] = P(j,l);	
	do{
		prob = P(j,l);
		cumProbs[j-1] = cumProbs[j] + prob;
		j--;
	}while (prob > 0.001 && j > 0);
	while(j > 0){
		cumProbs[j-1] = 1;
		j--;
	}
}

// Calculates a pseudorandom float
double ranflt(double max){
	return (max * ((double) rand()))/((double) (RAND_MAX));
}

// Double comparison function used in sorting events
int compDouble(const void* fst, const void* snd){
	double arg1 = *(double*) fst;
	double arg2 = *(double*) snd;

	double diff = arg1 - arg2;

	if (diff < 0) return -1;
	if (diff > 0) return 1;
	return 0;
}

