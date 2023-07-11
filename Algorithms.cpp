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

int* insertionSort(int* original, int size, int start) {
    int value, j;
    for (int i = start + 1; i < size; i++) {
        value = original[i];
        j = i - 1;

        while (j >= start && original[j] > value) {
            original[j + 1] = original[j];
            j--;
        }
        original[j + 1] = value;
    }
    return original;
}
int* quickSort(int* original, int start, int end) {
    int initialpivot = original[start];
    int aux;
    original[start] = original[end - 1];
    original[end - 1] = initialpivot;
    int leftStop = -1;
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
    if (leftStop == -1 && start<end-1) {
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
int* bubbleSort(int* original, int size) {
    int aux;
    size = size - 1;
    while(size>0) {
        for (int i = 0; i < size; i++) {
            if (original[i] > original[i + 1]) {
                aux = original[i];
                original[i] = original[i + 1];
                original[i + 1] = aux;
            }
        }
        size--;
    }
    return original;
}
int* timSort(int* original, int size) {
    int elements = 32;
    int a = size % elements;
    int* result = new int[size];
    for (int i = 0; i < size/elements; i ++) {
        insertionSort(original, elements * (i+1), elements * i);
    }
    if (a != 0)
        insertionSort(original, size, size - a);
    int count = 0;
    while (true) {
        int k = elements * (count * 2);
        if (k >= size) {
            k = 0;
            count = 0;
            elements += elements;
        }
        int leftsize = elements;
        if (leftsize >= size)
            break;
        int rightsize = leftsize;
        int l = k + elements;
        int initialk = k;
        if (l+elements > size){
            rightsize = size - l;
        }
        for (int j = 0; j < leftsize+rightsize; j++) {
            if (k- initialk >= leftsize) {
                result[j] = original[l];
                l++;
            }
            else {
                if (l- initialk >= rightsize+elements) {
                    result[j] = original[k];
                    k++;
                }
                else {
                    if (original[k] <= original[l]) {
                        result[j] = original[k];
                        k++;
                    }
                    else {
                        result[j] = original[l];
                        l++;
                    }
                }
            }
        }
        for (int f = initialk; f < leftsize + rightsize+initialk; f++){
            original[f] = result[f- initialk];
        }
        count++;
    }
    return result;
}

int* initializeRandomArray(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int desired_max_value = 100000;

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
    std::cout << "f) Tim Sort" << "\n";

    std::cin >> selection;
    return selection;
}
int* callAlgorithm(char selection,int* arr,int size) {
    int* res{};
    switch (selection)
    {
    case 'a':
        res = insertionSort(arr, size,0);
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
        res = bubbleSort(arr, size);
        break;
    case 'f':
        res = timSort(arr, size);
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
    int size = 100000;
    int* arr = initializeRandomArray(size);

    char selection= menu();

    //start timer
    start = clock();
    int* result = callAlgorithm(selection,arr,size);
    end = clock();
    //end timer

    total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "CPU time used "<< total_time<<" seconds"<<"\n";

    bool correct = checkSort(result, size);
    (correct == true) ? std::cout << "Correctly sorted" : std::cout << "Incorrectly sorted";

    return 0;
}
