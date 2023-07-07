#include <iostream>
#include <random>
#include <time.h>

void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << "   ";
    }
    std::cout <<"\n";

}

int* insertionSort(int* original, int size) {
    /*
    This algorithm compares two values and if they are not in the correct orther then you swap them and check
    if the new position of the swaped value is correct with the next one in the array.
    */
    int aux = 0;
    for (int i = 0; i < size-1; i++)
    {
        if (i < 0)
            i = 0;
        if (original[i] > original[i + 1]) {
            aux = original[i];
            original[i] = original[i + 1];
            original[i + 1] = aux;
            i -= 2;
        }
    }
    return original;
}
int* quickSort(int* original, int start, int end) {
    int initialpivot = original[start];
    int aux;
    original[start] = original[end - 1];
    original[end - 1] = initialpivot;
    int leftStop = 123456789;
    int rightStop = end - 2;
    bool found = false;
    for (int i = start; i < end; i++) {
        if (original[i] > initialpivot) {
            leftStop = i;
            for (int j = rightStop; j > leftStop; j--)
            {
                if (original[j] < initialpivot) {
                    found = true;
                    rightStop = j-1;
                    break;
                }
            }
            if (!found) {
                aux = original[end - 1];
                original[end - 1] = original[leftStop];
                original[leftStop] = aux;
                if(start<leftStop)
                    original = quickSort(original, start, leftStop);
                if(leftStop+1<end)
                    original = quickSort(original, leftStop + 1, end);
                break;
            }
            else {
                found = false;
                aux = original[rightStop+1];
                original[rightStop+1] = original[leftStop];
                original[leftStop] = aux;
            }
        }
    }
    if (leftStop == 123456789 && start<end-1) {
        original = quickSort(original, start, end-1);
    }
    return original;
}
int* selectionSort(int* original, int size) {
    int aux;
    int min = 123123123;
    int minindex = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++) {
            if (original[j] < min) {
                min = original[j];
                minindex = j;
            }
        }
        aux = original[i];
        original[i] = original[minindex];
        original[minindex] = aux;
        min = 123123123;
    }
    return original;
}
int* mergeSort(int* original, int size) {
    int* left = new int[size / 2];
    int* right = new int[size - size / 2];
    int* result = new int[size];

    if (size > 1) {
        int half = size / 2;
        for (int i = 0; i < size; i++){
            if (i < half)
                left[i] = original[i];
            else
                right[i-half] = original[i];
        }
        int leftsize = half;
        int rightsize = size-half;
        left = mergeSort(left, leftsize);
        right = mergeSort(right, rightsize);
        int k = 0;
        int l = 0;
        for (int j = 0; j < size; j++) {
            
            if (k >= leftsize) {
                result[j] = right[l];
                l++;
            }
            else {
                if(l>= rightsize) {
                    result[j] = left[k];
                    k++;
                }
                else {
                    if (left[k] <= right[l]) {
                        result[j] = left[k];
                        k++;
                    }
                    else {
                        result[j] = right[l];
                        l++;
                    }
                }
            }
        }
        return result;
    }
    return original;
}

int* initializeRandomArray(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int desired_max_value = 10000;

    std::uniform_int_distribution<> dis(0, desired_max_value);

    int* ar = new int[size];    

    for (int i = 0; i < size; i++) {
        ar[i] = dis(gen);
    }

    return ar;
}
char menu() {
    char selection;

    std::cout << "Select the desired Sorting method:" << "\n";
    std::cout << "a) Insertion Sort" << "\n";
    std::cout << "b) Quick Sort" << "\n";
    std::cout << "c) Selection Sort" << "\n";
    std::cout << "d) Merge Sort" << "\n";
    std::cout << "e) Bubble Sort" << "\n";

    std::cin >> selection;
    return selection;
}
int* callAlgorithm(char selection,int* arr,int size) {
    int* res{};
    switch (selection)
    {
    case 'a':
        res = insertionSort(arr, size);
        break;
    case 'b':
        res = quickSort(arr, 0,size);
        break;
    case 'c':
        res = selectionSort(arr, size);
        break;
    case 'd':
        res = mergeSort(arr, size);
        break;
    case 'e':
        break;
    case 'f':
        break;
    default:
        std::cout << "Invalid option..."<<"\n";
        break;
    }
    return res;
}
bool checkSort(int* ar, int size) {
    for (int i = 0; i < size - 1; i++)
    {
        if (ar[i] > ar[i + 1])
            return false;
    }
    return true;
}

int main() {
    clock_t start, end;
    double total_time;
    //int size = 10;
    int size = 100000;
    int* arr = initializeRandomArray(size);

    /*
    int* arr = new int[8];
    arr[0] = 5;
    arr[1] = 6;
    arr[2] = 8;
    arr[3] = 1;
    arr[4] = 3;
    arr[5] = 10;
    arr[6] = 4;
    arr[7] = 2;
    int size = 8;
    */

    char selection= menu();

    //printArr(arr, size);
    //start timer
    start = clock();
    int* result = callAlgorithm(selection,arr,size);
    end = clock();
    //end timer
    //printArr(result, size);

    total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "CPU time used "<< total_time<<" seconds"<<"\n";

    bool correct = checkSort(result, size);
    (correct == true) ? std::cout << "Correctly sorted" : std::cout << "Incorrectly sorted";

    return 0;
}
