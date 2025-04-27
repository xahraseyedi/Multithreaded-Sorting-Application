#include <stdio.h>
#include <pthread.h>

#define len 7

int array[len] = {13,9,16,45,15,24,7};

void* sort_left( void* arg ) {
    
    for (int i = 1; i < len/2 ; i++ ) {
        int c = array[i];
        int j = i - 1;
        while ( j >= 0 && array[j] > c ) {
            
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = c;
    }
    return NULL;
}

void* sort_right(void* arg) {
    
    for ( int i = len/2 + 1; i < len; i++ ) {
        
        int c = array[i];
        int j = i - 1;
        while ( j >= len/2 && array[j] > c ) {
            
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = c;
    }
    return NULL;
}

void* merge(void* arg) {
    
    int temp[len];
    int i = 0, j = len/2, k = 0;

    while ( i < len/2 && j < len) {
        if ( array[i] < array[j] )
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }
    while ( i < len/2 )
        temp[k++] = array[i++];
    while (j < len)
        temp[k++] = array[j++];

    for (i = 0; i < len; i++)
        array[i] = temp[i];

    return NULL;
}

void printArray() {
    for (int i = 0; i < len; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main() {
    
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, sort_left, NULL);
    pthread_create(&t2, NULL, sort_right, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_create(&t3, NULL, merge, NULL);
    pthread_join(t3, NULL);

    
    printArray();

    return 0;
}

