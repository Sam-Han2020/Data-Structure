#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        if(root == NULL) return 0;
        int res = 0;
        res += rangeSumBST(root->left,low,high);
        if(root->val >= low && root->val <= high) res += root->val;
        res += rangeSumBST(root->right,low,high);
        return res;
    }
    
    // 视频解法
    int rangeSumBST(struct TreeNode* root, int low, int high){
        if(root == NULL) return 0;
        if(root->val > high)    //如果最大的值都比当前结点值小，那么肯定在左边才能找到
            return rangeSumBST(root->left, low, high);
        else if(root->val < low)   //如果最小值都比当前结点大，那么肯定在右边才能找到
            return rangeSumBST(root->right, low, high);
        else
            //这种情况肯定是在范围内了，将当前结点值加上左右的，再返回
            return root->val + rangeSumBST(root->right, low, high) + rangeSumBST(root->left, low, high);
    }
    
};

