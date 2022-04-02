class LFUCache {
public:
    LFUCache(int _capacity) {
        capacity = _capacity;
    }

    int get(int key) {
        if (capacity == 0) {
            return -1;
        }
        auto it = keyTable.find(key);
        if (it == keyTable.end()) {
            return -1;
        }
        list<Node>::iterator node = it->second;
        int val = node->val, freq = node->freq;
        freqTable[freq].erase(node);

        if (freqTable[freq].size() == 0) {
            freqTable.erase(freq);
            if (freq == minFreq)
                minFreq++;
        }
        // 更新访问频率
        freqTable[freq + 1].push_front(Node(key, val, freq + 1));
        keyTable[key] = freqTable[freq + 1].begin();
        return val;
    }

    void put(int key, int val) {
        if (capacity == 0) {
            return;
        }
        auto it = keyTable.find(key);
        if (it != keyTable.end()) {
            auto node = it->second;
            node->val = val;
            int freq = node->freq;
            freqTable[freq].erase(node);

            if (freqTable[freq].size() == 0) {
                freqTable.erase(freq);
                if (freq == minFreq)
                    minFreq++;
            }
            // 更新访问频率
            freqTable[freq + 1].push_front(Node(key, val, freq + 1));
            keyTable[key] = freqTable[freq + 1].begin();
        }
        else {  // 插入新项
            if (keyTable.size() == capacity) {  // 换出目前使用频率最低的项
                auto old = freqTable[minFreq].back();
                freqTable[minFreq].pop_back();  // 从链表中删除
                keyTable.erase(old.key);  // 从keyTable中删除
                if (freqTable[minFreq].size() == 0) {  // 从freqTable中删除
                    freqTable.erase(minFreq);
                }
            }
            freqTable[1].push_front(Node(key, val, 1));
            keyTable[key] = freqTable[1].begin();
            minFreq = 1;
        }
    }

    struct Node {
        int key, val, freq;
        Node(int _key, int _val, int _freq) : key(_key), val(_val), freq(_freq) {}
    };

    int capacity;
    int minFreq;  // 目前的最低频率(1或单调增加)
    unordered_map<int, list<Node>::iterator> keyTable;
    unordered_map<int, list<Node>> freqTable;
};
