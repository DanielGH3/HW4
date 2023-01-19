#include "funcs.h"

int min(int a, int b){
    if (a > b) return b;
    return a;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int *arr, int *end) {
    int * start = arr;
    while (start < --end) {
        swap(start++, end);
    }
}
