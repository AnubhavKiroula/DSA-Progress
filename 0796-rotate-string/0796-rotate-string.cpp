class Solution {
public:
    bool rotateString(string s, string goal) {
        if(s.size() != goal.size()) return false;
        string con = s + s;
        if(con.find(goal) != string::npos) return true;
        else return false;
    }
};