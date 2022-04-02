class BIT {
private:
    vector<int> prefixSum;
    static inline int lowbit(int x) {
        return x & (-x);
    }
public:
    BIT(int n) : prefixSum(n + 1, 0) {}

    void update(int i, int delta) {
        while (i < prefixSum.size()) {
            prefixSum[i] += delta;
            i += lowbit(i);
        }
    }

    int query(int i) {
        int ans = 0;
        while (i > 0) {
            ans += prefixSum[i];
            i -= lowbit(i);
        }
        return ans;
    }
};
