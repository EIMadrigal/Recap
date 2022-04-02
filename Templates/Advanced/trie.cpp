// vector用c - 'a'快速定位孩子结点
class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    ~Trie() {
        if (root) {
            delete root;
        }
    }

    void insert(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            if (cur->children[c - 'a'] == nullptr) {
                cur->children[c - 'a'] = new TrieNode();
            }
            cur = cur->children[c - 'a'];
        }
        cur->isEnd = true;
    }

    bool search(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            if (cur->children[c - 'a'] == nullptr) {
                return false;
            }
            cur = cur->children[c - 'a'];
        }
        return cur->isEnd;
    }

    bool startWith(string prefix) {
        TrieNode* cur = root;
        for (char c : prefix) {
            if (cur->children[c - 'a'] == nullptr) {
                return false;
            }
            cur = cur->children[c - 'a'];
        }
        return true;
    }

private:
    struct TrieNode {
        TrieNode() : children(26, nullptr), isEnd(false) {}
        ~TrieNode() {
            for (TrieNode* child : children) {
                delete child;
            }
        }

        vector<TrieNode*> children;
        bool isEnd;
    };

    TrieNode* root;
};


// unordered_map用c定位孩子结点
class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    ~Trie() {
        if (root) {
            delete root;
        }
    }

    void insert(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            if (cur->children.find(c) == cur->children.end()) {
                cur->children[c] = new TrieNode();
            }
            cur = cur->children[c];
        }
        cur->isEnd = true;
    }

    bool search(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            if (cur->children.find(c) == cur->children.end()) {
                return false;
            }
            cur = cur->children[c];
        }
        return cur->isEnd;
    }

    bool startWith(string prefix) {
        TrieNode* cur = root;
        for (char c : prefix) {
            if (cur->children.find(c) == cur->children.end()) {
                return false;
            }
            cur = cur->children[c];
        }
        return true;
    }

private:
    struct TrieNode {
        TrieNode() : isEnd(false) {}
        ~TrieNode() {
            for (auto child : children) {
                if (child.second) {
                    delete child.second;
                }
            }
        }

        unordered_map<char, TrieNode*> children;
        bool isEnd;
    };

    TrieNode* root;
};
