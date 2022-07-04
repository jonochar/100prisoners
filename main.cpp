#include "main.h"

using namespace std;

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int N, i;
    float trials = 0;
    float passes = 0;
    if (argc > 1) {
        N = stoi(argv[1]);
    } else {
        N = TRIALS;
    }

    vector<future<int> > results;
    vector<thread> thread_pool;

    for(i = 0; i<THREADS; i++) {
        promise<int> p;
        results.push_back(p.get_future());
        thread_pool.push_back(thread(run_sim_n_times, N, move(p)));
    }
    for(i = 0; i<THREADS; i++) {
        passes += (float) results[i].get();
        trials += (float) N;
    }
    for(i = 0; i<THREADS; i++) {
        thread_pool[i].join();
    }


    float rate = 100*passes/trials;
    cout << fixed << setprecision(3) << "Success Rate: " << rate << "%. N = " << trials << endl;
}

void run_sim_n_times(int N, promise<int> p) {
    int pass = 0;
    int fail = 0;
    for (int i = 0; i < N; i++) {
        if (run_sim() == 1) {
            fail++;
        } else {
            pass++;
        }
    }
    p.set_value(pass);
}

int run_sim() {
    int boxes [NUM_PRISONERS];
    int i, next, prisoner;

    // Setup
    for (i = 0; i < NUM_PRISONERS; i++) {
        boxes[i] = i;
    }
    shuffle_array(boxes, NUM_PRISONERS);

    for (prisoner = 0; prisoner < NUM_PRISONERS; prisoner++) {
        if(find_tag(prisoner, boxes) == 1) {
            return 1;
        }
    }

    return 0;
}

int find_tag(int prisoner, int boxes[]) {
    int contents, i, j;
    int been_there[100] = {0};
    been_there[prisoner] = 0;
    int cur = prisoner;

    for (i = 0; i < NUM_PRISONERS/2; i++) {
        
        // Check if we've been here
        if (been_there[cur] == 1) {
            for (j = 0; j < NUM_PRISONERS; j++) {
                if (been_there[j] == 0) {
                    cur = j;
                    break;
                }
            }
        }

        // Look inside
        contents = boxes[cur];

        // If we found ourself in the box, we done
        if(contents == prisoner) {
            return 0;
        }

        // Mark that we've been to this box
        been_there[cur] = 1;

        // Now we need to prepare to move to the next box, but first, check if we've
        // finished our first loop. If yes, it's time to jump onto a new loop
        // Check the map for the first box that hasn't been visited and start the search there.
        cur = contents;
    }

    return 1;
}

void shuffle_array(int arr[], size_t n) {
    if (n <= 1) return;

    int temp;
    int rand_idx;
    for (size_t i = 0; i < n; i++) {
        // Do I still remember how to do a swap...
        rand_idx = rand() % n;
        temp = arr[i];
        arr[i] = arr[rand_idx];
        arr[rand_idx] = temp;
    }
}

void print_arr(int arr[], int n) {
    for(int i = 0; i<n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}