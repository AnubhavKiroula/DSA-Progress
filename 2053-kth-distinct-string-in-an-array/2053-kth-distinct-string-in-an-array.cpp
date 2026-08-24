class Solution {
public:
    string kthDistinct(vector<string>& arr, int k) {
        map<string,int> mpp;
        for(string s : arr){
            mpp[s]++;
        }
        int cnt = 0;
        for(string s : arr){
            if(mpp[s] == 1){
                cnt++;
                if(cnt == k) return s;
            }
        }
        return "";
    }
};
