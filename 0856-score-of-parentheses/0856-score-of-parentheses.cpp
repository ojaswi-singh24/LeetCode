class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0);
        for(char c : s){
            if(c == '('){
                st.push(0);
            }else{
                int val = st.top();
                st.pop();
                int score = (val==0)?1:2*val;
                st.top() += score;
            }
        }
        return st.top();
    }
};