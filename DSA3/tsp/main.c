#include <limits.h> //INT_MAX
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define EXACT_TIME_LIMIT 300 // 5MIN
// #define MAX_VERTICES 80 no

int getVertexCountFromFile(FILE *file);
void readMatrixFromFile(FILE *file, int nVertex,
                        int adjacencyMatrix[nVertex][nVertex]);
int calculateRouteCost(int nVertex, int adjacencyMatrix[nVertex][nVertex],
                       int route[nVertex]);
void nearestNeighbor(int nVertex, int adjacencyMatrix[nVertex][nVertex],
                     int route[nVertex]);
void printRoute(int nVertex, int route[nVertex]);

void reverseRoutePart(int route[], int start, int end);

void twoOPT(int nVertex, int adjacencyMatrix[nVertex][nVertex],
            int route[nVertex]);

void branchAndBound(int nVertex, int adjacencyMatrix[nVertex][nVertex],
                    int route[nVertex], int visited[nVertex], int routePosition,
                    int currentVertex, int currentCost, int *bestCost,
                    int bestRoute[nVertex]);

int getOptimalCostsFromFileName(char *filename);

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("input error: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    int nVertex = getVertexCountFromFile(file);
    int adjacencyMatrix[nVertex][nVertex];

    readMatrixFromFile(file, nVertex, adjacencyMatrix);
    fclose(file);

    // heuristic: nearest beighbor + 2-opt

    int route[nVertex];

    // Nearest Neighbor
    clock_t nearestNeighborStart = clock();

    nearestNeighbor(nVertex, adjacencyMatrix, route);

    clock_t nearestNeighborEnd = clock();

    int nearestNeighborCost =
        calculateRouteCost(nVertex, adjacencyMatrix, route);

    double nearestNeighborExecutionTime =
        (double)(nearestNeighborEnd - nearestNeighborStart) / CLOCKS_PER_SEC;

    // 2-opt
    clock_t twoOptStart = clock();

    twoOPT(nVertex, adjacencyMatrix, route);

    clock_t twoOptEnd = clock();

    int twoOptCost = calculateRouteCost(nVertex, adjacencyMatrix, route);

    int optimalCost = getOptimalCostsFromFileName(argv[1]);

    float gap = ((float)(twoOptCost - optimalCost) / optimalCost) * 100.0;

    double twoOptExecutionTime =
        (double)(twoOptEnd - twoOptStart) / CLOCKS_PER_SEC;
    printf("Heuristic\n");

    printf("\tNearest Neighbor cost: %d\n", nearestNeighborCost);
    printf("\tNearest Neighbor time: %.6f seconds\n",
           nearestNeighborExecutionTime);

    printf("\n\tNearest Neighbor + 2-opt cost: %d\n", twoOptCost);
    printf("\t2-opt time: %.6f seconds\n", twoOptExecutionTime);
    printf("\tGap: %.2f%%\n", gap);
    printRoute(nVertex, route);

    // exact: branch and bound

    int exactRoute[nVertex];
    int exactVisited[nVertex];
    int bestRoute[nVertex];

    for (int i = 0; i < nVertex; i++) {
        exactVisited[i] = 0;
        bestRoute[i] = route[i];
    }

    exactRoute[0] = 0;
    exactVisited[0] = 1;

    int bestCost =
        twoOptCost; // get the result from the nearest neighbor and 2-opt

    clock_t exactStartTime = clock();
    alarm(EXACT_TIME_LIMIT);
    branchAndBound(nVertex, adjacencyMatrix, exactRoute, exactVisited, 1, 0, 0,
                   &bestCost, bestRoute);
    alarm(0); // cancel
    clock_t exactEndTime = clock();
    double exactExecutionTime =
        (double)(exactEndTime - exactStartTime) / CLOCKS_PER_SEC;

    printf("\nExact\n");
    printf("\tBranch and Bound cost: %d\n", bestCost);
    printf("\tExecution time: %.6f seconds\n", exactExecutionTime);
    printRoute(nVertex, bestRoute);

    return 0;
}

int getVertexCountFromFile(FILE *file) {
    int nVertex = 0;
    int c, lastChar;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            nVertex++;
        }
        lastChar = c;
    }

    if (lastChar != '\n') {
        nVertex++;
    }

    rewind(file); // "like the old days, hm?" (by mariltom)
    return nVertex;
}

void readMatrixFromFile(FILE *file, int nVertex,
                        int adjacencyMatrix[nVertex][nVertex]) {
    for (int i = 0; i < nVertex; i++) {
        for (int j = 0; j < nVertex; j++) {
            if (fscanf(file, "%d", &adjacencyMatrix[i][j]) != 1) {
                return;
            }
        }
    }
    return;
}

int calculateRouteCost(int nVertex, int adjacencyMatrix[nVertex][nVertex],
                       int route[nVertex]) {
    int totalCost = 0;
    for (int i = 0; i < nVertex - 1; i++)
        totalCost += adjacencyMatrix[route[i]][route[i + 1]];
    totalCost += adjacencyMatrix[route[nVertex - 1]][route[0]]; // circle
    return totalCost;
}

void nearestNeighbor(int nVertex, int adjacencyMatrix[nVertex][nVertex],
                     int route[nVertex]) {
    int visited[nVertex];
    for (int i = 0; i < nVertex; i++)
        visited[i] = 0;

    int currentVertex = 0; // start of a route

    route[0] = currentVertex;
    visited[currentVertex] = 1;

    for (int routePosition = 1; routePosition < nVertex;
         routePosition++) { // already visited 0
        int bestNeighborVertex =
            -1; // -1 means not a vertex | 0 ... n (out of range)
        int bestNeighborVertexCost = INT_MAX; // yes, 'the limit'
        for (int vertex = 0; vertex < nVertex; vertex++) {
            if (adjacencyMatrix[currentVertex][vertex] <
                    bestNeighborVertexCost &&
                !visited[vertex]) {
                bestNeighborVertex = vertex;
                bestNeighborVertexCost = adjacencyMatrix[currentVertex][vertex];
            }
        }
        route[routePosition] = bestNeighborVertex;
        currentVertex = bestNeighborVertex;
        visited[currentVertex] = 1;
    }
}

void printRoute(int nVertex, int route[nVertex]) {
    printf("Route: ");

    for (int i = 0; i < nVertex; i++) {
        printf("%d ", route[i]);
        if (i < nVertex - 1) {
            printf("-> ");
        }
    }
    printf("-> %d\n", route[0]); // return to start
}

void reverseRoutePart(int route[], int start, int end) {
    while (start < end) {
        int temp = route[start];
        route[start] = route[end];
        route[end] = temp;
        start++;
        end--;
    }
}

void twoOPT(int nVertex, int adjacencyMatrix[nVertex][nVertex],
            int route[nVertex]) {
    int hasImproved = 1, oldCost, newCost;
    while (hasImproved) {
        hasImproved = 0;
        for (int start = 1; start < nVertex - 1; start++) {
            for (int end = start + 1; end < nVertex; end++) {

                oldCost = calculateRouteCost(nVertex, adjacencyMatrix, route);
                reverseRoutePart(route, start, end);
                newCost = calculateRouteCost(nVertex, adjacencyMatrix, route);

                if (newCost < oldCost)
                    hasImproved = 1;
                else {
                    reverseRoutePart(route, start, end); // revert
                }
            }
        }
    }
}

void branchAndBound(int nVertex, int adjacencyMatrix[nVertex][nVertex],
                    int route[nVertex], int visited[nVertex], int routePosition,
                    int currentVertex, int currentCost, int *bestCost,
                    int bestRoute[nVertex]) {
    if (routePosition == nVertex) { // base
        int totalCost = currentCost + adjacencyMatrix[currentVertex][route[0]];

        if (totalCost < *bestCost) {
            *bestCost = totalCost;
            for (int i = 0; i < nVertex; i++) {
                bestRoute[i] = route[i];
            }
        }
        return;
    }
    for (int vertex = 0; vertex < nVertex; vertex++) {
        if (!visited[vertex]) {
            visited[vertex] = 1;
            route[routePosition] = vertex;

            int edgeCost = adjacencyMatrix[currentVertex][vertex];
            int newCost = currentCost + edgeCost;

            if (newCost < *bestCost) {
                branchAndBound(nVertex, adjacencyMatrix, route, visited,
                               routePosition + 1, vertex, newCost, bestCost,
                               bestRoute);
            }
            visited[vertex] = 0; // backtrack
        }
    }
}

int getOptimalCostsFromFileName(char *filename) {
    char *underscore = strrchr(filename, '_');

    if (underscore == NULL) {
        return 1;
    }

    int optimalCost;

    if (sscanf(underscore + 1, "%d", &optimalCost) != 1) {
        return 1;
    }

    return optimalCost;
}
