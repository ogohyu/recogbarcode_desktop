#pragma once

#define MAX_LABEL 10000

#define MAX_CONTOUR 5000

typedef struct _ContourPoints
{
	int num;
	int x[MAX_CONTOUR];
	int y[MAX_CONTOUR];
} ContourPoints;

void DibBinarization(CDib& dib, int th);
int DibBinarizationIterative(CDib& dib);

ContourPoints DibContourTracing(CDib& dib);
void DibCrop(CDib& dib, int StartX, int StartY, int EndX, int EndY);
void DibSort(CDib& dib);
