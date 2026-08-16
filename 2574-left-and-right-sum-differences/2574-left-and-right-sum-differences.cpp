class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        vector<int> answer;
        int n = nums.size();
        vector<int> leftsum(n,0);
        vector<int> rightsum(n,0); 
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                leftsum[i] += nums[j];
            }
            for(int k=i+1;k<n;k++){
                rightsum[i] += nums[k];
            }
            answer.emplace_back(abs(leftsum[i] - rightsum[i]));
        }
        return answer;

    }
};