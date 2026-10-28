class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<bool>> dp(m * n, vector<bool>(1024, false));

        dp[0][grid[0][0]] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;

                int idx = i * n + j;
                int val = grid[i][j];

                if (i > 0) {
                    for (int x = 0; x < 1024; x++) {
                        if (dp[(i - 1) * n + j][x]) {
                            dp[idx][x ^ val] = true;
                        }
                    }
                }

                if (j > 0) {
                    for (int x = 0; x < 1024; x++) {
                        if (dp[i * n + j - 1][x]) {
                            dp[idx][x ^ val] = true;
                        }
                    }
                }
            }
        }

        int idx = (m - 1) * n + (n - 1);

        for (int x = 0; x < 1024; x++) {
            if (dp[idx][x]) return x;
        }

        return -1;
    }
};