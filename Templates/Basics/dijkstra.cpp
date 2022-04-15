// 邻接矩阵
vector<int> dijkstra(vector<vector<int>>& g, int s) {
    int n = g.size();
    vector<int> dis(n, INT_MAX);
    vector<bool> vis(n, false);
    dis[s] = 0;
    
    for (int i = 0; i < n; ++i) {
        // 寻找未访问点中dis最小的
        int minIdx = -1, minDis = INT_MAX;
        for (int j = 0; j < n; ++j) {
            if (!vis[j] && dis[j] < minDis) {
                minDis = dis[j], minIdx = j;
            }
        }
        // 剩余的点与起点不连通
        if (minIdx == -1) return {};
        vis[minIdx] = true;  // 锁死当前的最小点
        // 以minIdx为中介试图优化dis[j]
        for (int j = 0; j < n; ++j) {
            // 未锁死、j可达、路过minIdx可以使dis[j]更优
            if (!vis[j] && g[minIdx][j] != INT_MAX && dis[minIdx] + g[minIdx][j] < dis[j])
                dis[j] = dis[minIdx] + g[minIdx][j];
        }
    }
    return dis;
}

// 邻接表
vector<int> dijkstra(vector<vector<pair<int, int>>>& g, int s) {
    int n = g.size();
    vector<int> dis(n, INT_MAX);
    vector<bool> vis(n, false);
    dis[s] = 0;
    
    for (int i = 0; i < n; ++i) {
        // 寻找未访问点中dis最小的
        int minIdx = -1, minDis = INT_MAX;
        for (int j = 0; j < n; ++j) {
            if (!vis[j] && dis[j] < minDis) {
                minDis = dis[j], minIdx = j;
            }
        }
        
        if (minIdx == -1) return {};
        vis[minIdx] = true;
        // 直接获得minIdx能到达的点
        for (int j = 0; j < g[minIdx].size(); ++j) {
            int w = g[minIdx][j].first, id = g[minIdx][j].second;
            if (!vis[id] && dis[minIdx] + w < dis[id])
                dis[id] = dis[minIdx] + w;
        }
    }
    return dis;
}

// 邻接表 + 堆优化
typedef pair<int, int> p;
vector<int> dijkstra(vector<vector<p>>& g, int s) {
    int n = g.size();
    vector<int> dis(n, INT_MAX), parent(n);
    vector<bool> vis(n, false);
    dis[s] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        int minIdx = pq.top().second, minDis = pq.top().first;
        pq.pop();
        if (vis[minIdx]) continue;
        vis[minIdx] = true;
        for (auto adj : g[minIdx]) {
            if (!vis[adj.second] && dis[minIdx] + adj.first < dis[adj.first]) {
                dis[adj.first] = dis[minIdx] + adj.first;
                pq.push({dis[adj.first], adj.second});
                parent[adj.second] = minIdx;
            }
        }
    }
    return dis;
}
