#include<stack>
class Solution {
public:
    bool isValid(string s) {
        if(s.size()%2 != 0){
            return false;
        }
        stack<char> ans;
        for(int i=0;i<s.size();++i){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
                ans.push(s[i]);
            }else if (s[i] == ')' || s[i] == ']' || s[i] == '}' ){
                if(ans.empty() == false){
                    if(ans.top() == '{' && s[i] == '}') ans.pop();
                    else if(ans.top() == '(' && s[i] == ')') ans.pop();
                    else if(ans.top() == '[' && s[i] == ']') ans.pop();
                    else return false;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
        if(ans.empty()){
            return true;
        }else{
            return false;
        }
    }
};