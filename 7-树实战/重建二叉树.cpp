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
        TreeNode* deduceTree(vector<int>& preorder, vector<int>& inorder) {
            if(inorder.size() == 0) return NULL;
            TreeNode *node = new TreeNode;
            node->val = preorder[0];
            preorder.erase(preorder.begin());
            int index = 0;
            for(int i=0;i<inorder.size();++i)
            {
                if(inorder[i] == node->val)
                {
                    index = i;
                    break;
                }
            }
            vector<int> inorder1,inorder2;
            for(int i=0;i<index;++i) inorder1.push_back(inorder[i]);
            for(int i=index+1;i<inorder.size();++i) inorder2.push_back(inorder[i]);
            node->left = deduceTree(preorder , inorder1);
            node->right = deduceTree(preorder , inorder2);
            return node;
        } 

        // 以下为视频解法

        struct TreeNode * createNode(int val){   //这个就是单纯拿来创建结点的函数
            struct TreeNode * node = (TreeNode*)malloc(sizeof(struct TreeNode));
            node->left = node->right = NULL;
            node->val = val;
            return node;
        }
        
        //核心递归分治实现
        struct TreeNode* buildTreeCore(int * preorder, int * inorder, int start, int end, int index){
            if(start > end) return NULL;   //如果都超出范围了，肯定不行
            if(start == end) return createNode(preorder[index]);   //如果已经到头了，那么直接创建结点返回即可
            struct TreeNode * node = createNode(preorder[index]);   //先从前序遍历中找到当前子树的根结点值，然后创建对应的结点
            int pos = 0;   
            while (inorder[pos] != preorder[index]) pos++;   //找到中序的对应位置，从这个位置开始左右划分
            node->left = buildTreeCore(preorder, inorder, start, pos - 1, index+1);   
              //当前结点的左子树按照同样的方式建立
              //因为前序遍历的下一个结点就是左子树的根结点，所以说这里给index+1
            node->right = buildTreeCore(preorder, inorder, pos+1, end, index+(pos-start)+1);  
              //当前结点的右子树按照同样的方式建立
              //最后一个index需要先跳过左子树的所有结点，才是右子树的根结点，所以说这里加了个pos-start，就是中序划分出来，左边有多少就减去多少
            return node;   //向上一级返回当前结点
        }
        
        struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
            return buildTreeCore(preorder, inorder, 0, preorderSize - 1, 0);
              //这里传入了前序和中序序列，并且通过start和end指定当前中序序列的处理范围，最后的一个index是前序遍历的对应头结点位置
        }
        
    };