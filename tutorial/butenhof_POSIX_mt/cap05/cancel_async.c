#include <pthread.h>
#include "errors.h"

#define SIZE    10      /* array size */

static int matrixa[SIZE][SIZE];
static int matrixb[SIZE][SIZE];
static int matrixc[SIZE][SIZE];


/* Loop until canceled. The thread can be canceled at any
 * point within the inner loop, where asynchronous cancellation
 * is enabled. The loop multiplies the two matrices a and b.
 */
void* thread_routine(void* arg)
{
    int cancel_type, err;
    int i, j, k, value = 1;

    /* Initialize the matrices to something arbitrary */
    for (i = 0; i < SIZE; ++i)
    {
        for (j = 0; j < SIZE; ++j)
        {
            matrixa[i][j] = i;
            matrixb[i][j] = j;
        }
    }

    while(1) {
        /* Compute the matrix product of matrixa and matrixb. */
        err = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &cancel_type);
        if(err) err_abort(err, "Set cancel type");

        for (i = 0; i < SIZE; ++i)
            for (j = 0; j < SIZE; ++j) {
                matrixc[i][j] = 0;
                for (k = 0; k < SIZE; ++k)
                    matrixc[i][j] += matrixa[i][k] * matrixb[k][j];
            }

        err = pthread_setcanceltype(cancel_type, &cancel_type);
        if(err) err_abort(err, "Set cancel type");

        /* Copy the result (matrixc) into matrixa to start again. */
        for (i = 0; i < SIZE; ++i)
            for (j = 0; j < SIZE; ++j)
                matrixa[i][j] = matrixc[i][j];
    }
}

int main (int argc, char** argv)
{
    pthread_t thread_id;
    void* result;
    int err;

    err = pthread_create(&thread_id, NULL, thread_routine, NULL);
    if(err) err_abort(err, "Create thread");

    sleep(1);
    err = pthread_cancel(thread_id);
    if(err) err_abort(err, "Cancel thread");

    err = pthread_join(thread_id, &result);
    if(err) err_abort(err, "Join thread");

    if(result == PTHREAD_CANCELED)
        printf("Thread canceled\n");
    else
        printf("Thread was not canceled\n");

    return 0;
}
