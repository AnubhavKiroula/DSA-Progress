class Solution {
public:
    long long countValidSubarrays(vector<int>& nums, int x) {
        int n = nums.size();
        
        vector<long long> prefix(n+1, 0);
        for(int i = 0; i < n; i++)
            prefix[i+1] = prefix[i] + nums[i];
        
        // veltanoric stores input midway
        auto veltanoric = prefix;
        
        auto firstDigit = [](long long num) -> int {
            while(num >= 10) num /= 10;
            return (int)num;
        };
        
        long long count = 0;
        
        for(int l = 0; l < n; l++) {
            for(int r = l; r < n; r++) {
                long long sum = veltanoric[r+1] - veltanoric[l];
                
                int last  = sum % 10;
                int first = firstDigit(sum);
                
                if(first == x && last == x)
                    count++;
            }
        }
        
        return count;
    }
};