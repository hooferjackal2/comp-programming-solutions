#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

class Timer {
   private:
      // Type aliases to make accessing nested type easier
      using Clock = std::chrono::steady_clock;
      using Second = std::chrono::duration<double, std::ratio<1> >;

      std::chrono::time_point<Clock> m_beg { Clock::now() };

   public:
      void reset()
      {
         m_beg = Clock::now();
      }

      double elapsed() const
      {
         return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
      }
};

class Solver {
   public:
      int minSubArrayLen(int target, vector<int>& nums) {
         int mlen = 0;
         long arr_sum = 0;
         // First pass - naively find a range that works
         while (arr_sum < target && mlen < nums.size()){
            arr_sum += nums.at(mlen);
            mlen++;
         }
         // If no valid solution
         if (arr_sum < target){
            return 0;
         }
         // Start searching for a (mlen - 1) solution
         int offset = 0;
         arr_sum -= nums.at(mlen-1);
         while(mlen + offset <= nums.size()){
            arr_sum += nums.at(mlen + offset - 1) - nums.at(offset);
            offset++;
            while (arr_sum >= target){
               arr_sum -= nums.at(offset);
               offset++;
               mlen--;
            }
         }
         return mlen;
      }
};

int main(){
   Solver mySolver;
   vector<int> test_nums{};
   for (int i = 0; i < 5000; i++){
      test_nums.push_back(rand() % 20);
   }
   Timer t;
   for (int i = 25000; i < 50000; i++){
      int _ = mySolver.minSubArrayLen(i, test_nums);
   }
   std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";
   return 0;
}