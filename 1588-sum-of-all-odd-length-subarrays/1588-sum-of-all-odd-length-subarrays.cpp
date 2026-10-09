class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int curSum = 0;
            for (int j=i;j<n;++j) {
                curSum += arr[j];
                int len = j-i+1;
                if (len % 2 != 0) {
                    ans += curSum;
                }
            }
        }
        return ans;
    }
};