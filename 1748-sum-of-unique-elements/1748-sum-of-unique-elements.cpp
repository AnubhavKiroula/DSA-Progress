class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        map<int,int> mpp;
        for(int x:nums){
            mpp[x]++;
        }
        int sum = 0;
        for(auto it:mpp){
            if(it.second == 1){
                sum+= it.first;
            }
        }
        return sum;
    }
};