long long int fact(int k){
	if(k==0){
		return 1;
	} else { 
		return k*fact(k-1);
	}
}

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

void cumprobs(double l, int probCount, double* cumProbs){
	int j = probCount - 1;
	double prob = 0;
	std::cout << j << "\n";
	
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

double ranflt(double max){
	return (max * ((double) rand()))/((double) (RAND_MAX));
}
