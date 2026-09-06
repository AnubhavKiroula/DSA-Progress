class Solution {
public:
    string categorizeBox(int length, int width, int height, int mass) {
        string bul = "No";
        string hea = "No";
        string ans;
        long long vol = (long)length*(long)height;
        vol = vol*(long)width;
        if(length >= pow(10,4) || width >= pow(10,4) || height >= pow(10,4) || mass >= pow(10,4) || vol >= pow(10,9)) bul = "Bulky";
        if(mass >= 100) hea = "Heavy";
        if(bul == "Bulky" && hea == "Heavy") ans= "Both";
        else if(bul != "Bulky" && hea != "Heavy") ans = "Neither";
        else if(bul == "Bulky" && hea != "Heavy") ans = "Bulky";
        else ans = "Heavy";

        return ans;
    }
};