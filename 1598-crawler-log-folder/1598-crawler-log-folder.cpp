class Solution {
public:
    int minOperations(vector<string>& logs) {
        vector<string> cnt;
        for (string log : logs) {
            if (log == "../") {
                if (!cnt.empty()) {
                    cnt.pop_back();
                }
            } else if (log != "./") {
                cnt.push_back(log);
            }
        }
        return cnt.size();
    }
};