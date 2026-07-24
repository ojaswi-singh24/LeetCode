class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string merge;
        int minLength = min(word1.size(), word2.size());
        for(int i = 0; i< minLength; i++){
            merge = merge+word1[i]+word2[i];
        }
        return merge+word1.substr(minLength)+word2.substr(minLength);
    }
};