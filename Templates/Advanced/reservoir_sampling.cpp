https://gregable.com/2007/10/reservoir-sampling.html

vector<int> reservoirSampling(vector<int>& nums, int k) {
    vector<int> res(k);
    const int n = nums.size();
    for (int i = 0; i < k; ++i) {
        res[i] = nums[i];
    }
    for (int i = k; i < n; ++i) {
        int random = rand() % i;  // [0, i - 1]
        if (random < k) {  // 概率是 k / i
            res[random] = nums[i];
        }
    }
    return res;
}
