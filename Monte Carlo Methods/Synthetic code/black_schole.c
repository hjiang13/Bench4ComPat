#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to generate a random number from a standard normal distribution
double random_normal() {
    static int hasSpare = 0;
    static double spare;
    if (hasSpare) {
        hasSpare = 0;
        return spare;
    }

    hasSpare = 1;
    double u, v, s;
    do {
        u = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
        v = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
        s = u * u + v * v;
    } while (s >= 1.0 || s == 0.0);

    s = sqrt(-2.0 * log(s) / s);
    spare = v * s;
    return u * s;
}

// Function to calculate the mean of an array
double mean(double *array, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}

// Function to calculate the standard deviation of an array
double stddev(double *array, int size, double mean) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += (array[i] - mean) * (array[i] - mean);
    }
    return sqrt(sum / (size - 1));
}

int main() {
    int M = 100000;        // Number of trials
    double S = 100.0;      // Initial stock price
    double E = 100.0;      // Strike price
    double r = 0.05;       // Risk-free rate
    double sigma = 0.2;    // Volatility
    double T = 1.0;        // Time to maturity in years
    double *trials = malloc(M * sizeof(double));

    srand(time(NULL));     // Seed the random number generator

    // Monte Carlo simulation
    for (int i = 0; i < M; i++) {
        double t = S * exp((r - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * random_normal());
        trials[i] = exp(-r * T) * fmax(t - E, 0);
    }

    // Calculate mean and standard deviation
    double mean_value = mean(trials, M);
    double stddev_value = stddev(trials, M, mean_value);

    // Print the results
    printf("Mean: %f\n", mean_value);
    printf("Standard Deviation: %f\n", stddev_value);

    // Clean up
    free(trials);

    return 0;
}
