#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_elements(int * elements, int qty){
    printf("[");
    for (int i = 0; i < qty; i++){
        if (qty > 50){
            if ((i < 10) || (i > qty - 10)){
                printf("%d", elements[i]);
                if(i != qty-1){printf(",");}
            } else if (i < 11){printf(" ");
            } else if (i < 14){printf(".");
            } else if (i < 15){printf(" ,");}
        } else {
            printf("%d", elements[i]);
            if(i != qty-1){printf(",");}
        }
    }
    printf("]");
}

int * insertion_sort(int * elements, int qty){
    int i = 0, j = 0, tmp = 0;

    for (i = 1; i < qty; i++){
        j = i - 1;
        tmp = elements[i];
        while ((j >= 0) && (tmp < elements[j])){
            elements[j+1] = elements[j];
            j--;
        }
        elements[j+1] = tmp;
    }
    return elements;
}

int * selection_sort(int * elements, int qty){
    int i = 0, j = 0, min_idx = 0, tmp = 0; 

    for (i = 0; i < qty-1; i++){ 
        min_idx = i; 
        for (j = i+1; j < qty; j++) 
        if (elements[j] < elements[min_idx]){
            min_idx = j; 
        }
        tmp = elements[min_idx];
        elements[min_idx] = elements[i];
        elements[i] = tmp;
    } 
    return elements;
}

void merge(int *elements, int left, int mid, int right)
{
    int left_qty = mid - left + 1;
    int right_qty = right - mid;
    int left_list[left_qty], right_list[right_qty];

    for (int i = 0; i < left_qty; i++){
        left_list[i] = elements[left + i];
    }
    for (int j = 0; j < right_qty; j++){
        right_list[j] = elements[mid + 1 + j];
    }
 
    int i = 0;
    int j = 0;
    int k = left;
 
    while (i < left_qty && j < right_qty) {
        if (left_list[i] <= right_list[j]) {
            elements[k] = left_list[i];
            i++;
        } else {
            elements[k] = right_list[j];
            j++;
        }
        k++;
    }
 
    while (i < left_qty) {
        elements[k] = left_list[i];
        i++;
        k++;
    }
 
    while (j < right_qty) {
        elements[k] = right_list[j];
        j++;
        k++;
    }
}

void merge_sort(int *elements,int left,int right){
    int mid = left + (right - left) / 2;
    if(left >= right){
        return;
    }
    merge_sort(elements, left, mid);
    merge_sort(elements, mid + 1, right);
    merge(elements, left, mid ,right);
}

void quick_sort(int * elements, int left, int right){
    int mid = 0, tmp = 0, i = left, j = right;
    mid = elements[(left + right) / 2];
    do {
        while (elements[i] < mid){i++;}
        while (elements[j] > mid){j--;}
        if (i <= j){
            tmp = elements[i];
            elements[i] = elements[j];
            elements[j] = tmp;
            i++;
            j--;
        }
    } while ( i <= j);
    if(left < j){quick_sort(elements, left, j);}
    if(i < right){quick_sort(elements, i, right);}
}

double get_time_interval(struct timespec begin, struct timespec end){
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    return seconds + nanoseconds*1e-9;
}

int check_ordering(int * elements, int qty){
    int i  = 0;
    while (i < qty) {
        if (i != qty - 1) {
            if ((elements[i] - elements[i+1]) > 0){
                return 0;
            }
        }
        i++;
    }
    return 1;
}

void print_report(char *title, int * elements, int qty, double time_interval){
    printf("\n%s", title);
    printf("\nElements: ");
    print_elements(elements, qty);
    if (check_ordering(elements, qty)){
        printf("\nIt is ordered correctly.");
    } else {
        printf("\nIt is not ordered correctly.");
    }
    printf("\nProcessing time interval: %lf seconds\n", time_interval);
}


int main(int argc, char const *argv[])
{
    int qty = 0, *disordered_elements, *insertion_sort_elements, *selection_sort_elements, *merge_sort_elements, *quick_sort_elements;
    double insertion_sort_time_interval, selection_sort_time_interval, merge_sort_time_interval, quick_sort_time_interval;
    struct timespec begin, end;

    srand(time(NULL));

    printf("Enter the number of elements desired: ");
    scanf("%d", &qty);

    disordered_elements = (int *) malloc(sizeof(int) * qty);
    if(!disordered_elements){printf("Error: Memory fault!"); return 1;}

    insertion_sort_elements = (int *) malloc(sizeof(int) * qty);
    if(!insertion_sort_elements){printf("Error: Memory fault!"); return 1;}

    selection_sort_elements = (int *) malloc(sizeof(int) * qty);
    if(!selection_sort_elements){printf("Error: Memory fault!"); return 1;}

    merge_sort_elements = (int *) malloc(sizeof(int) * qty);
    if(!merge_sort_elements){printf("Error: Memory fault!"); return 1;}

    quick_sort_elements = (int *) malloc(sizeof(int) * qty);
    if(!quick_sort_elements){printf("Error: Memory fault!"); return 1;}

    printf("\nDisordered elements: [");
    for (int i = 0; i < qty; i++){
        disordered_elements[i] = rand() % (qty*2);

        insertion_sort_elements[i] = disordered_elements[i];
        selection_sort_elements[i] = disordered_elements[i];
        merge_sort_elements[i] = disordered_elements[i];
        quick_sort_elements[i] = disordered_elements[i];

        printf("%d", disordered_elements[i]);
        if(i != (qty - 1)){printf(",");}
    }
    printf("]\n");

    printf("\n > Running Insertion Sort...\n");
    clock_gettime(CLOCK_REALTIME, &begin);
    insertion_sort_elements = insertion_sort(insertion_sort_elements, qty);
    clock_gettime(CLOCK_REALTIME, &end);
    insertion_sort_time_interval = get_time_interval(begin, end);
    print_report("Insertion Sort", insertion_sort_elements, qty, insertion_sort_time_interval);
    
    printf("\n > Running Selection Sort...\n");
    clock_gettime(CLOCK_REALTIME, &begin);
    selection_sort_elements = selection_sort(selection_sort_elements, qty);
    clock_gettime(CLOCK_REALTIME, &end);
    selection_sort_time_interval = get_time_interval(begin, end);
    print_report("Selection Sort", selection_sort_elements, qty, selection_sort_time_interval);
    
    printf("\n > Running Merge Sort...\n");
    clock_gettime(CLOCK_REALTIME, &begin);
    merge_sort(merge_sort_elements, 0, qty-1);
    clock_gettime(CLOCK_REALTIME, &end);
    merge_sort_time_interval = get_time_interval(begin, end);
    print_report("Merge Sort", merge_sort_elements, qty, merge_sort_time_interval);
    
    printf("\n > Running Quick Sort...\n");
    clock_gettime(CLOCK_REALTIME, &begin);
    quick_sort(quick_sort_elements, 0, qty - 1);
    clock_gettime(CLOCK_REALTIME, &end);
    quick_sort_time_interval = get_time_interval(begin, end);
    print_report("Quick Sort", quick_sort_elements, qty, quick_sort_time_interval);

    printf("\n------------- Performance comparison --------------");
    printf("\n  Algorithm  |   Correctly ordered   |  Performance");
    printf("\n---------------------------------------------------");
    printf("\n  Insertion  |           %d           |  %lf seconds", check_ordering(insertion_sort_elements, qty), insertion_sort_time_interval);
    printf("\n  Selection  |           %d           |  %lf seconds", check_ordering(selection_sort_elements, qty), selection_sort_time_interval);
    printf("\n  Merge      |           %d           |  %lf seconds", check_ordering(merge_sort_elements, qty), merge_sort_time_interval);
    printf("\n  Quick      |           %d           |  %lf seconds", check_ordering(quick_sort_elements, qty), quick_sort_time_interval);
    printf("\n---------------------------------------------------");
    printf("\nLabels: 1 = True; 0 = False\n");

    free(disordered_elements);
    free(insertion_sort_elements);
    free(selection_sort_elements);
    free(merge_sort_elements);
    free(quick_sort_elements);

    return 0;
}
