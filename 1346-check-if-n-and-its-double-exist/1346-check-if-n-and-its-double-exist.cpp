class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        unordered_map<int,int> mpp;
        for(int x:arr){
            mpp[x]++;
        }
        if(mpp[0] >1) return true;
        
        for(int i=0;i<arr.size()-1;++i)
            for(int j=i+1;j<arr.size();++j){
                if(arr[i] == 2*arr[j] || arr[j] == 2*arr[i]) return true;
            }
        
        return false;
    }
};