class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
       int total=0;
       unordered_map<int,int> mpp;
       int freq=0;
       for(int x:nums){
        mpp[x]++;
        freq = max(freq,mpp[x]);
       } 
       for(auto it:mpp){
        if(it.second == freq){
            total += it.second;
        }
       }
       return total;
    }
};