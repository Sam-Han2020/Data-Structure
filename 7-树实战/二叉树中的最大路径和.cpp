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
        int result = -2147483648;
    
        int max(int a,int b)
        {
            return a > b ? a : b;
        }
    
        int dfs(TreeNode *root)
        {
            if(root == NULL) return 0;
            if(root->left==NULL && root->right==NULL)
            {
                result = max(root->val,result);
                return max(root->val,0);
            }
            int leftmax = max(dfs(root->left) , 0);
            int rightmax = max(dfs(root->right) , 0);
            result = max(leftmax + rightmax + root->val , result);
            return max(leftmax,rightmax) + root->val;
        }
    
        int maxPathSum(TreeNode* root) {
            dfs(root);
            return result;
        }
    };