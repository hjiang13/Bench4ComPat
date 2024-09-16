#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define L 20  // Linear dimension of the lattice
#define N (L * L)  // Total number of spins
#define STEPS 100000  // Number of Monte Carlo steps
#define TEMPERATURE 2.0  // Temperature

// Function to initialize the spin lattice
void initialize_spins(int spins[L][L]) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            spins[i][j] = (rand() % 2) * 2 - 1;  // Randomly assign +1 or -1
        }
    }
}

// Function to compute the energy of the system
double compute_energy(int spins[L][L]) {
    double energy = 0.0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            int right = (i + 1) % L;
            int down = (j + 1) % L;
            energy -= spins[i][j] * (spins[right][j] + spins[i][down]);
        }
    }
    return energy;
}

// Function to compute the magnetization of the system
double compute_magnetization(int spins[L][L]) {
    double magnetization = 0.0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            magnetization += spins[i][j];
        }
    }
    return magnetization;
}

// Function to perform a single Monte Carlo step
void monte_carlo_step(int spins[L][L], double temperature) {
    for (int n = 0; n < N; n++) {
        int i = rand() % L;
        int j = rand() % L;

        int right = (i + 1) % L;
        int left = (i - 1 + L) % L;
        int down = (j + 1) % L;
        int up = (j - 1 + L) % L;

        int dE = 2 * spins[i][j] * (spins[right][j] + spins[left][j] + spins[i][down] + spins[i][up]);

        if (dE <= 0 || ((double)rand() / RAND_MAX) < exp(-dE / temperature)) {
            spins[i][j] = -spins[i][j];
        }
    }
}

int main() {
    int spins[L][L];
    double temperature = TEMPERATURE;

    srand(time(NULL));

    initialize_spins(spins);

    double energy = compute_energy(spins);
    double magnetization = compute_magnetization(spins);

    printf("Initial Energy: %f\n", energy);
    printf("Initial Magnetization: %f\n", magnetization);

    for (int step = 0; step < STEPS; step++) {
        monte_carlo_step(spins, temperature);

        if (step % 10000 == 0) {
            energy = compute_energy(spins);
            magnetization = compute_magnetization(spins);
            printf("Step: %d, Energy: %f, Magnetization: %f\n", step, energy, magnetization);
        }
    }

    energy = compute_energy(spins);
    magnetization = compute_magnetization(spins);
    printf("Final Energy: %f\n", energy);
    printf("Final Magnetization: %f\n", magnetization);

    return 0;
}
