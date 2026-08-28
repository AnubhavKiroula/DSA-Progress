class Solution {
public:
    long long minimalKSum(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        long long sum = 0;
        long long curr = 1;
        for(int x : nums){
            if(curr < x){
                long long take = min<long long>(k, x - curr);
                sum += (curr + curr + take - 1) * take / 2;
                k -= take;
                if(k == 0) return sum;
            }
            curr = (long long)x + 1;
        }
        if(k > 0){
            sum += (curr + curr + k - 1) * k / 2;
        }
        return sum;
    }
};
