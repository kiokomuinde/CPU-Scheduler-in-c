#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

//Defining a line length
#define MAX_LINE_LENGTH 255

int main(int argc, char *argv[])
{
	//Global variables, input files and strings
	FILE *inputFile, *outputFile;
	char *input, *output;
	char *algorithm;

	//Declaring the integer values associated with the arrays
	int limit = 0;
	int i, n = 0;

	//Declaring our arrays to hold sequential values of each term in the
	//input file
	int* pIdArr; 
	int* arrivalArr; 
	int* burstArr;

	if( argc == 4) {

      
      	input = argv[1];
      	output = argv[2];
      	algorithm = argv[3];

    }else if(argc < 4){

    	perror("Please provide the required arguments. Three or five arguments");
		return -1;
    }else if (argc == 5)
    {	
    	input = argv[1];
      	output = argv[2];
      	algorithm = argv[3];
    	//limit is equated to the last fourth if it was provided.
    	limit = atoi(argv[4]);
    }else{

    	perror("Too many arguments");
		return -1;
    }




    //Opening the input file 
	inputFile = fopen(input, "r");
	if(inputFile == NULL){

		perror("Error opening input file");
		return -1;
	}

	//a string character of length maxlinelength to be used in looping
	//through the inout file
	char ch1[MAX_LINE_LENGTH];


	//Check if the limit of the processes was provided.
	//Else create arrays of size the number of lines in input file


	if (limit == 0)
	{
		while((fgets(ch1, MAX_LINE_LENGTH, inputFile)) != NULL){
		
			n++;
    	}

    	limit = n;
	}
	//Close input file
    fclose(inputFile);


    //Dynamically creating our arrays of size limit.
    pIdArr = calloc(limit, sizeof(int) ); 
    arrivalArr = calloc(limit, sizeof(int) );
    burstArr = calloc(limit, sizeof(int) );


    //Opening the input file again to feed our arrays
	inputFile = fopen(input, "r");
	if(inputFile == NULL){

		perror("Error opening input file a second time.");
		return -1;
	}


	//Feeding the file contents to our three arrays.
    int counter = 0;
	while((fgets(ch1, MAX_LINE_LENGTH, inputFile)) != NULL){
		
		char *token;
		//Getting the variables from the space separated line
		token = strtok(ch1, " ");
		for (i = 0; i < 4; ++i)
		{	//geting pid, arrival time and burst time in each file.
			
			if (i == 0)
			{
				pIdArr[counter] = atoi(token);
				

			}else if (i == 1)
			{

				arrivalArr[counter] = atoi(token);
			}else if (i == 2)
			{
				burstArr[counter] = atoi(token);

			}

			token = strtok(NULL," ");
			
		}

		//Increament counter to access next index of the arrays
		counter++;

		//If the limit is reached stop reading in the processes
		if (counter == limit)
		{
			break;
		}

    }

    //Close input file
    fclose(inputFile);

    //Opening the output file for writing
	outputFile = fopen(output, "w");
	if(outputFile == NULL){

		perror("Error opening output file");
		return -1;
	}

	//Setting counters and waiting time to 0.
	int burstCounter = 0, waitingTime = 0, minBurst = 1;

	int totalWaitingTime = 0, totalTurnAroundTime = 0;

	if (strcmp(algorithm, "SJF") == 0){
	
	    for (i= 0; i < limit; ++i)
	    {	
	    	
	    	
	    	//First process goes to queue without waiting.
	    	if (i==0)
	    	{
	    		burstCounter += burstArr[i];
	    		waitingTime = 0;
	    		printf("%d %d %d %d\n", pIdArr[i], arrivalArr[i], burstCounter, waitingTime);
	    		
	    		//Getting cummulative values for turnaround and waitingtime
	    		//values
	    		totalTurnAroundTime += burstArr[minBurst];
	    		totalWaitingTime += waitingTime;

	    		//Setting printed process id to zero so the processes
	    		//are not repeated.
	    		pIdArr[i] = 0;
	    	}else if (arrivalArr[i] >= burstCounter)
	    	{
	    		burstCounter += burstArr[i];
	    		waitingTime = 0;
	    		printf("%d %d %d %d\n", pIdArr[i], arrivalArr[i], burstCounter, waitingTime);

	    		//Getting cummulative values for turnaround and waitingtime
	    		//values
	    		totalTurnAroundTime += burstArr[minBurst];
	    		totalWaitingTime += waitingTime;

	    		//Setting printed process id to zero so the processes
	    		//are not repeated.
	    		pIdArr[i] = 0;
	    	}else{

	    		int j= 0;
	    		while( j < limit ){

	    			if (pIdArr[j] != 0)
	    			{
	    				if (arrivalArr[j] <= burstCounter)
		    			{
		    				if (j>1)
		    				{
		    					if (burstArr[minBurst] > burstArr[j])
			    				{
			    					minBurst = j;
			    				}else if (burstArr[minBurst] < burstArr[j]){

			    					minBurst = minBurst;
			    				}
		    				}
		    				
		    			}
	    			}

	    			
	    			j++;
	    		}
	    		
	    		burstCounter += burstArr[minBurst];
	    		waitingTime =  burstCounter - arrivalArr[minBurst];
	    		printf("%d %d %d %d\n", pIdArr[minBurst], arrivalArr[minBurst], burstCounter, waitingTime);

	    		//Getting cummulative values for turnaround and waitingtime
	    		//values
	    		totalTurnAroundTime += burstArr[minBurst];
	    		totalWaitingTime += waitingTime;
	    		//Setting printed process id to zero so the processes
	    		//are not repeated.
	    		pIdArr[minBurst] = 0;

	    		//Refresh the value of minBurst.
	    		//It should be the lowest index of pid array which is not
	    		//equal to zero.
	    		for (i = 0; i < limit; ++i)
	    		{
	    			if (pIdArr[i] != 0){
	    				minBurst = i;
	    				break;
	    			}
	    		}
	    		
	    	}
	    }
	}else if (strcmp(algorithm, "SRTF") == 0)
	{
		burstCounter = 0; waitingTime = 0; minBurst = 1;
		totalWaitingTime = 0; totalTurnAroundTime = 0;
		int finalLoop = 0, k;

		for (k = 0; k < limit; ++k)
		{
			
		
			for (i= 0; i < limit; ++i)
		    {	
		    	//First process goes to queue without waiting.
		    	// int j=0;

		    	
		    		
		    	
		    	if (k==0)
		    	{
			    		
		    		if (pIdArr[k] != 0)
		    		{
			    		if (burstArr[k] == 0)
			    		{
			    			printf("%d %d %d %d\n", pIdArr[i], arrivalArr[i], burstCounter, waitingTime);

				    		//Getting cummulative values for turnaround and waitingtime
				    		//values
				    		totalTurnAroundTime += burstArr[i];
				    		totalWaitingTime += waitingTime;
				    		//Setting printed process id to zero so the processes
				    		//are not repeated.
				    		pIdArr[i] = 0;
			    		}else{

			    			burstCounter ++;
			    			burstArr[i]--;
			    			i--;
			    			k--;
			    		}
			    	
			    	}
		    	}else if (arrivalArr[i] > burstCounter)
		    	{
		    		
		    		if (pIdArr[i] != 0)
		    		{

			    		if (burstArr[i]==0)
			    		{	

			    			waitingTime =  burstCounter - arrivalArr[minBurst];
			    			printf("%d %d %d %d\n", pIdArr[i], arrivalArr[i], burstCounter, waitingTime);

				    		//Getting cummulative values for turnaround and waitingtime
				    		//values
				    		totalTurnAroundTime += burstArr[i];
				    		totalWaitingTime += waitingTime;
				    		//Setting printed process id to zero so the processes
				    		//are not repeated.
				    		pIdArr[i] = 0;
			    		}else{
			    			burstCounter ++;
		    				burstArr[i]--;
		    				i--;
		    				k--;
			    		}

			    		
			    	}


		    	}else{

		    		int j=0;
		    		for (j = 0; j < limit; ++j)
		    		{

		    			if (pIdArr[j] != 0)
		    			{
		    				if (arrivalArr[j] <= burstCounter)
			    			{
			    				if (j>1)
			    				{
			    					if (burstArr[minBurst] > burstArr[j])
				    				{
				    					minBurst = j;
				    				}else if (burstArr[minBurst] < burstArr[j]){

				    					minBurst = minBurst;
				    				}
			    				}
			    				
			    			}
		    			}

		    		}
		    		
		    		if (pIdArr[minBurst] !=0)
		    		{
		    			
		    		
			    		if (burstArr[minBurst] == 0)
			    		{
		    				waitingTime =  burstCounter - arrivalArr[minBurst];
			    			printf("%d %d %d %d\n", pIdArr[minBurst], arrivalArr[minBurst], burstCounter, waitingTime);

				    		//Getting cummulative values for turnaround and waitingtime
				    		//values
				    		totalTurnAroundTime += burstCounter;
				    		totalWaitingTime += waitingTime;
				    		//Setting printed process id to zero so the processes
				    		//are not repeated.
				    		pIdArr[minBurst] = 0;

				    		//Refresh the value of minBurst.
				    		//It should be the lowest index of pid array which is not
				    		//equal to zero.
				    		for (finalLoop = 0; finalLoop < limit; finalLoop++)
				    		{
				    			if (pIdArr[finalLoop] != 0){
				    				minBurst = finalLoop;
				    				break;
				    			}
				    		}
			    		}

				    		burstCounter ++;
				    		burstArr[minBurst]--;

		    		}	
		    		
		    		
		    	}
		    }

		    if (finalLoop == limit)
			{
				break;				
			}

	    }

	    
	}
    
	double averageWaiting = totalWaitingTime/limit;
	double averageTurning = totalTurnAroundTime / limit;

	fprintf(outputFile,"\n\n\n Average waiting time:  %f", averageWaiting);
	fprintf(outputFile,"\n Average turning time:  %f", averageTurning);
    //Close output file
    fclose(outputFile);

    //Free our arrays
    free(pIdArr);
    free(arrivalArr);
    free(burstArr);

}