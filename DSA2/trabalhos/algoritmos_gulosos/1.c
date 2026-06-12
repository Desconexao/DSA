#include <stdio.h>

void quickSortStations(int array[], int iLeft, int iRight);

void minStops(int totalDistance, int maxRange, int stations[], int n) {
    quickSortStations(stations, 0, n - 1); // se já n tiver ordenado...

    int current = 0;
    int i = 0;

    printf("stops: ");

    while (current + maxRange < totalDistance) {
        int last = current;

        while (i < n && stations[i] <= current + maxRange) {
            last = stations[i];
            i++;
        }

        if (last == current) {
            printf("impossiblee\n"); // n conseguiu chegar no proximo
            return;
        }

        printf("%d ", last);
        current = last;
    }

    printf("\nreached destination: %d\n", totalDistance); // chegou no destinop
}

void quickSortStations(int array[], int iLeft, int iRight) {
    if (iLeft >= iRight)
        return;

    int left = iLeft, right = iRight;
    int pivot = array[(left + right) / 2];

    while (left <= right) {
        while (array[left] < pivot)
            left++;
        while (array[right] > pivot)
            right--;

        if (left <= right) {
            int temp = array[left];
            array[left] = array[right];
            array[right] = temp;
            left++;
            right--;
        }
    }

    quickSortStations(array, iLeft, right);
    quickSortStations(array, left, iRight);
}

int main() {
    int stations[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 55};
    int n = sizeof(stations) / sizeof(stations[0]);

    minStops(55, 15, stations, n);
    return 0;
}

/*
 * Sempre busca andar o máximo para a menor distância
 * Se parar, anda menos e talvez precise de mais paradas depois
 * Escolher o mais distante não piora, pode até melhorar
 *
 */
