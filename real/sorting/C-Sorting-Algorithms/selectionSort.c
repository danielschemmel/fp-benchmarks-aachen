/*
	selectionSort.c
	Created 7 May 2016

	A selection sort implementation in C.
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

#include "selectionSort.h"

void selectionSortInt(int* values, const int arraySize)
{
	int i = 0;
	int j = 0;
	int minIndex = 0;
	int temp = 0;

	for(i = 0; i < arraySize - 1; ++i)
	{
		minIndex = i + 1;
		// select min
		for(j = i; j < arraySize; j++)
			if(values[j] < values[minIndex])
				minIndex = j;
		// swap values
		temp = values[i];
		values[i] = values[minIndex];
		values[minIndex] = temp;
	}
}

void selectionSortReverseInt(int* values, const int arraySize)
{
	int i = 0;
	int j = 0;
	int minIndex = 0;
	int temp = 0;

	for(i = 0; i < arraySize - 1; ++i)
	{
		minIndex = i + 1;
		// select min
		for(j = i; j < arraySize; j++)
			if(values[j] > values[minIndex])
				minIndex = j;
		// swap values
		temp = values[i];
		values[i] = values[minIndex];
		values[minIndex] = temp;
	}
}

void selectionSortFloat(float* values, const int arraySize)
{
	int i = 0;
	int j = 0;
	int minIndex = 0;
	float temp = 0;

	for(i = 0; i < arraySize - 1; ++i)
	{
		minIndex = i + 1;
		// select min
		for(j = i; j < arraySize; j++)
			if(values[j] < values[minIndex])
				minIndex = j;
		// swap values
		temp = values[i];
		values[i] = values[minIndex];
		values[minIndex] = temp;
	}
}

void selectionSortDouble(double* values, const int arraySize)
{
	int i = 0;
	int j = 0;
	int minIndex = 0;
	double temp = 0;

	for(i = 0; i < arraySize - 1; ++i)
	{
		minIndex = i + 1;
		// select min
		for(j = i; j < arraySize; j++)
			if(values[j] < values[minIndex])
				minIndex = j;
		// swap values
		temp = values[i];
		values[i] = values[minIndex];
		values[minIndex] = temp;
	}
}
