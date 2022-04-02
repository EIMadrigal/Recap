class UnionFind {
private:
    vector<int> parents_;
    vector<int> ranks_;

public:
    UnionFind(int n) {
        // 是否等于n取决于index从0开始还是从1开始
        for(int i = 0; i <= n; ++i) {
            parents_.emplace_back(i);
            ranks_.emplace_back(0);
        }
    }

    // get the root of x
    int find(int x) {
        // path compression
        if (x != parents_[x]) {
            parents_[x] = find(parents_[x]);
        }
        return parents_[x];
    }

    // merge set u and v
    // false -> u and v are already in one set
    bool merge(int u, int v) {
        int rootu = find(u);
        int rootv = find(v);
        if (rootu == rootv)
            return false;

        // merge low rank to high rank
        if (ranks_[rootu] < ranks_[rootv]) {
            parents_[rootu] = rootv;
        }
        else if (ranks_[rootu] > ranks_[rootv]) {
            parents_[rootv] = rootu;
        }
        else {
            parents_[rootu] = rootv;
            ++ranks_[rootv];
        }
        return true;
    }
};
