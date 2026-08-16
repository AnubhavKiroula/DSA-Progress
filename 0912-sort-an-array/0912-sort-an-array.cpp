class Solution {
public:
    int partition(vector<int>& arr , int low , int high){
        int pivot = arr[low];
        int i = low;
        int j = high;
        while (i<j){
            while (arr[i] <= pivot && i <=high-1){
                i++;
            }
            while(arr[j] > pivot && j >=low+1){
                j--;
            }
            if(i<j){
                swap(arr[i] , arr[j]);
            }
        }
        swap(arr[low] , arr[j]);
        return j;
    }
    void qs(vector<int>& arr , int low , int high){
            if(low<high){
                int p_idx = partition(arr ,low , high );
                qs(arr, low, p_idx-1);
                qs(arr, p_idx+1, high);
            }
    }
    vector<int> sortArray(vector<int>& nums) {
        qs(nums , 0 , nums.size() -1);
        return nums;
    }
};