class Solution {
public:

    vector<string> ans;

    void backtrack(string& s, int index, int leftRem, int rightRem,
                   int balance, string& current) {

        if (index == s.size()) {
            if (leftRem == 0 && rightRem == 0 && balance == 0) {
                ans.push_back(current);
            }
            return;
        }

        char c = s[index];

        if (c == '(') {

            if (leftRem > 0) {
                backtrack(s, index + 1, leftRem - 1, rightRem,
                          balance, current);
            }

            current.push_back('(');

            backtrack(s, index + 1, leftRem, rightRem,
                      balance + 1, current);

            current.pop_back();
        }

        else if (c == ')') {

            if (rightRem > 0) {
                backtrack(s, index + 1, leftRem, rightRem - 1,
                          balance, current);
            }

            if (balance > 0) {
                current.push_back(')');

                backtrack(s, index + 1, leftRem, rightRem,
                          balance - 1, current);

                current.pop_back();
            }
        }

        else {
            current.push_back(c);

            backtrack(s, index + 1, leftRem, rightRem,
                      balance, current);

            current.pop_back();
        }
    }


    vector<string> removeInvalidParentheses(string s) {

        int leftRem = 0;
        int rightRem = 0;

        for (char c : s) {

            if (c == '(') {
                leftRem++;
            }
            else if (c == ')') {

                if (leftRem > 0) {
                    leftRem--;
                }
                else {
                    rightRem++;
                }
            }
        }

        string current = "";

        backtrack(s, 0, leftRem, rightRem, 0, current);

        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        return ans;
    }
};