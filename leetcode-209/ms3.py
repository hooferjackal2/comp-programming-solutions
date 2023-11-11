import random
import time


def minSubArrayLen(target, nums) -> int:
    mlen = 0
    arr_sum = 0
    # First pass - naively find a range that works
    while arr_sum < target and mlen < len(nums):
        arr_sum += nums[mlen]
        mlen += 1
    # If no valid solution
    if arr_sum < target:
        return 0
    # Start searching for a (mlen - 1) solution
    offset = 0
    arr_sum -= nums[mlen-1]
    while mlen + offset <= len(nums):
        arr_sum += nums[mlen + offset - 1] - nums[offset]
        offset += 1
        while arr_sum >= target:
            arr_sum -= nums[offset]
            offset += 1
            mlen -= 1
    return mlen


testlist = []
for i in range(1, 5000):
    testlist.append(random.randint(1, 20))
t0 = time.time()
for i in range(25000, 50000):
    _ = minSubArrayLen(i, testlist)
t1 = time.time()
print(t1 - t0)
