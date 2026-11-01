class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        const int MOD = 1e9 + 7;

        // dp[i][j][0] = ways entering (i,j) from left
        // dp[i][j][1] = ways entering (i,j) from above

        vector<vector<vector<long long>>> dp(
            m + 1,
            vector<vector<long long>>(n + 1, vector<long long>(2, 0))
        );

        dp[0][0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                long long right = dp[i][j][0];
                long long down = dp[i][j][1];

                if (grid[i][j] == 0) {

                    long long total = (right + down) % MOD;

                    // Move right
                    dp[i][j + 1][0] =
                        (dp[i][j + 1][0] + total) % MOD;

                    // Move down
                    dp[i + 1][j][1] =
                        (dp[i + 1][j][1] + total) % MOD;

                } 
                else {

                    // Entered mirror moving right:
                    // Reflect down
                    dp[i + 1][j][1] =
                        (dp[i + 1][j][1] + right) % MOD;

                    // Entered mirror moving down:
                    // Reflect right
                    dp[i][j + 1][0] =
                        (dp[i][j + 1][0] + down) % MOD;
                }
            }
        }

        return (dp[m - 1][n - 1][0] +
                dp[m - 1][n - 1][1]) % MOD;
    }
};