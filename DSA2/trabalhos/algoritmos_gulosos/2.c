#include <stdio.h>

typedef struct {
    int start, end;
} Interval;

void quickSortIntervals(Interval arr[], int left, int right);

void minCover(int L, Interval intervals[], int n) {
    quickSortIntervals(intervals, 0, n - 1);

    int current = 0, i = 0;

    printf("intervals:\n");

    while (current < L) {
        int bestEnd = current;

        while (i < n && intervals[i].start <= current) {
            if (intervals[i].end > bestEnd)
                bestEnd = intervals[i].end;
            i++;
        }

        if (bestEnd == current) {
            printf("impossible\n");
            return;
        }

        printf("[%d, %d]\n", current, bestEnd);
        current = bestEnd;
    }
}

void quickSortIntervals(Interval arr[], int left, int right) {
    if (left >= right)
        return;

    int i = left, j = right;
    int pivot = arr[(i + j) / 2].start;

    while (i <= j) {
        while (arr[i].start < pivot)
            i++;
        while (arr[j].start > pivot)
            j--;

        if (i <= j) {
            Interval temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    quickSortIntervals(arr, left, j);
    quickSortIntervals(arr, i, right);
}

int main() {
    Interval intervals[] = {
        {0, 2},    {1, 5},    {2, 6},    {3, 7},    {4, 9},    {5, 10},
        {6, 11},   {7, 13},   {8, 14},   {9, 15},   {10, 16},  {11, 18},
        {12, 19},  {13, 20},  {14, 22},  {15, 23},  {16, 24},  {17, 25},
        {18, 26},  {19, 28},  {20, 29},  {21, 30},  {22, 31},  {23, 33},
        {24, 34},  {25, 35},  {26, 36},  {27, 38},  {28, 39},  {29, 40},
        {30, 41},  {31, 43},  {32, 44},  {33, 45},  {34, 46},  {35, 48},
        {36, 49},  {37, 50},  {38, 51},  {39, 53},  {40, 54},  {41, 55},
        {42, 56},  {43, 58},  {44, 59},  {45, 60},  {46, 61},  {47, 63},
        {48, 64},  {49, 65},  {50, 66},  {51, 68},  {52, 69},  {53, 70},
        {54, 71},  {55, 73},  {56, 74},  {57, 75},  {58, 76},  {59, 78},
        {60, 79},  {61, 80},  {62, 81},  {63, 83},  {64, 84},  {65, 85},
        {66, 86},  {67, 88},  {68, 89},  {69, 90},  {70, 91},  {71, 93},
        {72, 94},  {73, 95},  {74, 96},  {75, 98},  {76, 99},  {77, 100},
        {78, 101}, {79, 103}, {80, 104}, {81, 105}, {82, 106}, {83, 108},
        {84, 109}, {85, 110}, {86, 111}, {87, 113}, {88, 114}, {89, 115},
        {90, 116}, {91, 118}, {92, 119}, {93, 120}, {94, 121}, {95, 123},
        {96, 124}, {97, 125}, {98, 126}, {99, 128}};
    // pedi uma quantidade  absurdo de intervalos pra IA.
    minCover(128, intervals, 100);
    return 0;
}
