class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans;
        int cnt1 =0 , cnt2=0;
        int el1 = INT_MIN;
        int el2 = INT_MIN;
        int chk1 = 0 , chk2=0;
        int min = (int)(n/3) +1;
        for(int i=0;i<n;i++){
            if(cnt1 == 0 && el2 != nums[i]){
                cnt1= 1;
                el1 = nums[i];
            }else if(cnt2 == 0 && el1 != nums[i]){
                cnt2= 1;
                el2 = nums[i];
            }
            else if(el1 == nums[i]) cnt1++;
            else if(el2 == nums[i]) cnt2++;
            else{
                cnt1-- , cnt2--;
            }
        }
        for(int i=0;i<n;i++){
            if(el1 ==nums[i]){
                chk1++;
            }
            if(el2 == nums[i]){
                chk2++;
            }
        }
        if(chk1 >= min){
            ans.emplace_back(el1);
        }
        if(chk2 >= min){
            ans.emplace_back(el2);
        }
        sort(ans.begin() , ans.end());
        return ans;
    }
};