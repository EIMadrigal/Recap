// 一维
// [l,r]区间和：preSum[r + 1] - preSum[l]
vector<int> preSum(n + 1, 0);
for (int i = 1; i <= n; ++i) {
    preSum[i] = preSum[i - 1] + nums[i - 1];
}


// 二维
// (x1,y1) -> (x2,y2)区间和：
// preSum[x2+1][y2+1] - preSum[x2][y2+1] - preSum[x2+1][y2] + preSum[x2][y2]
vector<int> preSum(m + 1, vector<int>(n + 1, 0));
for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
        preSum[i][j] = preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1] + nums[i - 1][j - 1];
    }
}
