#include <iostream>
using namespace std;

class SearchRotated {
public:
    int search(int arr[], int n, int target, int& comparisons) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        comparisons++;
        if (arr[mid] == target)
            return mid;

        comparisons += 2;
        if (arr[left] == arr[mid] && arr[mid] == arr[right]) {
            left++;
            right--;
        }
        else {
            comparisons++;
            if (arr[left] <= arr[mid]) {
                comparisons += 2;
                if (arr[left] <= target && target < arr[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else {
                comparisons += 2;
                if (arr[mid] < target && target <= arr[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
    }

    return -1;
    }
};

int main() {
    SearchRotated sr;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[100]; 

    cout << "Enter elements (rotated sorted array):\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int target;
    cout << "Enter element to search: ";
    cin >> target;

    int comparisons = 0;
    int result = sr.search(arr, n, target, comparisons);

    if (result != -1)
        cout << "Found at index: " << result << endl;
    else
        cout << "Not found\n";

    cout << "Comparisons: " << comparisons << endl;

    return 0;
}