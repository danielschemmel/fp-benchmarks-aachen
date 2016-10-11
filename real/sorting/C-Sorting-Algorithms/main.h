/*
	main.h
	Created 19 May 2016

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

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "selectionSort.h"

#define ARRAY_SIZE 10000
#define VERBOSE 0

void testSortedInts(int* sortedArray, const int size);
void testReverseSortedInts(int* sortedArray, const int size);

#endif
