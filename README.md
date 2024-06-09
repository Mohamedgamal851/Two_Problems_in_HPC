# This first problem is search-in-array
This is a C program to search for a key in a 2D array. Matrix dimensions and the key we will search for will be taken as input, initialize the matrix with random numbers, share the matrix with all processes and return the indices of the key, if key is not found return -1.

Note: Must use dynamic allocation
### Input: row, column, key
### Output: array containing the indices the key appeared at.
## Parallelization Process:
-Use “ #pragma omp parallel for “ directive to divide the search loops iterations among
processes.
-every time the key is found display which process found it at what index and add that
index to an array let’s say “indxArr” and print that array.

# This second problem is Calculating Standard Deviation

Write a parallel c program to calculate standard deviation using
### Given:
An integer n (number of elements per process).
### Output:
Standard deviation of randomly generated (n * numberOfProcesses) elements.
## How to Calculate Standard Deviation:
1. Calculate the Mean. (sum of n elements/ n)
2. For each number, subtract the mean and square the result. ( (element - mean)2 )
3. Calculate the mean of the squared differences. ( 𝑠𝑢𝑚( (𝑒𝑙𝑒𝑚𝑒𝑛𝑡 − 𝑚𝑒𝑎𝑛)2) / 𝑛 )
4. Take the square root of step three.
## Parallelization Scenario:
- Get n from user and make it shared.
### In the parallel part of the code will be the following
- Generate n random elements.
- Calculate local sum of the generated n elements.
- Calculate local mean of the generated n elements. (local sum / n)
- Calculate local sum of squared differences from the mean. Sum( (element - mean)2)
- Add local sum of squared differences to global sum. globalSum += localSumOSqD
- Calculate the global mean. (global sum / n * numOfProcesses).
- Calculate the square root of the global mean.
