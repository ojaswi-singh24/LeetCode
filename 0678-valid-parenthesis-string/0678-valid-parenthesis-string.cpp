class Solution {
public:
    bool checkValidString(string s) {
       int low = 0;
       int high = 0;
       for(char c : s){
        if(c=='('){
            high++;
            low++;
        }else if ( c==')'){
            high--;
            low--;
        }else{
            high++;
            low--;
        }
        low = max(0, low);
        if(high<0){
            return false;
        }
       }
       return low == 0;
    }
};