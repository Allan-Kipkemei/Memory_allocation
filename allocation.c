#include <stdlib.h>
#include <stdio.h>

int main() {
    int *arr = (int *)malloc(5 * sizeof(int));  // Allocate memory for 5 integers
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);  // End program if memory allocation fails
    }
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 2;
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    free(arr);  // Free the allocated memory
    return 0;
}
