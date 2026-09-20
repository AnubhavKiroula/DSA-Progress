class Solution {
public:
    int encrypt(int x){
        int maxi = 0;
        int cnt =0;
        while(x>0){
            int dig = x%10;
            cnt++;
            maxi = max(maxi,dig);
            x /= 10;
        }
        if(cnt == 4) return 1111;
        else if(cnt == 3) return (maxi*100+maxi*10+maxi);
        else if(cnt == 2) return (maxi*10+maxi);
        else return maxi;
    }
    int sumOfEncryptedInt(vector<int>& nums) {
        int sum = 0;
        for(int x:nums){
            sum+= encrypt(x);
        }
        return sum;
    }
};