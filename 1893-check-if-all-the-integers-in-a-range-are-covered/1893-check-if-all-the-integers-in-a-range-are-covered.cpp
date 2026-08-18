class Solution {
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        for(int x = left; x <= right; ++x) {
            bool covered = false;
            for(auto r : ranges) {
                if(r[0] <= x && x <= r[1]) {
                    covered = true;
                    break;
                }
            }
            if(!covered) return false;
        }
        return true;
    }
};