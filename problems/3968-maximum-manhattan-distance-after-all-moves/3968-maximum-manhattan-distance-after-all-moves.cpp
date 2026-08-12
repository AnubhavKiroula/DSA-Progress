class Solution {
public:
    int maxDistance(string moves) {
        int U=0, D=0, L=0, R=0, W=0;
        for(char c : moves) {
            if(c=='U') U++;
            else if(c=='D') D++;
            else if(c=='L') L++;
            else if(c=='R') R++;
            else W++;
        }
        
        int best = 0;
        // Try assigning all wildcards to each direction
        int dirs[4][4] = {{W,0,0,0},{0,W,0,0},{0,0,W,0},{0,0,0,W}};
        //                  wu  wd  wl  wr
        for(auto& d : dirs) {
            int x = (R+d[3]) - (L+d[2]);
            int y = (U+d[0]) - (D+d[1]);
            best = max(best, abs(x)+abs(y));
        }
        return best;
    }
};