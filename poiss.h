long long int fact(int k){
	if(k==0){
		return 1;
	} else { 
		return k*fact(k-1);
	}
}

long double P(int k, double l){
	long double el = exp(-l);
	long double pel = (pow(l,k))*el;
	
	int curr = k;
	long double r = pel;


	if(k == 0){
		return pel;
	}

	while(curr > 1){
		r = (double) r/((double) curr);
		curr--;
	}

	return r;
}

double ranflt(double max){
	return (max * ((double) rand()))/((double) (RAND_MAX));
}
