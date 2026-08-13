#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int prefix, suffix, max_len, len;
    char left_char, right_char;
};

class Solution {
private:
    vector<Node> tree;
    string s;

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = {1, 1, 1, 1, s[start], s[start]};
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    Node merge(const Node& left, const Node& right) {
        Node res;
        res.left_char = left.left_char;
        res.right_char = right.right_char;
        res.len = left.len + right.len;

        res.prefix = left.prefix;
        if (left.prefix == left.len && left.right_char == right.left_char) {
            res.prefix += right.prefix;
        }

        res.suffix = right.suffix;
        if (right.suffix == right.len && right.left_char == left.right_char) {
            res.suffix += left.suffix;
        }

        res.max_len = max({
            left.max_len, 
            right.max_len, 
            (left.right_char == right.left_char ? left.suffix + right.prefix : 0)
        });
        
        return res;
    }

    void update(int node, int start, int end, int idx, char val) {
        if (start == end) {
            s[idx] = val;
            tree[node] = {1, 1, 1, 1, val, val};
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        this->s = s;
        int n = s.length();
        tree.resize(4 * n);
        build(1, 0, n - 1);

        vector<int> ans;
        int q = queryIndices.size();
        for (int i = 0; i < q; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans.push_back(tree[1].max_len);
        }
        return ans;
    }
};