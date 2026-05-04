#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void displayArray(int nums[], int length)
{
    cout << "Array : [";
    for (int i = 0; i < length; i++)
    {
        cout << nums[i];
        if (i < length - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}


void minOperation(int nums[], int length)
{
    int minValue = nums[0];
#pragma omp parallel for reduction(min : minValue)
    for (int i = 0; i < length; i++)
    {
        if (nums[i] < minValue)
        {
            minValue = nums[i];
        }
    }
    cout << "Min Value :" << minValue << endl;
}

void maxOperation(int nums[], int length)
{
    int maxValue = nums[0];
#pragma omp parallel for reduction(max : maxValue)
    for (int i = 0; i < length; i++)
    {
        if (nums[i] > maxValue)
        {
            maxValue = nums[i];
        }
    }
    cout << "Max Value :" << maxValue << endl;
}


void sumOperation(int nums[], int length)
{
    int sumValue = 0;
#pragma omp parallel for reduction(+ : sumValue)
    for (int i = 0; i < length; i++)
    {
        sumValue = sumValue + nums[i];
    }
    cout << "Sum Value:" << sumValue << endl;
}


void avgOperation(int nums[], int length)
{
    int sumValue = 0;
#pragma omp parallel for reduction(+ : sumValue)
    for (int i = 0; i < length; i++)
    {
        sumValue = sumValue + nums[i];
    }
    cout << "Average Value:" << (sumValue / length) << endl;
}

int main() {

    int length = 1000;
    int nums[length];
    for (int i = 0; i < length; i++)
    {
        nums[i] = i;
    }

    

    // displayArray(nums,length);

    cout << "Parallel Operations" << endl;

    auto start_parallel = high_resolution_clock::now();

    minOperation(nums,length);
    maxOperation(nums,length);
    sumOperation(nums,length);
    avgOperation(nums,length);

    auto stop_parallel = high_resolution_clock::now();
    auto duration_parallel = duration_cast<microseconds>(stop_parallel - start_parallel).count();
    cout << "Execution Time : "<<duration_parallel<< " microseconds" << endl;
}