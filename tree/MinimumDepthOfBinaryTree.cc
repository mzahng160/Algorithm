class Solution {
public:
    int run(TreeNode *root) {
        if(root == nullptr)
            return 0;
        if(root->left == nullptr)
            return run(root->right) + 1;
        if(root->right == nullptr)
            return run(root->left) + 1;
        int height_l = run(root->left) + 1;
        int height_r = run(root->right) + 1;
        return height_l < height_r ? height_l : height_r;
    }
};
