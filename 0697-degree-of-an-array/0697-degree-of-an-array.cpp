class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int,int> freq, first, last;
        int degree = 0;
        
        for(int i=0; i<nums.size(); ++i){
            int x = nums[i];
            if(!first.count(x)) first[x] = i;
            last[x] = i;
            degree = max(degree, ++freq[x]);
        }
        
        int ans = nums.size();
        for(auto it : freq){
            if(it.second == degree){
                int len = last[it.first] - first[it.first] + 1;
                ans = min(ans, len);
            }
        }
        return ans;
    }
};
