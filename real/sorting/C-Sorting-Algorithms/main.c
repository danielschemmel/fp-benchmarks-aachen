/*
	main.c
	Created 7 May 2016

	A selection sort tester in C.
    Copyright (C) 2016  Douglas Chidester

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "main.h"

int main(void)
{
	char* filename = "randomInts.txt";
	int values[ARRAY_SIZE];
	//int values[ARRAY_SIZE] = {5, -3, 2, 1, -4, 100, -20, 15, 3, -3, 45, 44, -40};
	
	#if VERBOSE
	int k = 0;
	#endif

	// read ints from a file
	FILE *myfile = fopen(filename, "r");
    if(myfile == NULL)
    {
        perror("Error opening file");
    }
    else
    {
    	for(int i = 0; i < ARRAY_SIZE; ++i)
	    {
	    	fscanf(myfile, "%d", &values[i]);
	    }
	    fclose(myfile);

	    #if VERBOSE
	    // print out array before sorting
		printf("starting array\n[ ");
		for(k = 0; k < ARRAY_SIZE; k++)
		{
			printf("%d ", values[k]);
		}
		puts("]");
		#endif

		// sort
		selectionSortInt(values, ARRAY_SIZE);

		#if VERBOSE
		// print out array after sorting
		printf("sorted array\n[ ");
		for(k = 0; k < ARRAY_SIZE; k++)
		{
			printf("%d ", values[k]);
		}
		puts("]");
		#endif

		// test to make sure the sort worked
		testSortedInts(values, ARRAY_SIZE);

		// reverse sort and test
		selectionSortReverseInt(values, ARRAY_SIZE);
		
		#if VERBOSE
		printf("sorted array\n[ ");
		for(k = 0; k < ARRAY_SIZE; k++)
		{
			printf("%d ", values[k]);
		}
		puts("]");
		#endif
		
		testReverseSortedInts(values, ARRAY_SIZE);
    }
    
	return 0;
}

void testSortedInts(int* sortedArray, const int size)
{
	int isSorted = 1;
	int i = 0;

	if(size <= 1)
	{
		puts("Value is sorted!");
	}
	else if(size > 1)
	{
		for(i = 0; sortedArray[i] && sortedArray[i + 1] && i < size; ++i)
		{
			if(sortedArray[i] > sortedArray[i + 1])
			{
				isSorted = 0;
				break;
			}
		}

		if(isSorted)
		{
			puts("Values are sorted!");
		}
		else
		{
			printf("Array not sorted at index %d!\n", i);
			printf("%d > %d\n", sortedArray[i], sortedArray[i + 1]);
		}
		
	}
}

void testReverseSortedInts(int* sortedArray, const int size)
{
	int isSorted = 1;
	int i = 0;

	if(size <= 1)
	{
		puts("Value is sorted!");
	}
	else if(size > 1)
	{
		for(i = 0; sortedArray[i] && sortedArray[i + 1] && i < size; ++i)
		{
			if(sortedArray[i] < sortedArray[i + 1])
			{
				isSorted = 0;
				break;
			}
		}

		if(isSorted)
		{
			puts("Values are sorted!");
		}
		else
		{
			printf("Array not sorted at index %d!\n", i);
			printf("%d < %d\n", sortedArray[i], sortedArray[i + 1]);
		}
	}
}
