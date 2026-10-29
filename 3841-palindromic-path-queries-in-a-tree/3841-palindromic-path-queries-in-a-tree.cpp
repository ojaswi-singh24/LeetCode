
class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> up(LOG, vector<int>(n, 0));
        vector<int> tin(n), tout(n), depth(n);
        int timer = 0;

        // Iterative DFS: avoid stack overflow on a long tree.
        vector<tuple<int, int, bool>> st;
        st.push_back({0, 0, false});

        while (!st.empty()) {
            auto [u, p, exit] = st.back();
            st.pop_back();

            if (exit) {
                tout[u] = timer;
                continue;
            }

            tin[u] = timer++;
            up[0][u] = p;

            for (int k = 1; k < LOG; k++) {
                up[k][u] = up[k - 1][up[k - 1][u]];
            }

            st.push_back({u, p, true});

            for (int i = (int)adj[u].size() - 1; i >= 0; i--) {
                int v = adj[u][i];
                if (v == p) continue;

                depth[v] = depth[u] + 1;
                st.push_back({v, u, false});
            }
        }

        auto isAncestor = [&](int u, int v) {
            return tin[u] <= tin[v] && tin[v] < tout[u];
        };

        auto lca = [&](int u, int v) {
            if (isAncestor(u, v)) return u;
            if (isAncestor(v, u)) return v;

            for (int k = LOG - 1; k >= 0; k--) {
                if (!isAncestor(up[k][u], v)) {
                    u = up[k][u];
                }
            }
            return up[0][u];
        };

        // Fenwick tree for range XOR updates and point queries.
        vector<int> bit(n + 2, 0);

        auto add = [&](int idx, int val) {
            for (; idx <= n + 1; idx += idx & -idx) {
                bit[idx] ^= val;
            }
        };

        auto rangeXor = [&](int l, int r, int val) {
            if (l > r) return;
            add(l + 1, val);
            add(r + 2, val);
        };

        auto pointQuery = [&](int pos) {
            int res = 0;
            for (int idx = pos + 1; idx > 0; idx -= idx & -idx) {
                res ^= bit[idx];
            }
            return res;
        };

        auto maskOf = [](char c) {
            return 1 << (c - 'a');
        };

        // Initialize each root-to-node path mask.
        for (int u = 0; u < n; u++) {
            rangeXor(tin[u], tout[u] - 1, maskOf(s[u]));
        }

        vector<bool> ans;

        for (const string &q : queries) {
            stringstream ss(q);
            string type;
            int u, v;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int delta = maskOf(s[u]) ^ maskOf(c);

                if (delta != 0) {
                    rangeXor(tin[u], tout[u] - 1, delta);
                    s[u] = c;
                }
            } else {
                ss >> v;

                int w = lca(u, v);

                int mask = pointQuery(tin[u])
                         ^ pointQuery(tin[v])
                         ^ maskOf(s[w]);

                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};
