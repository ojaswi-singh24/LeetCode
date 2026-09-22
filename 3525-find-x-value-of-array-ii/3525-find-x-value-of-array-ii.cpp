class Solution {
public:

    struct Node {
        int total;
        int cnt[5];

        Node() {
            total = 0;

            for (int i = 0; i < 5; i++) {
                cnt[i] = 0;
            }
        }
    };

    int n, k;
    vector<Node> tree;

    Node merge(Node &left, Node &right) {

        Node res;

        // Product of the whole combined segment
        res.total = (left.total * right.total) % k;

        // Prefixes completely inside left
        for (int r = 0; r < k; r++) {
            res.cnt[r] += left.cnt[r];
        }

        // Prefixes that contain all of left
        // and then some prefix of right
        for (int r = 0; r < k; r++) {

            int newRem = (left.total * r) % k;

            res.cnt[newRem] += right.cnt[r];
        }

        return res;
    }

    void build(int node, int l, int r, vector<int>& nums) {

        if (l == r) {

            int rem = nums[l] % k;

            tree[node].total = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = l + (r - l) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        tree[node] = merge(
            tree[node * 2],
            tree[node * 2 + 1]
        );
    }

    void update(int node, int l, int r, int index, int value) {

        if (l == r) {

            // Reset the node
            tree[node] = Node();

            int rem = value % k;

            tree[node].total = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = l + (r - l) / 2;

        if (index <= mid) {

            update(
                node * 2,
                l,
                mid,
                index,
                value
            );

        } else {

            update(
                node * 2 + 1,
                mid + 1,
                r,
                index,
                value
            );
        }

        tree[node] = merge(
            tree[node * 2],
            tree[node * 2 + 1]
        );
    }

    Node query(int node, int l, int r, int ql, int qr) {

        // Completely inside query range
        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int mid = l + (r - l) / 2;

        // Completely in left
        if (qr <= mid) {
            return query(
                node * 2,
                l,
                mid,
                ql,
                qr
            );
        }

        // Completely in right
        if (ql > mid) {
            return query(
                node * 2 + 1,
                mid + 1,
                r,
                ql,
                qr
            );
        }

        // Crosses both sides
        Node leftPart = query(
            node * 2,
            l,
            mid,
            ql,
            qr
        );

        Node rightPart = query(
            node * 2 + 1,
            mid + 1,
            r,
            ql,
            qr
        );

        return merge(leftPart, rightPart);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {

        this->k = k;
        n = nums.size();

        tree.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> answer;
        answer.reserve(queries.size());

        for (auto &q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            nums[index] = value;

            update(
                1,
                0,
                n - 1,
                index,
                value
            );

            // Get information for nums[start ... n-1]
            Node res = query(
                1,
                0,
                n - 1,
                start,
                n - 1
            );

            answer.push_back(res.cnt[x]);
        }

        return answer;
    }
};