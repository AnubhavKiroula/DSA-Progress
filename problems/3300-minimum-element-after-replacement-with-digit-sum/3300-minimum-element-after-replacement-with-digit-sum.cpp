class Solution {
public:
    int minElement(vector<int>& nums) {
        vector<int> ans;
        for(int i=0;i<nums.size();i++){
            int sum=0;
            int n=nums[i];
            while(n>0){
                sum +=n%10;
                n = n/10;
            }
            ans.emplace_back(sum);
        }
        int small = ans[0];
        for(int x : ans){
            if(x < small){
                small = x;
            }
        }
        return small;
    }
};