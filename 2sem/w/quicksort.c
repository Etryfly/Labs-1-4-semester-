


void quickSort(int *arr, int size) {
    int ix = size / 2;
    for (int i = 0; i < ix; ++i) {
        swap(arr[i])
    }
}

void swap(int *a, int *b) {
    int **tmp = &a;
    *a = *b;
    *b = **tmp;
}