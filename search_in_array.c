#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int main() {
    int row, col, key;
    printf("Enter the number of rows: ");
    scanf("%d", &row);
    printf("Enter the number of columns: ");
    scanf("%d", &col);
    printf("Enter the key to search: ");
    scanf("%d", &key);
    int **matrix = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++) {
        matrix[i] = (int *)malloc(col * sizeof(int));
    }
    srand(time(NULL));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
    int *indxArr = (int *)malloc(2 * row * col * sizeof(int));
    int indxCount = 0;
    #pragma omp parallel for 
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == key) {
                int tid = omp_get_thread_num();
                printf("Key found by thread %d at index (%d, %d)\n", tid, i, j);
                int index = indxCount * 2; 
                indxArr[index] = i;
                indxArr[index + 1] = j;
                indxCount++;
            }
        }
    }
    printf("Indices of the key: ");
    for (int i = 0; i < indxCount; i++) {
        int index = i * 2;
        printf("(%d, %d) ", indxArr[index], indxArr[index + 1]);
    }
    if (indxCount == 0) {
        printf("-1");
    }
    printf("\n");
    free(indxArr);
    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
