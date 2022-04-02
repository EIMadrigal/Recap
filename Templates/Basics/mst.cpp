struct Edge {
    int from, to, weight;
    bool operator == (const Edge& x) const {
        return weight == x.weight;
    }
};

struct EdgeHash {
    size_t operator () (const Edge& x) const {
        return x.from * 2 + x.to;
    }
};

unordered_set<Edge, EdgeHash> kruskalMST(int vertex_num, vector<Edge>& g) {
    unordered_set<Edge, EdgeHash> ans;
    std::sort(g.begin(), g.end(), [](const Edge& a, const Edge& b) {return a.weight < b.weight;});
    UnionFind uf(vertex_num);
    for (Edge& cur : g) {
        int u = uf.find(cur.from), v = uf.find(cur.to);
        if (u != v) {
            ans.insert(cur);
            uf.merge(u, v);
            if (ans.size() == vertex_num - 1) {
                break;
            }
        }
    }
    for (int i = 1; i < vertex_num; ++i) {
        if (uf.find(i) != uf.find(i + 1))
            cout << "不连通";
            return {};
    }
    return ans;
}

unordered_set<Edge, EdgeHash> primMST(vector<vector<int>>& g) {
    unordered_set<Edge, EdgeHash> ans;
    auto cmp = [](const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    };
    // 解锁边进入小根堆
    priority_queue<Edge, vector<Edge>, decltype(cmp)> smallq(cmp);
    unordered_set<int> nodeset;

    int cnt = 0;
    nodeset.insert(0);
    for (int j = 1; j < g.size(); ++j) {
        if (g[0][j] != INT_MAX)
            smallq.push({0, j, g[0][j]});  // 解锁该点的边
    }
    while (!smallq.empty()) {
        Edge cur = smallq.top(); smallq.pop();
        int to_node = cur.to;  // 可能新点
        if (nodeset.find(to_node) == nodeset.end()) {
            ans.insert(cur);
            ++cnt;
            nodeset.insert(to_node);
            if (cnt == g.size() - 1) break;
            for (int j = 0; j < g.size(); ++j) {
                if (g[to_node][j] != INT_MAX && nodeset.find(j) == nodeset.end())
                    smallq.push({to_node, j, g[to_node][j]});
            }
        }
    }
    for (int i = 0; i < g.size(); ++i) {
        if (nodeset.find(i) == nodeset.end()) {
            cout << "不连通";
            return {};
        }
    }
    return ans;
}

typedef pair<int, int> p;
int primMST(vector<vector<p>>& g) {
    int ans = 0;
    unordered_set<int> vis;
    priority_queue<p, vector<p>, greater<p>> smallq;
    
    int cnt = 0;
    vis.insert(0);
    for (int i = 0; i < g[0].size(); ++i) {
        smallq.push(g[0][i]);
    }
    while (!smallq.empty()) {
        p cur = smallq.top(); smallq.pop();
        if (vis.find(cur.second) == vis.end()) {
            ans += cur.first;
            vis.insert(cur.first);
        }
        for (int i = 0; i < g[cur.second].size(); ++i) {
            if (vis.find(g[cur.second][i].second) == vis.end()) {
                smallq.push(g[cur.second][i]);
            }
        }
    }
    for (int i = 0; i < g.size(); ++i) {
        if (vis.find(i) == vis.end()) {
            cout << "不连通";
            return -1;
        }
    }
    return ans;
}

// 最小生成森林
unordered_set<Edge, EdgeHash> primMSForest(vector<vector<int>>& g) {
    auto cmp = [](const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    };
    // 解锁边进入小根堆
    priority_queue<Edge, vector<Edge>, decltype(cmp)> smallq(cmp);
    unordered_set<int> nodeset;

    unordered_set<Edge, EdgeHash> ans;
    for (int i = 0; i < g.size(); ++i) {
        if (nodeset.find(i) == nodeset.end()) {
            nodeset.insert(i);
            for (int j = i + 1; j < g[i].size(); ++j) {
                if (g[i][j] != INT_MAX)
                    smallq.push({i, j, g[i][j]});  // 解锁该点的边
            }
            while (!smallq.empty()) {
                Edge cur = smallq.top(); smallq.pop();
                int to_node = cur.to;  // 可能新点
                if (nodeset.find(to_node) == nodeset.end()) {
                    ans.insert(cur);
                    nodeset.insert(to_node);
                    for (int j = 0; j < g.size(); ++j) {
                        if (g[to_node][j] != INT_MAX && nodeset.find(j) == nodeset.end())
                            smallq.push({to_node, j, g[to_node][j]});
                    }
                }
            }
        }
    }
    return ans;
}
