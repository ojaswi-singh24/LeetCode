class Solution {
public:
    int minAddToMakeValid(string s) {
        stack<int> st;
        int count=0;
        for(char c : s){
            if(c == '('){
                st.push(c);
            } else{
                if(!st.empty()){
                    st.pop();
                }else{
                    count++;
                }
                
            }
        }
        if(!st.empty()){
            count+=st.size();
        }
        return count;
    }
};