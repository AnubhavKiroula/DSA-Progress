class Solution {
public:
    string trafficSignal(int timer) {
        string ans;
        if(timer == 0){
            ans = "Green";
        }else if(timer == 30){
            ans = "Orange";
        }else if(timer > 30 && timer <= 90){
            ans = "Red";
        }else ans = "Invalid";
        return ans;
    }
};