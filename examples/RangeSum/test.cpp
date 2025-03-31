#include "TestFramework.h"

#include "RangeSum.h"

TEST(RangeSumTest100M) {

    const int seed = 1234;
    srand(seed);
    
    const int size = 1000000000;

    // crate a 100 million element array
    std::vector<int> arr(size);
    int expectedSum = 0;
    // fill the array with random numbers
    for (int i = 0; i < size; i++) {
        // random sign
        arr[i] = (rand() % 2 == 0 ? 1 : -1) * (rand() % 100);

        expectedSum += arr[i];
    }

    
    TIME_TEST("Standard Implementation Test", [&]() {

        // test the range sum function
        int sum = RangeSum(arr, 0, size - 1);
        // check if the sum is correct
        EXPECT_EQ(sum, expectedSum);

    });

    TIME_TEST("SIMD Implementation Test", [&]() {

        // test the range sum function
        int sum = RangeSum_SIMD(arr, 0, size - 1);
        // check if the sum is correct
        EXPECT_EQ(sum, expectedSum);

    });


}