#include <stdio.h>

typedef struct {
    char id;
    int deadline;
    int profit;
} Job;

void quickSortJobs(Job arr[], int left, int right);

void scheduleJobs(Job jobs[], int n) {
    quickSortJobs(jobs, 0, n - 1);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;

    char schedule[maxDeadline];
    for (int i = 0; i < maxDeadline; i++)
        schedule[i] = '-';

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (schedule[j] == '-') {
                schedule[j] = jobs[i].id;
                break;
            }
        }
    }

    printf("schedule:\n");
    for (int i = 0; i < maxDeadline; i++)
        printf("day %d: %c\n", i + 1, schedule[i]);
}

void quickSortJobs(Job arr[], int left, int right) {
    if (left >= right)
        return;

    int i = left, j = right;
    int pivot = arr[(i + j) / 2].profit;

    while (i <= j) {
        while (arr[i].profit > pivot)
            i++; // DESC
        while (arr[j].profit < pivot)
            j--;

        if (i <= j) {
            Job temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    quickSortJobs(arr, left, j);
    quickSortJobs(arr, i, right);
}

int main() {
    Job jobs[] = {
        {'A', 2, 100}, {'B', 1, 19}, {'C', 2, 27}, {'D', 1, 25}, {'E', 3, 15}};

    scheduleJobs(jobs, 5);
    return 0;
}
