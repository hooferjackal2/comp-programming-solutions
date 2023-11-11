#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int modifiedCmp(int int1, int int2){
    int int1save = int1;
    int int2save = int2;
    int place1 = 1;
    int place2 = 1;
    while (place1 <= (int1 / 10)){
      place1 *= 10;
    }
    while (place2 <= (int2 / 10)){
      place2 *= 10;
    }
    int firstDgt1 = int1 / place1;
    int firstDgt2 = int2 / place2;
    while (place1 > 0 && place2 > 0){
      if (int1 / place1 > int2 / place2){
        return 1;
      } else if (int1 / place1 < int2 / place2){
        return 0;
      } else {
        int1 %= place1;
        int2 %= place2;
        place1 /= 10;
        place2 /= 10;
      }
    }
    if (place1 == 0 && place2 == 0){
      return 0;
    } else if (place1 == 0 && int2 == 0){
      return 1;
    } else if (place2 == 0 && int1 == 0){
      return 0;
    } else if (place1 == 0 && int2 / place2 == 0){
      return 1;
    } else if (place2 == 0 && int1 / place1 == 0){
      return 0;
    } else if (place1 == 0){
      return modifiedCmp(int1save, int2);
    } else { //  place2 == 0
      return modifiedCmp(int1, int2save);
    }
}

void modifiedMergeSort(int* nums, int startIdx, int endIdx){
    if (startIdx < endIdx - 1){
        int midIdx = (startIdx + endIdx) / 2;
        modifiedMergeSort(nums, startIdx, midIdx);
        modifiedMergeSort(nums, midIdx, endIdx);
        int *tmpArr = malloc(sizeof(int) * (endIdx - startIdx)); 
        for (int i = 0; i < endIdx - startIdx; i++){
          tmpArr[i] = nums[i + startIdx];
        }
        int idx1 = startIdx;
        int idx2 = midIdx;
        for (int i = startIdx; i < endIdx; i++){
          if (idx1 == midIdx){
            nums[i] = tmpArr[idx2 - startIdx];
            idx2++;
          } else if (idx2 == endIdx){
            nums[i] = tmpArr[idx1 - startIdx];
            idx1++;
          } else if (modifiedCmp(tmpArr[idx1 - startIdx], tmpArr[idx2 - startIdx])){
            nums[i] = tmpArr[idx1 - startIdx];
            idx1++;
          } else {
            nums[i] = tmpArr[idx2 - startIdx];
            idx2++;
          }
        }
    }
}

char * largestNumber(int* nums, int numsSize){
    int totalLen = 0;
    for (int i = 0; i < numsSize; i++){
        int num = nums[i];
        totalLen++;
        while (num >= 10){
            totalLen++;
            num /= 10;
        }
    }
    modifiedMergeSort(nums, 0, numsSize);
    char *numStr = malloc(sizeof(int) * (totalLen + 1)); // Maximum possible string length
    numStr[0] = '\0';
    char buf[12];
    int leadingZero = 1;
    for (int i = 0; i < numsSize; i++){
      if (nums[i] == 0 && leadingZero && i < (numsSize - 1)){
        continue;
      }
      leadingZero = 0;
      sprintf(buf, "%d", nums[i]);
      strcat(numStr, buf);
    }
    return numStr;
}

int main(int argc, char *argv){
  printf("Hello World\n");
  int testArr1[] = {4704,6306,9385,7536,3462,4798,5422,5529,8070,6241,
                    9094,7846, 663,6221, 216,6758,8353,3650,3836,8183,
                    3516,5909,6744,1548,5712,2281,3664,7100,6698,7321,
                    4980,8937,3163,5784,3298,9890,1090,7605,1380,1147,
                    1495,3699,9448,5208,9456,3846,3567,6856,2000,3575,
                    7205,2697,5972,7471,1763,1143,1417,6038,2313,6554,
                    9026,8107,9827,7982,9685,3905,8939,1048, 282,7423,
                    6327,2970,4453,5460,3399,9533, 914,3932, 192,3084,
                    6806, 273,4283,2060,5682,   2,2362,4812,7032, 810,
                    2465,6511, 213,2362,3021,2745,3636,6265,1518,8398};
  printf("%s\n", largestNumber(testArr1, 100));
  return 0;
}
