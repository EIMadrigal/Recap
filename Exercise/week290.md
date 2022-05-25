## 2248 Intersection of Multiple Arrays
我的做法：用`unordered_map`记录每个数的出现次数，排序频率等于`nums.size`的数返回
```cpp
class Solution {
public:
    vector<int> intersection(vector<vector<int>>& nums) {
        const int m = nums.size();
        unordered_map<int, int> freq;
        for (const auto& arr : nums) {
            for (int num : arr) {
                freq[num]++;
            }
        }
        vector<int> res;
        for (const auto& [k, v] : freq) {
            if (v == m) {
                res.push_back(k);
            }
        }
        sort(res.begin(), res.end());
        return res;
    }
};
```

## 2249 Count Lattice Points Inside a Circle
我的做法：用`set`去重，只判断右上1/4圆内的格点，根据对称性判断其他3/4圆。$O(nr^2)$
```cpp
class Solution {
public:
    int countLatticePoints(vector<vector<int>>& circles) {
        set<pair<int, int>> res;
        for (auto circle : circles) {
            int x = circle[0], y = circle[1], r = circle[2];
            for (int i = x; i <= x + r; ++i) {
                for (int j = y; j <= y + r; ++j) {
                    if ((i - x) * (i - x) + (j - y) * (j - y) <= r * r) {
                        res.insert(make_pair(i, j));
                        res.insert(make_pair(i, 2 * y - j));
                        res.insert(make_pair(2 * x - i, j));
                        res.insert(make_pair(2 * x - i, 2 * y - j));   
                    }
                }
            }
        }
        return res.size();
    }
};
```

## 2250 Count Number of Rectangles Containing Each Point
我的做法：注意到高度范围$[1,100]$，因此可以统计每个高度的矩形并按照长度排序，对每个点$(x,y)$从高度y向上遍历，在每个高度二分即可。$O(nlgn)$
```cpp
class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        vector<vector<int>> recs(101);
        for (auto rec : rectangles) {
            recs[rec[1]].emplace_back(rec[0]);
        }
        for (int i = 1; i <= 100; ++i) {
            if (recs[i].size() > 1)
                sort(recs[i].begin(), recs[i].end());
        }
        vector<int> res(points.size(), 0);
        for (int i = 0; i < points.size(); ++i) {
            for (int j = points[i][1]; j <= 100; ++j) {
                if (!recs[j].empty()) {
                    auto it = lower_bound(recs[j].begin(), recs[j].end(), points[i][0]);
                    if (it != recs[j].end())
                        res[i] += recs[j].size() - (it - recs[j].begin());
                }
            }
        }
        return res;
    }
};
```

## 2251 Number of Flowers in Full Bloom
我的做法：假设花开不败，一个人可以看到`upper_bound`朵花。由于花儿凋零，`lower_bound`朵花就看不到了
```cpp
class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& persons) {
        vector<int> res(persons.size(), 0);
        vector<int> s(flowers.size()), e(flowers.size());
        for (int i = 0; i < flowers.size(); ++i) {
            s[i] = flowers[i][0], e[i] = flowers[i][1];
        }
        sort(s.begin(), s.end());
        sort(e.begin(), e.end());
        for (int i = 0; i < persons.size(); ++i) {
            auto it1 = upper_bound(s.begin(), s.end(), persons[i]);
            auto it2 = lower_bound(e.begin(), e.end(), persons[i]);
            res[i] = it1 - s.begin() - (it2 - e.begin());
        }
        return res; 
    }
};
```
