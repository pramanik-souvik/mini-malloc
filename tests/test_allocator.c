#include <stdio.h>
#include <string.h>
#include "../src/my_alloc.h"

int main() {
    printf("Running allocator tests...\n");

    int* arr = (int*) my_malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) arr[i] = i * 10;

    printf("malloc test: ");
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    printf("\n");

    my_free(arr);

    char* text = (char*) my_calloc(10, sizeof(char));
    strcpy(text, "Hello");
    printf("calloc test: %s\n", text);
    my_free(text);

    char* buf = (char*) my_malloc(5);
    strcpy(buf, "Hi");
    buf = (char*) my_realloc(buf, 20);
    strcat(buf, ", world!");
    printf("realloc test: %s\n", buf);
    my_free(buf);

    return 0;
}