class Solution {
public:
    int totalNumbers(vector<int>& digits) {

        // Count how many times each digit appears
        int freq[10] = {};

        for (int i = 0; i < digits.size(); i++) {
            freq[digits[i]]++;
        }

        int count = 0;

        // a = hundreds digit
        for (int a = 1; a <= 9; a++) {

            // b = tens digit
            for (int b = 0; b <= 9; b++) {

                // c = units digit (must be even)
                for (int c = 0; c <= 8; c += 2) {

                    // Count digits required for this number
                    int required[10] = {};

                    required[a]++;
                    required[b]++;
                    required[c]++;

                    bool possible = true;

                    // Check whether we have enough copies
                    for (int d = 0; d < 10; d++) {
                        if (required[d] > freq[d]) {
                            possible = false;
                            break;
                        }
                    }

                    if (possible) {
                        count++;
                    }
                }
            }
        }

        return count;
    }
};