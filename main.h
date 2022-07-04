#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <thread>
#include <future>
#include <vector>

#define NUM_PRISONERS 100
#define TRIALS 1000
#define THREADS 4

void shuffle_array(int[], size_t);
int find_tag(int, int[]);
int run_sim();
void print_arr(int[], int);
void run_sim_n_times(int, std::promise<int>);

#endif