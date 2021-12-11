//Matthew Calandrella - Programming Exercise #2 - ECE 432: Computer Architecture

//Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){
	
	//Initializing for User Choice, Vector Size and Processor, as well as start and end times for the Timers
	int choice = 0;
	int size = 0;
	int processor = 0;
	double start;
	double end;
	
	//Credentials
	printf("Matthew Calandrella - PE#2 ECE 432\n\n");
		
		
	//Which Processor are we running on?
	printf("Which Processor are we Running On?\n\n");
	printf("1 - Intel XeonE5-2690 (Sandy Bridge)\n");
	printf("2 - Intel Xeon 4210 (Cascade Lake)\n");
	printf("3 - AMD EPYC 7452 (Rome)\n\n");
		
	scanf("%d", &processor);
	printf("\n");
		
	//Asking User for Vector Size
	printf("Select a Vector Size: \n\n");
		
	//Getting Vector Size
	scanf("%d", &size);
	printf("\n");
		
		
	//If the user chooses an invalid processor, the following error occurs
	if(processor > 3){
		printf("Error, Invalid\n");
		return 0;
	}
		
	//If the user chooses an invalid choice, the following error occurs
	if(choice > 3){
		printf("Error, Invalid\n");
		return 0;
	}
		
	printf("\n");
		
	//If the user initializes the array as a value outside of the specified bounds, the following error occurs
	if( size < 1 || size > 1000){
		printf("Error, Invalid Size\n");
		return 0;
	}
		
		
	//Initializing the Vectors
	int i = 0;
	int k = 0;
	double* a;
	double* x;
	double* y;
	double* z;
		
	//Allocating Memory for the Vectors
	a = (double*)malloc(size * sizeof(double));
	x = (double*)malloc(size * sizeof(double));
	y = (double*)malloc(size * sizeof(double));
	z = (double*)malloc(size * sizeof(double));

			
	//Filling up the Vectors with Random Values, to the specified size
	srand(time(0));
	for(i; i < size; i++){
		x[i] = rand() % 1000000;
		y[i] = rand() % 1000000;
		a[i] = rand() % 1000000;
	}
	
	//Defining the Number of Outer Loops
	long long int outerLoops = 6000000;
	
	//Start Total Execution Time Timer
	start = omp_get_wtime();
	
	//Outer Loop
	for(k; k < outerLoops; k++){
		
		int j = 0;
		
		//Performing the Vector Operation	
		for(j; j < size; j++){
				
			z[j] = ((a[i] * x[i]) + y[i]);
			
		}
		
	}
	
	//End Total Execution Time Timer
	end = omp_get_wtime();
	
	//Freeing the Memory from the Vectors
	free(x);
	free(y);
	free(z);
	
	
	//Benchmarks
	
	//Benchmark a - b
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
	
	//Benchmark c
	printf("Expression being tested: z[i] = (a[i] * x[i]) + y[i])\n");
	
	//Benchmark d
	printf("Compiler Flags: -O0 , -fopenmp , -mavx , -no-vec\n");
	
	//Benchmark e
	printf("Number of Elements per Vector: %d\n", size);
	
	//Benchmark f
	printf("Number of Outer Resolution Loops: %d\n", outerLoops);
	
	//Benchmark g
	printf("Total Elapsed Execution Time for the Benchmark: %f Seconds\n", end - start);
	
	//Benchmark h
	printf("Execution Time per Vector: %E Seconds\n", ((end - start) / outerLoops));
	
	//Benchmark i
	printf("Execution Time per Arithmetic Operation: %E Seconds\n", (((end - start) / outerLoops) / size) / 2);
	
	//Benchmark j
	printf("Sustained DP Floating Point Operations: %f FLOPS\n", ((outerLoops * size) / (end - start)));
	
	//Benchmark k
	if(processor == 1){
		printf("The Number of CPU Clock Cycles per DP FLOP: %f CPO\n", (3800000000 * (end - start)) / (outerLoops * size));
	}
	if(processor == 2){
		printf("The Number of CPU Clock Cycles per DP FLOP: %f CPO\n", (3200000000 * (end - start)) / (outerLoops * size));
	}
	if(processor == 3){
		printf("The Number of CPU Clock Cycles per DP FLOP: %f CPO\n", (3350000000 * (end - start)) / (outerLoops * size));
	}
	
	//Benchmark m
	printf("Estimated L1D to/from the CPU Data BW (Bytes/sec) to sustain DAXPY (Ops/sec): %f\n", (16.0 * ((outerLoops * size) / (end - start))));
	printf("Estimated L1D to the CPU to the Data BW (Bytes/sec) to sustain DAXPY (Ops/sec): %f\n", (((outerLoops * size) / (end - start)) * (16.0 * (3.0 / 4.0))));
	printf("Estimated L1D from the CPU to the Data BW (Bytes/sec) to sustain DAXPY (Ops/sec): %f\n\n", (((outerLoops * size) / (end - start)) * (16.0 * (1.0 / 4.0))));
}
