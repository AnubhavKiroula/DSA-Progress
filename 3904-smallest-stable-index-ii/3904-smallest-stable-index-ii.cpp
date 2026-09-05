class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> Maxele(n), Minele(n);

        Maxele[0] = nums[0];
        for (int i = 1; i < n; ++i)
            Maxele[i] = max(Maxele[i - 1], nums[i]);

        Minele[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i)
            Minele[i] = min(Minele[i + 1], nums[i]);

        for (int i = 0; i < n; ++i) {
            int score = Maxele[i] - Minele[i];
            if (score <= k)
                return i;
        }
        return -1;
    }
};
