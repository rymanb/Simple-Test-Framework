#include "RangeSum.h"
#include <immintrin.h>

int RangeSum(const std::vector<int>& arr, int start, int end)
{
    // check if the array is empty
    if (arr.empty()) {
        return 0;
    }

    int size = static_cast<int>(arr.size());

    // validate start and end
    if (start < 0 || end < 0 || start >= size || end >= size || start > end) {
        return 0;
    }

    // calculate the sum
    int sum = 0;
    for (int i = start; i <= end; i++) {
        // check for overflow or underflow

        // add the current element to the sum
        sum += arr[i];
    }

    // return the sum
    return sum;
}

int RangeSum_SIMD(const std::vector<int>& arr, int start, int end)
{
    // check for empty array
    if (arr.empty()) return 0;

    // make sure range is valid 
    if (start < 0 || end >= static_cast<int>(arr.size()) || start > end)
        return 0;

    const int* data = arr.data() + start;
    int count = end - start + 1;
    // multiple of 8 for SIMD because each avx2 register is 256 bits so can hold 8 32-bit integers at a time
    int simdLength = count - (count % 8); 

    __m256i sumVec = _mm256_setzero_si256();

    // SIMD sum
    // handle 8 elements at a time for reasons mentioned above
    // a possible optimization here could be to use several avx2 registers at a time and unwind the loop
    // to handle more than 8 elements at a time but that would probably be overkill for this problem

    // this loop essentially grabs 8 elements at a time and sums them on top of the sumVec
    // for example lets say we do 3 at a time, the sumVec would look like this after each iteration:
    // arr = [0, 1, 2, 3, 0, 4], range = (0, 5)
    // [0, 0, 0] -> [0, 1, 2] -> [3, 1, 6]
    for (int i = 0; i < simdLength; i += 8) {
        __m256i vec = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(data + i));
        sumVec = _mm256_add_epi32(sumVec, vec);
    }

    // store the sumVec in an array to extract the values
    // length of 8 because we are summing 8 elements at a time so can't have any more or less
    // we align to 32 bytes because the store operation requires it or else it will throw a segfault
    alignas(32) int temp[8];
    _mm256_store_si256(reinterpret_cast<__m256i*>(temp), sumVec);

    
    // sum the 8 elements in the temp array
    int sum = 0;
    for (int i = 0; i < 8; ++i) {
        sum += temp[i];
    }

    // if we had any left over elements that didnt fill the 8 int registers then we need to add them to the sum
    for (int i = simdLength; i < count; ++i) {
        sum += data[i];
    }

    return sum;
}