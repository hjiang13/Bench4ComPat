#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Function to estimate Pi using the Monte Carlo method
double estimate_pi(int num_samples) {
    int inside_circle = 0;

    // Seed the random number generator
    srand(time(NULL));

    for (int i = 0; i < num_samples; i++) {
        // Generate random point (x, y)
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        // Check if the point is inside the unit circle
        if (x * x + y * y <= 1.0) {
            inside_circle++;
        }
    }

    // Estimate Pi as 4 * (number of points inside circle / total number of points)
    return (4.0 * inside_circle) / num_samples;
}

int main() {
    int num_samples = 1000000;  // Number of samples to use for the estimation

    // Estimate Pi
    double pi_estimate = estimate_pi(num_samples);

    // Print the estimated value of Pi
    printf("Estimated value of Pi using %d samples: %f\n", num_samples, pi_estimate);

    return 0;
}
