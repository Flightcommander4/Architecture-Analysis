//Matthew Calandrella - Programming Exercise #4 - ECE 432: Computer Architecture

//Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

//Defining Outer Loops and Vector Size
#define size 128
#define outerLoops 6E7



int main(){
	
	//Initializing for User Choice, Vector Size and Processor, as well as start and end times for the Timers
	int processor;
	double start;
	double end;
	double* a;
	double* x;
	double* y;
	double* z;
	long long i, k, j;
	double AOpTime;
	 
	double ExecTimeTotal;
	double VectorExecTime;
	double FLOPS;
	
	//Credentials
	printf("Matthew Calandrella - PE#4 ECE 432\n\n");
		
		
	//Which Processor are we running on?
	printf("Which Processor are we Running On?\n\n");
	printf("1 - Intel XeonE5-2690 (Sandy Bridge)\n");
	printf("2 - Intel Xeon 4210 (Cascade Lake)\n");
	printf("3 - AMD EPYC 7452 (Rome)\n\n");
		
	scanf("%d", &processor);
	printf("\n");

		
		
	//If the user chooses an invalid processor, the following error occurs
	if(processor > 3){
		printf("Error, Invalid\n");
		return 0;
	}
		
	printf("\n");
 
		
	//Allocating Memory for the Vectors
	a = (double*)malloc(size * sizeof(double));
	x = (double*)malloc(size * sizeof(double));
	y = (double*)malloc(size * sizeof(double));
	z = (double*)malloc(size * sizeof(double));

			
	//Filling up the Vectors with Random Values, to the specified size
	for(i=0; i < size; i++){
		x[i] = rand() % 1000000;
		y[i] = rand() % 1000000;
		a[i] = rand() % 1000000;
		z[i] = rand() % 1000000;
	}
	
	//Start Total Execution Time Timer
	start = omp_get_wtime();
	
	//Outer Loop
	for(k=0; k < outerLoops; k++){
		
		//Performing the Vector Operation	
		for(i=0; i < size; i++){
				
			z[i] = ((a[i] * x[i]) + y[i]);
			
		}
		
	}
	
	//End Total Execution Time Timer
	end = omp_get_wtime();
	
	
	
	
	//Benchmarks
	
	//Benchmark i-ii
	if(processor == 1){
		printf("Processor Being Tested: Intel Xeon E5-2690 (Sandy Bridge)\n");
		printf("Processor Clock Frequency: 3.8 GHz\n");
	}
	else if(processor == 2){
		printf("Processor Being Tested: Intel Xeon 4210 (Cascade Lake)\n");
		printf("Processor Clock Frequency: 3.2 GHz\n");
	}
	else if(processor == 3){
		printf("Processor Being Tested: AMD EPYC 7452 (Rome)\n");
		printf("Processor Clock Frequency: 3.35 GHz\n");
	}
	
	//Benchmark iii
	printf("Expression being tested: z[i] = (a[i] * x[i]) + y[i])\n");
	
	//Benchmark iv
	printf("Number of Elements per Vector: %d\n", size);
	
	//Benchmark v
	printf("Number of Outer Resolution Loops: %E\n", outerLoops);
	
	//Benchmark vi
	printf("Total Elapsed Execution Time for the Benchmark: %f Seconds\n", (ExecTimeTotal = (end - start)));
	
	//Benchmark vii
	printf("Execution Time per Vector: %E Seconds\n", (VectorExecTime = ExecTimeTotal / outerLoops));
	
	//Benchmark viii
	printf("Execution Time per Arithmetic Operation: %E Seconds\n", AOpTime = (VectorExecTime / size) / 2);
	
	//Benchmark ix
	printf("Sustained DP Floating Point Operations: %e FLOPS\n", FLOPS = 1.0/AOpTime);
	
	//Benchmark x-xi
	if(processor == 1){
		printf("The Number of CPU Clock Cycles per DP FLOP: %f CPO\n", (3.8E9/FLOPS));
		printf("The Number of DP FLOPs per Clock Cycle: %f OPC\n", (FLOPS/3.8E9));
	}
	if(processor == 2){
		printf("The Number of CPU Clock Cycles per DP FLOP: %f CPO\n", (3200000000 * (end - start)) / (outerLoops * size) / 2);
		printf("The Number of DP FLOPs per Clock Cycle: %f CPO\n", ((1 / (((end - start) / (outerLoops * size))) / 2)) / 3200000000);
	}
	if(processor == 3){
		printf("The Number of CPU Clock Cycles per DP FLOP: %f CPO\n", (3350000000 * (end - start)) / (outerLoops * size) / 2);
		printf("The Number of DP FLOPs per Clock Cycle: %f CPO\n", ((1 / (((end - start) / (outerLoops * size))) / 2)) / 3350000000);
	}
	
	//Benchmark xii
	printf("Estimated L1D to/from the CPU Data BW (Bytes/sec) to sustain DAXPY (Ops/sec): %e\n", (16.0 * FLOPS));
	printf("Estimated L1D to the CPU to the Data BW (Bytes/sec) to sustain DAXPY (Ops/sec): %e\n", (FLOPS*16.0 * (3.0 / 4.0)));
	printf("Estimated L1D from the CPU to the Data BW (Bytes/sec) to sustain DAXPY (Ops/sec): %e\n", (FLOPS*16.0 * (1.0 / 4.0)));
	
	//Benchmark xiii
	printf("Estimated Average Memory Access Time (AMAT) in Sec / Byte: %e\n\n", ( 1.0/(FLOPS * 16.0)) );
	

	//Freeing the Memory from the Vectors
	free(a);
	free(x);
	free(y);
	free(z);
	return 0;
}
