class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int n = arr.size();
        for(int i=0;i<n-1;++i){
            int max = arr[i+1];
            for(int j=i+1;j<n;++j){
                if(arr[j] > max) max = arr[j];
            }
            arr[i] = max;
        }
        arr[n-1] = -1;
        return arr;
    }
};