class Difference {
public:
    Difference(vector<int>& nums) {
        diff = vector<int>(nums.size(), 0);
        diff[0] = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            diff[i] = nums[i] - nums[i - 1];
        }
    }

    // for every num in [i, j] increase delta
    void increament(int i, int j, int delta) {
        diff[i] += delta;
        if (j + 1 < diff.size()) {
            diff[j + 1] -= delta;
        }
    }

    vector<int> getArr() {
        vector<int> ans(diff.size(), 0);
        ans[0] = diff[0];
        for (int i = 1; i < ans.size(); ++i) {
            ans[i] = ans[i - 1] + diff[i];
        }
        return ans;
    }
private:
    vector<int> diff;
};
