 // L 242. 有效的字母异位词

 /*
  思路1： 暴力求解（sort，再 compare）
          时间复杂度： O(nlogn)

  思路2： 哈希表
         1. 一开始进行判断 if(s.size() != t.size()) return false; 保证了字符串的长度一致 
         2.只要字符串长度一致，若是字母异位词，则hash[0]至hash[25]都等于0，若不是字母异位词，必然存在一个hash[x] = -1 
         时间复杂度：O(n)
 */

// 思路1：

 bool isAnagram(string s, string t) {
       sort(s.begin(),s.end());
       sort(t.begin(),t.end());      
       return s==t;  //s==t，return true; s!=t，return false.
    }

//思路2：

bool isAnagram(string s, string t) {
        if(s.size() != t.size()) return false;
        int hash[26] = {0};
        for(char c : s) hash[c - 'a'] ++;
        for(char c : t) 
            if(-- hash[c - 'a'] == -1) return false;
        return true;
    }


// L 94. 二叉树的中序遍历

/*
  思路1：递归法
        这里需要注意的是，函数返回的是 vector<int> 类型，所以需要定义一个vector<int>，vector向量表来存储输出
        时间复杂度：O(n)
        空间复杂度：O(n)
【对于递归方法，最好是建立一个新的函数作为调用】

  思路2：迭代法：时间复杂度和空间复杂度都为：O(n)

  思路3：Morris Traversal法
        时间复杂度：O(n)
        空间复杂度：O(1)
        https://www.cnblogs.com/anniekim/archive/2013/06/15/morristraversal.html
*/

// 思路1：

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ptr;
        break_return(root,ptr);
        return ptr;

    }
    
    void break_return(TreeNode* root , vector<int> & ptr)
    {
        if(!root) return ;
        break_return(root->left,ptr);
        ptr.push_back(root->val);
        break_return(root->right,ptr);
    }
};


//思路3：
// https://leetcode-cn.com/problems/binary-tree-inorder-traversal/solution/er-cha-shu-de-zhong-xu-bian-li-by-leetcode-solutio/
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode *predecessor = nullptr;

        while (root != nullptr) {
            if (root->left != nullptr) {
                // predecessor 节点就是当前 root 节点向左走一步，然后一直向右走至无法走为止
                predecessor = root->left;
                while (predecessor->right != nullptr && predecessor->right != root) {
                    predecessor = predecessor->right;
                }
                
                // 让 predecessor 的右指针指向 root，继续遍历左子树
                if (predecessor->right == nullptr) {
                    predecessor->right = root;
                    root = root->left;
                }
                // 说明左子树已经访问完了，我们需要断开链接
                else {
                    res.push_back(root->val);
                    predecessor->right = nullptr;
                    root = root->right;
                }
            }
            // 如果没有左孩子，则直接访问右孩子
            else {
                res.push_back(root->val);
                root = root->right;
            }
        }
        return res;
    }
};










