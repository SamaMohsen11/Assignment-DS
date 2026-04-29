#include <iostream>
using namespace std;

template <typename T>
class BitonicArray
{
private:
    T *arr;
    int arr_size;

    T *bitonic_array;

    T *splitted_arr_1;
    int splitted_arr_1_size;

    T *splitted_arr_2;
    int splitted_arr_2_size;

    int comparisons;
    int swaps;

    void splitArray()
    {
        for (int i = 0; i < splitted_arr_1_size; ++i)
            splitted_arr_1[i] = arr[i];

        for (int i = 0; i < splitted_arr_2_size; ++i)
            splitted_arr_2[i] = arr[splitted_arr_1_size + i];
    }

    void bubbleSort(T *a, int size)
    {
        int new_size = size;
        bool swapped_flag;

        for (int i = 0; i < size - 1; ++i)
        {
            swapped_flag = false;
            for (int j = 0; j < new_size - 1; ++j)
            {
                comparisons++;
                if (a[j] > a[j + 1])
                {
                    swap(a[j], a[j + 1]);
                    swapped_flag = true;
                    swaps++;
                }
            }
            new_size--;
            if (!swapped_flag)
                break;
        }
    }

    void selectionSort(T *a, int n)
    {
        int maxIdx;
        for (int i = 0; i < n - 1; ++i)
        {
            maxIdx = i;
            for (int j = i + 1; j < n; ++j)
            {
                comparisons++;
                if (a[j] > a[maxIdx])
                    maxIdx = j;
            }
            if (maxIdx != i)
            {
                T temp = a[i];
                a[i] = a[maxIdx];
                a[maxIdx] = temp;
                swaps++;
            }
        }
    }

    void combineArrays()
    {
        for (int i = 0; i < splitted_arr_1_size; ++i)
            bitonic_array[i] = splitted_arr_1[i];

        for (int i = 0; i < splitted_arr_2_size; ++i)
            bitonic_array[splitted_arr_1_size + i] = splitted_arr_2[i];
    }

public:
    BitonicArray(int size)
        : arr_size(size), comparisons(0), swaps(0)
    {
        arr = new T[arr_size];
        bitonic_array = new T[arr_size];

        splitted_arr_1_size = arr_size / 2;
        splitted_arr_2_size = arr_size - splitted_arr_1_size;

        splitted_arr_1 = new T[splitted_arr_1_size];
        splitted_arr_2 = new T[splitted_arr_2_size];
    }

    ~BitonicArray()
    {
        delete[] arr;
        delete[] bitonic_array;
        delete[] splitted_arr_1;
        delete[] splitted_arr_2;
    }

    void inputArray()
    {
        for (int i = 0; i < arr_size; ++i)
        {
            cout << "Enter element " << (i + 1) << ": ";
            cin >> arr[i];
        }
    }

    void buildBitonicArray()
    {
        comparisons = 0;
        swaps = 0;

        splitArray();
        bubbleSort(splitted_arr_1, splitted_arr_1_size);
        selectionSort(splitted_arr_2, splitted_arr_2_size);
        combineArrays();
    }

    int Search(T target)
    {
        for (int i = 0; i < arr_size; ++i)
            if (bitonic_array[i] == target)
                return i;
        return -1;
    }

    int getBitonicPointIndex()
    {
        int maxIdx = 0;
        for (int i = 1; i < arr_size; ++i)
            if (bitonic_array[i] > bitonic_array[maxIdx])
                maxIdx = i;
        return maxIdx;
    }

    void printArray()
    {
        cout << "Bitonic Array : ";
        for (int i = 0; i < arr_size; ++i)
            cout << bitonic_array[i] << " ";
        cout << endl;
    }

    void printStats()
    {
        cout << "Comparisons   : " << comparisons << endl;
        cout << "Swaps         : " << swaps << endl;
    }

    void printBitonicPoint()
    {
        int idx = getBitonicPointIndex();
        cout << "Bitonic Point : index=" << idx
             << ", value=" << bitonic_array[idx] << endl;
    }
};

int main()
{
    //Test 1 — Target at the bitonic point
    // BitonicArray<int> BA_1(7);
    // BA_1.inputArray();
    // BA_1.buildBitonicArray();
    // BA_1.printArray();
    // BA_1.printBitonicPoint();
    // cout << BA_1.Search(9);
    // cout << "\n========================================================================\n";


    //Test 2 — Target in the left half (ascending portion)
    // BitonicArray<int> BA_1(7);
    // BA_1.inputArray();
    // BA_1.buildBitonicArray();
    // BA_1.printArray();
    // BA_1.printBitonicPoint();
    // cout << BA_1.Search(2);
    // cout << "\n========================================================================\n";


    //Test 3 — Target in the right half (descending portion)
    // BitonicArray<int> BA_1(7);
    // BA_1.inputArray();
    // BA_1.buildBitonicArray();
    // BA_1.printArray();
    // BA_1.printBitonicPoint();
    // cout << BA_1.Search(3);
    // cout << "\n========================================================================\n";


    //Test 4 — Target not present
    // BitonicArray<int> BA_1(7);
    // BA_1.inputArray();
    // BA_1.buildBitonicArray();
    // BA_1.printArray();
    // BA_1.printBitonicPoint();
    // cout << BA_1.Search(99);
    // cout << "\n========================================================================\n";


    //Test 5 — Duplicate elements
    // BitonicArray<int> BA_1(7);
    // BA_1.inputArray();
    // BA_1.buildBitonicArray();
    // BA_1.printArray();
    // BA_1.printBitonicPoint();
    // cout << BA_1.Search(5);
    // cout << "\n========================================================================\n";
}