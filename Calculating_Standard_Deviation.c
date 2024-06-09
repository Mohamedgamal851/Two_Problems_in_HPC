#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>
int main() {
    int n;
    printf("Enter number of elements per process (n): ");
    scanf("%d", &n);
    int numThreads = omp_get_max_threads();
    double globalSum = 0.0;
    int i;
    #pragma omp parallel num_threads(numThreads) private(i) reduction(+:globalSum)
    {
        // Generate random elements and calculate local sums
        int *localArr = (int *)malloc(n * sizeof(int));
        double localSum = 0.0, localSumSqDiff = 0.0;
        srand(time(NULL) + omp_get_thread_num());
        for (i = 0; i < n; i++) {
            localArr[i] = rand() % 100; 
            localSum += localArr[i];
        }
        double localMean = localSum / n;
        for (i = 0; i < n; i++) {
            double diff = localArr[i] - localMean;
            localSumSqDiff += diff * diff;
        }
        free(localArr);
        globalSum += localSumSqDiff;
    }
    double globalMean =  globalSum / (n * numThreads);
    double standardDeviation = sqrt(globalMean);
    printf("Standard deviation: %.4f\n", standardDeviation);
    return 0;
}
