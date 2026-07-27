class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int current = 0;
        int highest = current;
        for (int altiGain: gain){
            current += altiGain;
            highest = max(highest, current);
        }
        return highest;
    }
};