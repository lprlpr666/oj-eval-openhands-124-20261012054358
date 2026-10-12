#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    vector<int> lazy;
    int n;
    
    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = 0;
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }
    
    void update_range(int node, int start, int end, int l, int r, int val) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        
        if (start > r || end < l) {
            return;
        }
        
        if (start >= l && end <= r) {
            tree[node] += val;
            if (start != end) {
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
            return;
        }
        
        int mid = (start + end) / 2;
        update_range(2 * node, start, mid, l, r, val);
        update_range(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }
    
    int query_range(int node, int start, int end, int l, int r) {
        if (start > r || end < l) {
            return 0;
        }
        
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        
        if (start >= l && end <= r) {
            return tree[node];
        }
        
        int mid = (start + end) / 2;
        int left_max = query_range(2 * node, start, mid, l, r);
        int right_max = query_range(2 * node + 1, mid + 1, end, l, r);
        return max(left_max, right_max);
    }
    
public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        build(1, 1, n);
    }
    
    void update(int l, int r, int val) {
        update_range(1, 1, n, l, r, val);
    }
    
    int query(int l, int r) {
        return query_range(1, 1, n, l, r);
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, k, p;
    if (!(cin >> x >> k >> p)) {
        return 0;
    }
    
    // We need to track seat usage for segments between stations
    // There are x-1 segments: segment i goes from station i to i+1
    SegmentTree st(x - 1);
    
    for (int order = 0; order < p; order++) {
        int u, v, n;
        cin >> u >> v >> n;
        
        // Query maximum seat usage in the range [u, v-1]
        int max_usage = st.query(u, v - 1);
        
        if (max_usage + n <= k) {
            // Order can be fulfilled, update seat usage
            st.update(u, v - 1, n);
            cout << "T\n";
        } else {
            cout << "N\n";
        }
    }
    
    return 0;
}