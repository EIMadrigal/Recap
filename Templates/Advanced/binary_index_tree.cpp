// 一维
class BIT {
private:
    vector<int> prefix_sum_;
    static inline int lowbit(int x) {
        return x & (-x);
    }
public:
    BIT(int n) : prefix_sum_(n + 1, 0) {}

    void update(int i, int delta) {
        while(i < prefix_sum_.size()) {
            prefix_sum_[i] += delta;
            i += lowbit(i);  // add last set bit
        }
    }

    // compute nums[0] + nums[1] + ... + nums[i - 1]
    int query(int i) {
        int sum = 0;
        while(i > 0) {
            sum += prefix_sum_[i];
            i -= lowbit(i);  // flip the last set bit
        }
        return sum;
    }
};

// 二维
class BIT {
public:
    BIT(int m, int n) : prefix_sum_(m + 1, vector<int>(n + 1, 0)) {}

    void update(int i, int j, int delta) {
        for (int x = i; x < prefix_sum_.size(); x += lowbit(x))
            for (int y = j; y < prefix_sum_[0].size(); y += lowbit(y))
                prefix_sum_[x][y] += delta;
    }

    int query(int i, int j) {
        int ans = 0;
        for (int x = i; x > 0; x -= lowbit(x))
            for (int y = j; y > 0; y -= lowbit(y))
                ans += prefix_sum_[x][y];
        return ans;
    }

private:
    vector<vector<int>> prefix_sum_;  // 一维维护的是一个前缀和数组，二维维护一个前缀和矩阵
    static inline int lowbit(int x) {
        return x & (-x);
    }
};
