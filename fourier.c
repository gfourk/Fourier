
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct complex{
	double real;
	double imag;
};

struct complex w;
double same,co,si,re,im;
int i,j;

void fft(double* input_signal,int length,int s,struct complex* output_signal){
	if(length == 1){
		output_signal[0].real = input_signal[0];
		output_signal[0].imag = 0;
		return;
	}

	int half_length = (length/2);
	fft(&input_signal[0],half_length,2*s,output_signal);
	fft(&input_signal[0+s],half_length,2*s,&output_signal[half_length]);

	same = (-2*M_PI/length);
	for(i = 0; i<half_length; ++i){
		co = cos(i*same);
		si = sin(i*same);
		re = output_signal[i+half_length].real;
		im = output_signal[i+half_length].imag;
		output_signal[i+half_length].real = output_signal[i].real - re*co + im*si;
		output_signal[i+half_length].imag = output_signal[i].imag - re*si - im*co;
		output_signal[i].real = output_signal[i].real + re*co - im*si;
		output_signal[i].imag = output_signal[i].imag + re*si + im*co;
	}
}
#define N 8
int main(void){
	double* input;
	struct complex* output;
	output = malloc(sizeof(struct complex)*N);
	input = malloc(sizeof(double)*N);
	srand(11);
	for(j = 0; j<N; ++j){
		input[j] = rand()%256;
		printf("input[%d]=%lf\n",j,input[j]);
	}
	printf("start = %ld\n",clock());
	fft(input,N,1,output);
	printf("end = %ld\n",clock());	
	for(j = 0; j<N; ++j){
		printf("input[%d]=%lf,%lf\n",j,output[j].real,output[j].imag);
	}
	free(input);
	free(output);
	return 0;
}
