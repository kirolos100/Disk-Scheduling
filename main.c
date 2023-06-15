#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

int absolute(int x, int y) {
    return abs(x - y);
}

void sorting(int arr[], int size) {
    int i;
    int j;
    int tp;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                tp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tp;
            }
        }
    }
}



/*determine the absolute difference between the current location and the next request using the FCFS algorithm's function to determine the overall seek time.
current position updated*/
int fcfs(int arrr[], int n, int in) {
    int i;
    int distance = 0;
    int curr = in;

    for (i = 0; i < n; i++) {

        distance += absolute(curr, arrr[i]);


        curr = arrr[i];
    }

    return distance;
}

/*// The SSTF algorithm is used to determine the overall seek time. Locate the request that is closest to the current location. Update the seek time and location now. Put a visited on the request.
// Create the visited array with false values.*/
int sstf(int arrr[], int n, int in) {
    int i, distance = 0;
    int curr = in;
    bool *vis = (bool *)malloc(n * sizeof(bool));


    for (i = 0; i < n; i++) {
        vis[i] = false;
    }

    for (i = 0; i < n; i++) {
        int sdist = INT_MAX;
        int index;

        for (int j = 0; j < n; j++) {
            if (!vis[j] && absolute(curr, arrr[j]) < sdist) {
                sdist = absolute(curr, arrr[j]);
                index = j;
            }
        }

        distance += sdist;
        curr = arrr[index];

        vis[index] = true;
    }

    free(vis);

    return distance;
}

/*
scan we move to the rightmost or leftmost and we serve until we found the final target
SCAN towards the left direction // Determine the position to begin scanning towards the left // Process the arrr in the left direction // Move to the leftmost position
// Process the remaining arrr in the right direction
 // Function to compute the overall seek time using the SCAN algorithm*/
int scan(int arrr[], int n, int in, int direction) {
    int i, distance = 0;
    int curr = in;
    int le = 0;
    int ri = 4999;

    sorting(arrr, n);

    if (direction == 0) {


        for (i = 0; i < n; i++) {
            if (arrr[i] < in) {
                le = i;
            }
        }


        for (i = le; i >= 0; i--) {
            distance += absolute(curr, arrr[i]);
            curr = arrr[i];
        }


        distance += absolute(curr, 0);
        curr = 0;

        for (i = le + 1; i < n; i++) {
            distance += absolute(curr, arrr[i]);
            curr = arrr[i];
        }
    } else {
        /*SCAN in the right direction; locate the starting point for scanning in the right direction; process the arr in the right direction;
        move to the position to the right of that position; process the remaining arr in the left direction.*/
        for (i = 0; i < n; i++) {
            if (arrr[i] > in) {
                ri = i;
                break;
            }
        }


        for (i = ri; i < n; i++) {
            distance += absolute(curr, arrr[i]);
            curr = arrr[i];
        }


        distance += absolute(curr, 4999);
        curr = 4999;


        for (i = ri - 1; i >= 0; i--) {
            distance += absolute(curr, arrr[i]);
            curr = arrr[i];
        }
    }

    return distance;
}

/*
C-Look we serve until we found the least target or the max target then we go to rightmost or leftmost and finally we return and serve the other targets
C-LOOK algorithm is used in this function to determine the overall seek time. C-LOOK is directed left. Locate the starting point for your scan to go to the left.
Process the arrr in a left-to-right fashion // Continue processing the remaining arrr in the proper manner.*/
int clook(int arrr[], int n, int in, int direction) {
    int i, distance = 0;
    int curr = in;
    int le = 0;
    int ri = n - 1;

    sorting(arrr, n);

    if (direction == 0) {


        for (i = 0; i < n; i++) {
            if (arrr[i] <= in) {
                le = i;
            }
        }


        for (i = le; i >= 0; i--) {
            distance += absolute(curr, arrr[i]);
            curr = arrr[i];
        }


        for (i = ri; i > le; i--) {
            distance += absolute(curr, arrr[i]);
            curr = arrr[i];
        }
    } else {
        /*To process the arrr in the right direction, C-LOOK in the right direction,
        find the starting location for scanning in the right direction, and process the remaining arrr in the left direction.*/
        for (i = 0; i < n; i++) {
            if (arrr[i] >= in) {
                ri = i;
                break;
            }
        }


        for (i = ri; i < n; i++) {
            distance += absolute(curr, arrr[i]);
            curr = arrr[i];
        }


        for (i = le; i < ri; i++) {
            distance += absolute(curr, arrr[i]);
            curr = arrr[i];
        }
    }

    return distance;
}

int main(int argc, char *argv[]) {
    int n = 1000;  //disks
    int in, i;

    /*if (argc != 2) {
        printf("Usage: %s <in>\n", argv[0]);
        return 1;
    }*/

    in = atoi(argv[1]);

    int *arrr = (int *)malloc(n * sizeof(int));

    srand(time(NULL));
    for (i = 0; i < n; i++) {
        arrr[i] = rand() % 5000;
    }

    int fcfs_dist = fcfs(arrr, n, in);
    int sstf_dist = sstf(arrr, n, in);
    int scan_dist = scan(arrr, n, in, 0);
    int clook_dist = clook(arrr, n, in, 0);

    printf("FCFS Seek Time: %d\n", fcfs_dist);
    printf("SSTF Seek Time: %d\n", sstf_dist);
    printf("SCAN Seek Time (right direction): %d\n", scan_dist);
    printf("C-LOOK Seek Time (left direction): %d\n", clook_dist);

    free(arrr);

    return 0;
}
