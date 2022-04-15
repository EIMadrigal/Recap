class SegmentTree {
public:
    struct TreeNode {
        TreeNode(int l, int r, int val) : start(l), end(r), val(val), left(nullptr), right(nullptr) {}
        ~TreeNode() {
            if (left) {
                delete left;
                left = nullptr;
            }
            if (right) {
                delete right;
                right = nullptr;
            }
        }
        int start, end, val;  // val can be sum, min, max...
        TreeNode* left, *right;
    };
    
    TreeNode* buildTree(vector<int>& nums, int l, int r) {
        if (l == r) {
            return new TreeNode(l, r, nums[l]);
        }
        int m = l + (r - l) / 2;
        TreeNode* lef = buildTree(nums, l, m);
        TreeNode* rig = buildTree(nums, m + 1, r);
        TreeNode* root = new TreeNode(l, r, lef->val + rig->val);
        root->left = lef, root->right = rig;
        return root;
    }

    void update(TreeNode* root, int i, int newVal) {
        if (root->start == i && root->end == i) {
            root->val = newVal;
            return;
        }
        int m = root->start + (root->end - root->start) / 2;
        if (i <= m) {
            update(root->left, i, newVal);
        } else {
            update(root->right, i, newVal);
        }
        root->val = root->left->val + root->right->val;
    }

    int query(TreeNode* root, int l, int r) {
        if (l == root->start && r == root->end) {
            return root->val;
        }
        int m = root->start + (root->end - root->start) / 2;
        if (r <= m) {  // 查询范围完全落在左子树
            return query(root->left, l, r);
        } else if (l > m) {  // 查询范围完全落在右子树
            return query(root->right, l, r);
        } else {
            return query(root->left, l, m) + query(root->right, m + 1, r);
        }
        return 0;
    }
};
