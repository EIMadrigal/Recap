// BFS + 邻接表
bool topologicalSort(vector<vector<int>>& g, vector<int>& indegree) {
    int n = g.size(), cnt = 0;
    queue<int> q;  // 若有多个入度为0的顶点要选择编号最小的，可使用priority_queue
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {
        int cur = q.front(); q.pop();
        ++cnt;
        cout << cur << endl;  // 输出拓扑序列
        for (auto nei : g[cur]) {
            if (--indegree[nei] == 0)
                q.push(nei);
        }
    }
    return cnt == n;  // 排序成功, 否则有环
}

// DFS + 邻接表
bool topologicalSort(vector<vector<int>>& g) {
    int n = g.size();
    vector<int> vis(n, 0);  // 0 -> UNKNOWN, 1 -> VISITING, 2 -> VISITED
    for (int i = 0; i < n; ++i) {
        if (vis[i] == 0)
            if (dfs(g, vis, i))
                return false;  // 有环
    }
    return true;
}

bool dfs(vector<vector<int>>& g, vector<int>& vis, int u) {
    if (vis[u] == 1) return true;  // 有环
    if (vis[u] == 2) return false;
    vis[u] = 1;
    for (auto nei : g[u]) {
        if (dfs(g, vis, nei))
            return true;
        }
    vis[u] = 2;
    cout << u << "\n";  // 输出拓扑序列逆序
    return false;
}
