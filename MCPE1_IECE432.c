//Matthew Calandrella - Programming Exercise #1 - ECE 432: Computer Architecture

//Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

//Main Function
int main() {
	
	//Initializing for User Choice, Vector Size and Processor, as well as start and end times for the Timers
	int choice;
	int size;
	int processor;
	double start;
	double end;
	double arithmeticStart;
	double arithmeticEnd;
	double vectorStart;
	double vectorEnd;
	
	//Credentials
	printf("Matthew Calandrella - PE#1 ECE 432\n\n");
	
	
	//Which Processor are we running on?
	printf("Which Processor are we Running On?\n\n");
	printf("1 - Intel XeonE5-2690 (Sandy Bridge)\n");
	printf("2 - Intel Xeon 4210 (Cascade Lake)\n");
	printf("3 - AMD EPYC 7452 (Rome)\n\n");
	
	scanf("%d", &processor);
	printf("\n");
	
	//Choices presented to the User
	printf("Select a Vector Operation: \n\n");
	printf("1 - ADD \n");
	printf("2 - MULTIPLY \n");
	printf("3 - DIVIDE \n\n");
	
	//Getting User Choice
	scanf("%d", &choice);
	printf("\n");
	
	//Asking User for Vector Size
	printf("Select a Vector Size: \n\n");
	
	//Getting Vector Size
	scanf("%d", &size);
	printf("\n");
	
	//Start Total Execution Time Timer
	start = omp_get_wtime();
	
	
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
	float* x;
	float* y;
	float* z;
	
	//Allocating Memory for the Vectors
	x = (float*)malloc(size * sizeof(float));
	y = (float*)malloc(size * sizeof(float));
	z = (float*)malloc(size * sizeof(float));


	//Starting the Timer for Populating the Vectors
	vectorStart = omp_get_wtime();
		
	//Filling up the Vectors with Random Values, to the specified size
	srand(time(0));
	for(i; i < size; i++){
		x[i] = rand() % 1000000;
		y[i] = rand() % 1000000;
	}
		
	//Ending the Timer for Populating the Vectors
	vectorEnd = omp_get_wtime();
	
	//Defining the Number of Outer Loops
	long long int outerLoops = 6000000;
		
	for(k; k < outerLoops; k++){
			
		//Code Runs when User Choice is 1, which is Addition
		if(choice == 1){
			
			int j = 0;
			int loop = 0;
			int loop2 = 0;
			int loop3 = 0;
			
			//Starting the Timer for the Arithmetic
			arithmeticStart = omp_get_wtime();
			
			
			//Adding the values together, and putting them in the new Vector
			for(j; j < size; j++){
				
				z[j] = x[j] + y[j];
			
			}
			
			//Ending the Timer for the Arithmetic
			arithmeticEnd = omp_get_wtime();
			
			/*
			//Printing out the Vectors, for testing purposes
			printf("Vector X: ");
			
			for(loop; loop < size; loop++){
				printf(" %f ", x[loop]);
			}
			
			printf("\n");
			
			printf("Vector Y: ");
			
			for(loop2; loop2 < size; loop2++){
				printf(" %f ", y[loop2]);
			}
			
			printf("\n\n");
			
			printf("Resulting Vector Z: ");
			
			for(loop3; loop3 < size; loop3++){
				printf(" %f ", z[loop3]);
			}
			*/
			
		}
		
		//Code Runs when User Choice is 2, which is Multiplication
		else if(choice == 2){
			
			int j = 0;
			int loop = 0;
			int loop2 = 0;
			int loop3 = 0;
			
			//Starting the Timer for the Arithmetic
			arithmeticStart = omp_get_wtime();
			
			//Multiplying the values, and putting them in the new Vector
			for(j; j < size; j++){
				
				z[j] = x[j] * y[j];
			
			}
			
			//Ending the Timer for the Arithmetic
			arithmeticEnd = omp_get_wtime();
			
			/*
			//Printing out the Vectors, for testing purposes
			printf("Vector X: ");
			
			for(loop; loop < size; loop++){
				printf(" %f ", x[loop]);
			}
			
			printf("\n");
			
			printf("Vector Y: ");
			
			for(loop2; loop2 < size; loop2++){
				printf(" %f ", y[loop2]);
			}
			
			printf("\n\n");
			
			printf("Resulting Vector Z: ");
			
			for(loop3; loop3 < size; loop3++){
				printf(" %f ", z[loop3]);
			}
			*/
			
			
		}
		
		//Code Runs when User Choice is 3, which is Divison
		else if(choice == 3){
			
			int j = 0;
			int loop = 0;
			int loop2 = 0;
			int loop3 = 0;
			
			//Starting the Timer for the Arithmetic
			arithmeticStart = omp_get_wtime();
			
			//Dividing the values, and putting them in the new Vector
			for(j; j < size; j++){
				
				z[j] = x[j] / y[j];
			
			}
			
			//Ending the Timer for the Arithmetic
			arithmeticEnd = omp_get_wtime();
			
			/*
			//Printing out the Vectors, for testing purposes
			printf("Vector X: ");
			
			for(loop; loop < size; loop++){
				printf(" %f ", x[loop]);
			}
			
			printf("\n");
			
			printf("Vector Y: ");
			
			for(loop2; loop2 < size; loop2++){
				printf(" %f ", y[loop2]);
			}
			
			printf("\n\n");
			
			printf("Resulting Vector Z: ");
			
			for(loop3; loop3 < size; loop3++){
				printf(" %f ", z[loop3]);
			}
			*/
			
			
		}
	}
	
	end = omp_get_wtime();
	
	//Freeing the Memory from the Vectors
	free(x);
	free(y);
	free(z);
	
	
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
	if(choice == 1){
		printf("Arithmetic Operation Being Tested: Addition\n");
	}
	if(choice == 2){
		printf("Arithmetic Operation Being Tested: Multiplication\n");
	}
	if(choice == 3){
		printf("Arithmetic Operation Being Tested: Division\n");
	}
	
	//Benchmark iv
	printf("Compiler Flags: 4\n");
	
	//Benchmark v
	printf("Number of Elements Per Vector: %d\n", size);
	
	//Benchmark vi
	printf("Number of Outer Resolution Loops: %d\n", outerLoops);
	
	//Benchmark vii
	printf("Total Elapsed Execution Time for the Benchmark: %f Seconds\n", end - start);
	
	//Benchmark viii
	printf("Execution Time per Vector: %E Seconds\n", (end - start) / outerLoops );
	
	//Benchmark ix
	printf("Execution Time per Arithmetic Operation: %E Seconds\n", ((end - start) / outerLoops) / 1000);
	
	//Benchmark x
	printf("Sustained DP Floating Point Operations: %f FLOPS\n", ((outerLoops * size) / (end - start)));
	
	//Benchmark xi
	if(choice == 1){
		printf("The Number of CPU Clock Cycles per DP FLOP: %f CPO\n", (3800000000 * (end - start)) / (outerLoops * size));
	}
	if(choice == 2){
		printf("The Number of CPU Clock Cycles per DP FLOP: %f CPO\n", (3200000000 * (end - start)) / (outerLoops * size));
	}
	if(choice == 3){
		printf("The Number of CPU Clock Cycles per DP FLOP: %f CPO\n", (3350000000 * (end - start)) / (outerLoops * size));
	}
	
	printf("\n");
	
    return 0;
}
