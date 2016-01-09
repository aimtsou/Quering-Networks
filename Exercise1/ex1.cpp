#include <iostream>
using namespace std;

#define R 3
#define M 6

/*double d1[M][R] = {
	{1.5, 3.4, 6},      // network time
    {2000, 3500, 7000}, // thought time
    {22, 56, 77},       // server cpu
    {25, 62, 70},       // server disk
    {30, 66, 94},       // db cpu
    {22, 46, 73},       // db disk
};*/

double d2[M][R] = {
	{1.5, 3.4, 6},      // network time
    {2000, 3500, 7000}, // thought time
    {22, 56, 77},       // server cpu
    {25, 62, 70},       // server disk
    {15, 33, 47},       // db cpu
    {11, 23.5, 36.5},   // db disk
};

double n[M][R], r[M][R], l[R], ro[M][R], T[R];
// categories
int N1[R] = {35, 72, 18};
// new categories
int N2[R] = {49, 91, 26};
// approximation value
double approx = 0.001;

double abs(double a, double b) {
	if (a > b) 
		return a - b;
	else 
		return b - a;
}

int calc(int *N, double d[M][R]) {
	int i, j;
	double temp, sum_l[R], sum_r[M];
	int flag = 1;
	
	// Initializing N
	for (i = 0; i < M; i++) 
		for (j = 0; j < R; j++) 
			n[i][j] = (double)N[j]/M;

	while (flag) { 
		flag = 0;
		// Calculating waiting time for network and thought
		for (i = 0; i < R; i++) {
            r[0][i] = d[0][i];
            sum_l[i] = r[0][i];
            T[i] = r[0][i];
			r[1][i] = d[1][i];
            sum_l[i] += r[1][i];
            T[i] += r[1][i];
        }

        // Calculating waiting time for the rest
        for (i = 0; i < M; i++) 
        	sum_r[i]=0;
        for (i = 0; i < M; i++)
            for (j = 0; j < R; j++)
                sum_r[i] += n[i][j];
        for (i = 2; i < (M-1); i++)
            for (j = 0; j < R; j++) {
                r[i][j] = d[i][j] * (1 + ((N[j]-1)/N[j]) * n[i][j] + sum_r[i] - n[i][j]);
                T[j] += r[i][j];
                sum_l[j] += r[i][j];
            }

		// Calculating λ_j
		for (j = 0; j < R; j++)
			l[j] = N[j] / sum_l[j];

		// Check approximation as to stop algorithm
		for (i = 0; i < M; i++)
			for (j = 0; j < R; j++) {
				ro[i][j] = l[j] * d[i][j];
				temp = l[j] * r[i][j];
				
				if((abs(temp, n[i][j])) > approx) {
					flag = 1;
				}
				n[i][j] = temp;
			}
	}

	for (i = 0; i < R; i++) cout << "l="<< l[i] <<", T="<<T[i]<< "\n";
	cout<<"\n";
	for (i = 0; i < M; i++) 
		for (j = 0; j < R; j++) 
			cout << "i=" << i << ", j=" << j <<", r="<< ro[i][j] <<"\n";
}

int main() {
	//calc(N1, d1);
	//calc(N2, d1);
	// results get rounded in a weird way commenting out d1 with d2
	calc(N2, d2);

	return 0;
}
