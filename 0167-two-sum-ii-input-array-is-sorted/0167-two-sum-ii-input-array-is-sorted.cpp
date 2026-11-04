class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ans;
        int n = numbers.size();
        int left = 0;
        int right = n-1;
        while(left<right){
            int sum = numbers[left] + numbers[right];
            if(sum == target){
                ans.emplace_back(left+1);
                ans.emplace_back(right+1);
                return ans;
            }
            else if(sum < target) left++;
            else right--;
        }
        return ans;
    }
};