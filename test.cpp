#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

struct SumRenderer {
protected:
   vector<int> nums;

public:
   void add(const int num) {
      nums.push_back(num);
   }

   int sum() { 
      return accumulate(nums.begin(), nums.end(), 0); 
   }
};

struct SingleValue : SumRenderer
{
  SingleValue() = default;

  explicit SingleValue(const int value)
  {
     add(value);
  }
};

struct ManyValues : SumRenderer 
{
   ManyValues() = default;

   explicit ManyValues(const int value)
   {
      add(value);
   }
};


int sum(const vector<SumRenderer *> items) {
   int result {0};
   for (auto &i : items) {
      result += i->sum();
   }
   return result;
}

int main() {
   SingleValue single_value {1};
   ManyValues other_values;
   other_values.add(2);
   other_values.add(3);
   
   cout << "Sum: " << sum({ &single_value, &other_values}) << endl;
   return 0;
}
