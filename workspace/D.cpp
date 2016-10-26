#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int p1 = 0, p2 = numbers.size()-1;
        while(true) {
            int s = numbers[p1] + numbers[p2];
            if (s == target) {
                vector<int> ans;
                ans.push_back(p1+1);
                ans.push_back(p2+1);
                return ans;
            } else if (s > target) {
                p2--;
            } else {
                p1++;
            }
        }
    }
};
