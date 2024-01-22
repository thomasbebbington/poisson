long int fact(int k){
	if(k==0){
		return 1;
	} else { 
		return k*fact(k-1);
	}
}

double P(int k, double l){
	return (pow(l,k))*(exp(-l))/(fact(k));
}


