class Solution {
public:
    int duplicateNumbersXOR(vector<int>& nums) {
        unordered_map<int,int> mpp;
        int ans=0;
        for(int x:nums){
            if(mpp[x]){
                ans = ans^x;
            }
            mpp[x]++;
        }
        return ans;
    }
};