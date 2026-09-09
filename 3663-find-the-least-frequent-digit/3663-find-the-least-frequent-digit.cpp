class Solution {
public:
    int getLeastFrequentDigit(int n) {
        int minfre = INT_MAX;
        int ans;
        map<int,int> mpp;
        while(n > 0){
            int dig = n%10;
            mpp[dig]++;
            n = n/10;
        }
        for(auto it:mpp){
            if(it.second < minfre){
                minfre = it.second;
                ans = it.first;
            }
        }
        return ans;
    }
};