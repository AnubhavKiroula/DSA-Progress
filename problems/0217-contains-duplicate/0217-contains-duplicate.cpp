class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> check;
        for(int n : nums){
            if(check.count(n)){
                return true;
            }
            check.insert(n);
        }
        return false;
    }
};