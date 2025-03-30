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
    
        bool is_leaf(TreeNode* node) {
            return node->left == NULL && node->right == NULL;
        }
    
        int sumNumbers(TreeNode* root) {
            if(root == NULL) return 0;
            TreeNode *node = root;
            int sum = 0;
            int sum0 = 0;
            vector<TreeNode*> stack;
            vector<bool> bstack;
            while(1)
            {
                if(node == NULL)
                {
                    if(stack.size()==0) break;
                    node = stack[stack.size()-1];
                    if(bstack[bstack.size()-1]==true)
                    {
                        node = node->right;
                        bstack[bstack.size()-1] = false;
                    }
                    else
                    {
                        if(is_leaf(node)) sum += sum0;
                        sum0 = (sum0 - node->val) / 10;
                        stack.pop_back();
                        bstack.pop_back();
                        node = NULL;
                    }
                }
                else
                {
                    stack.push_back(node);
                    bstack.push_back(true);
                    sum0 = sum0 * 10 + node->val;
                    node = node->left;
                }
                
            }
            return sum;
        }

        // 以下为视频解法

        int sumNumbersImpl(struct TreeNode * root, int parent){
            if(root == NULL) return 0;   //如果到头了，直接返回0
              int sum = root->val + parent * 10;   //因为是依次向后拼接，所以说直接将之前的值x10然后加上当前值即可
            if(!root->left && !root->right)    //如果是叶子结点，那么直接返回结果
                return sum;
              //否则按照同样的方式将左右的结果加起来
            return sumNumbersImpl(root->left, sum) + sumNumbersImpl(root->right,  sum);
        }
        
        int sumNumbers(struct TreeNode* root){
            return sumNumbersImpl(root, 0);
        }
        
    };