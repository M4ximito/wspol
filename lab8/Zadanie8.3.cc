#include <iostream>
#include <omp.h>

#define NUM_PHILOSOPHERS 5
#define NUM_MEALS 3

omp_lock_t forks[NUM_PHILOSOPHERS];
omp_lock_t waiter;

void initialize() {
    omp_init_lock(&waiter);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        omp_init_lock(&forks[i]);
    }
}

void destroy() {
    omp_destroy_lock(&waiter);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        omp_destroy_lock(&forks[i]);
    }
}

void philosopher(int id) {
    int leftFork = id;
    int rightFork = (id + 1) % NUM_PHILOSOPHERS;

    for (int i = 0; i < NUM_MEALS; i++) {
        omp_set_lock(&waiter);

        omp_set_lock(&forks[leftFork]);
        omp_set_lock(&forks[rightFork]);

        omp_unset_lock(&waiter);

        std::cout << "Filozof " << id << " je posiłek " << i + 1 << std::endl;

        omp_unset_lock(&forks[leftFork]);
        omp_unset_lock(&forks[rightFork]);
    }
}

int main() {
    initialize();

    #pragma omp parallel num_threads(NUM_PHILOSOPHERS)
    {
        int id = omp_get_thread_num();
        philosopher(id);
    }

    destroy();

    return 0;
}
