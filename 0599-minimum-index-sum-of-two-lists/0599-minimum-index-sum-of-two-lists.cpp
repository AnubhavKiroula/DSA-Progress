class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        vector<string> ans;
        int minidx = INT_MAX;
        for (int i = 0; i < list1.size(); ++i) {
            auto j = find(list2.begin(), list2.end(), list1[i]);
            if (j != list2.end()) {
                int jidx = distance(list2.begin(), j);
                int idxsum = i + jidx;
                if (idxsum < minidx) {
                    minidx = idxsum;
                    ans.clear();
                    ans.push_back(list1[i]);
                } else if (idxsum == minidx) {
                    ans.push_back(list1[i]);
                }
            }
        }
        return ans;
    }
};