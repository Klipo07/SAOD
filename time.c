#include "sort.c"

int main() {
  int PrintArrays = 0;
  int step = 50000;
  int steps = 20;
  int n = step;
  int min_rand = 0, max_rand = 100000;

  char *result_str = (char *)malloc(200 * steps);
  int size_str = 0;

  printf("Size\t\tCounting\t\tBubble\t\tMerge\n");
  sprintf(result_str, "Size\t\tCounting\t\tBubble\t\tMerge\n");

  for (; n <= step * steps; n += step) {

    uint32_t *counting_arr = (uint32_t *)malloc(sizeof(uint32_t) * n);
    uint32_t *bubble_arr = (uint32_t *)malloc(sizeof(uint32_t) * n);
    uint32_t *merge_arr = (uint32_t *)malloc(sizeof(uint32_t) * n);

    for (int i = 0; i < n; i++) {
      int tmp = getrand(min_rand, max_rand);
      counting_arr[i] = tmp;
      bubble_arr[i] = tmp;
      merge_arr[i] = tmp;
    }

    double start;
    double func_time[3] = {0.f, 0.f, 0.f};

    start = wtime();
    countingSort(counting_arr, n);
    func_time[0] = wtime() - start;

    start = wtime();
    bubbleSort(bubble_arr, 0, n - 1);
    func_time[1] = wtime() - start;

    start = wtime();
    mergeSort(merge_arr, n);
    func_time[2] = wtime() - start;
    if (PrintArrays) {
      printf("\nCountingSort\tBubbleSort\tMergeSort: \n");
      for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d \n", counting_arr[i], bubble_arr[i], merge_arr[i]);
      }
    }
    printf("%d\t\t%f\t%f\t%f \n", n, func_time[0], func_time[1], func_time[2]);
    size_str = strlen(result_str);
    sprintf(result_str + size_str, "%d\t\t%f\t%f\t%f \n", n, func_time[0],
            func_time[1], func_time[2]);
  }
  FILE *file = fopen("sort.dat", "w");
  fprintf(file, result_str);
  fclose(file);
  return 0;
}