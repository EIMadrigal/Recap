class LRUCache {
public:
    LRUCache(int capacity) : capacity_(capacity) {}

    int get(int key) {
        auto it = map_.find(key);
        if (it == map_.end()) {
            return -1;
        }
        cache_.splice(cache_.begin(), cache_, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = map_.find(key);
        if (it != map_.end()) {
            it->second->second = value;
            cache_.splice(cache_.begin(), cache_, it->second);
        } else {
            if (map_.size() == capacity_) {
                map_.erase(cache_.back().first);
                cache_.pop_back();
            }
            cache_.push_front({key, value});
            map_[key] = cache_.begin();
        }
    }

private:
    int capacity_;
    list<pair<int, int>> cache_;  // list node stores (key, val) pair
    unordered_map<int, list<pair<int, int>>::iterator> map_;  // key -> node iterator
};

class LRUCache {
private:
    struct ListNode {
        int key, val;
        ListNode* prev, *next;
        ListNode() : key(0), val(0), prev(nullptr), next(nullptr) {}
        ListNode(int key, int val) : key(key), val(val), prev(nullptr), next(nullptr) {}
    };

    int capacity_;
    ListNode *head_, *tail_;
    unordered_map<int, ListNode*> map_;

public:
    LRUCache(int capacity) : capacity_(capacity) {
        head_ = new ListNode();
        tail_ = new ListNode();
        head_->next = tail_;
        tail_->prev = head_;
    }

    int get(int key) {
        if (map_.find(key) == map_.end()) {
            return -1;
        }
        ListNode* node = map_[key];
        _remove(node);
        _addHead(node);
        return node->val;
    }

    void put(int key, int value) {
        if (map_.find(key) != map_.end()) {
            ListNode* cur = map_[key];
            cur->val = value;
            _remove(cur);
            _addHead(cur);
            return;
        }
        if (map_.size() == capacity_) {
            ListNode* removed = tail_->prev;
            _remove(removed);
            map_.erase(removed->key);
            delete removed;
        }
        ListNode *node = new ListNode(key, value);
        _addHead(node);
        map_[key] = node;   
    }

    void _remove(ListNode* cur) {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
    }

    void _addHead(ListNode* cur) {
        cur->prev = head_;
        cur->next = head_->next;
        head_->next->prev = cur;
        head_->next = cur;
    }
};
