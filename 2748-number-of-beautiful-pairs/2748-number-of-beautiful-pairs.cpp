class Solution {
public:
    int gcd(int x,int y){
        if(y == 0) return x;
        else return gcd(y,x%y);
    }
    int lastdigit(int x){
        return x%10;
    }
    int firstdigit(int x){
        vector<int> ans;
        while(x>0){
            ans.emplace_back(x%10);
            x = x/10;
        }
        return ans[ans.size()-1];
    }
    int countBeautifulPairs(vector<int>& nums) {
        int n = nums.size();
        int cnt =0;
        for(int i=0;i<n;++i){
            for(int j=i+1;j<n;++j){
                if(gcd(firstdigit(nums[i]),lastdigit(nums[j])) == 1) cnt++;
            }
        }
        return cnt;
    }
};