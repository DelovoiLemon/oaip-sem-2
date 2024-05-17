#include<stdio.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"
typedef double (*func)(int);
double y_rec(int n) { return (n > 0) ? 1 / (n + y_rec(n - 1)) : 0.5; }
double y_lin(int n) 
{
	double res = 1./2.;
	for(int i = 1; i <= n; i++) res = 1. / (i + res);
	return res;
}
void print_res(func y, int n) { printf("n = %i y(n) = %lf\n", n, y(n)); }
int main() 
{
	int n; printf("Enter n: ");
	if(scanf("%i", &n) < 1) { printf(NONUMMSG); exit(1); }
	puts("Recursive:"); print_res(y_rec, n);
	puts("Linear:"); print_res(y_lin, n);
	return 0;
}
