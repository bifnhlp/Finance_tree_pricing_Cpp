#include "MC_European_option.h"

#define PI 3.14159265359
#define E 2.71828182846

using namespace std;

double normal()
{
	double x[2] = {double(rand())/RAND_MAX, double(rand())/RAND_MAX};
	return sqrt(-2*log(x[0]))*cos(2*PI*x[1]);
}

MC_European_option::MC_European_option(double r, double sigma, double S_0, double K, double T, int N, int M)
{
	this->r = r;
	this->sigma = sigma;
	this->S_0 = S_0;
	this->K = K;
	this->T = T;
	this->N = N;
	this->M = M;

	this->call_price = nan("");
	this->put_price = nan("");
}

double MC_European_option::get_call_price()
{
	return call_price;
}

double MC_European_option::get_put_price()
{
	return put_price;
}

void MC_European_option::MC_simulation()
{
	double dt = T/N;
	double S;
	call_price = 0;
	put_price = 0;
	for (int i=0; i<M; i++)
	{
		S = S_0;
		for (int k=0; k<N; k++)
		{
			S *= 1+r*dt+normal()*sigma*sqrt(dt);
		} 
		call_price += 1.0/M*max(0.0, S-K);
		put_price += 1.0/M*max(0.0, K-S);
	}
	call_price *= exp(-r*T);
	put_price *= exp(-r*T);

	return;
}




