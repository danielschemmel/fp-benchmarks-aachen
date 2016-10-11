/*
	selectionSort.h
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

#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

void selectionSortInt(int* values, const int arraySize);
void selectionSortReverseInt(int* values, const int arraySize);

void selectionSortFloat(float* values, const int arraySize);

void selectionSortDouble(double* values, const int arraySize);

#endif
