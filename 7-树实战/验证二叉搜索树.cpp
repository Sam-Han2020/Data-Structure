#include <iostream>
#include <stdlib.h>
#include <vector>
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

    bool isValidBST(TreeNode* root) {
        if(root == NULL) return false;
        vector<TreeNode*> stack;
        bool flag = true;
        int num = 0;
        while(root || stack.size()!=0)
        {
            while(root)
            {
                stack.push_back(root);
                root = root->left;
            }
            root = stack[stack.size()-1];
            stack.erase(stack.end());
            if(flag || root->val > num)
            {
                num = root->val;
                flag = false;
            }
            else return false;
            root = root->right;
        }
        return true;
    }

    // 以下为视频解法

    bool isValid(struct TreeNode* root, long min, long max){   //这里上界和下界用long表示，因为它的范围给到整个int，真是个老六
        if(root == NULL) return true;
        //这里还需要判断是否正常高于下界
        if(root->left != NULL && (root->left->val >= root->val || root->left->val <= min))
            return false;
        //这里还需判断一下是否正常低于上界
        if(root->right != NULL && (root->right->val <= root->val || root->right->val >= max))
            return false;
        return isValid(root->left, min, root->val) && isValid(root->right, root->val, max);
        //注意往左走更新上界，往右走更新下界
    }
    
    bool isValidBST(struct TreeNode* root){
        return isValid(root, -2147483649, 2147483648);   //下界刚好比int少1，上界刚好比int多1
    }
    
};