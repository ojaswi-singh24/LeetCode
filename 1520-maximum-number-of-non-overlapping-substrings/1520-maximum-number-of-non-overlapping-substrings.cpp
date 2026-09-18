
class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {

        int n = s.size();

        vector<int> first(26, n);
        vector<int> last(26, -1);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';

            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<vector<int>> intervals;

        for (int c = 0; c < 26; c++) {

            if (last[c] == -1)
                continue;

            int left = first[c];
            int right = last[c];

            bool valid = true;

            for (int i = left; i <= right; i++) {

                int x = s[i] - 'a';

                if (first[x] < left) {
                    valid = false;
                    break;
                }

                right = max(right, last[x]);
            }

            if (valid) {
                intervals.push_back({left, right});
            }
        }

        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        vector<string> ans;
        int prevEnd = -1;

        for (auto &interval : intervals) {

            int left = interval[0];
            int right = interval[1];

            if (left > prevEnd) {
                ans.push_back(s.substr(left, right - left + 1));
                prevEnd = right;
            }
        }

        return ans;
    }
};
