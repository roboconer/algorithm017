
// L 46.全排列
/* 思路1： STL中的全排列方法：next_permutation
          在进行应用STL的全排列方法之前，需要对数组进行升序排列(sort)，否则，只会输出初始排列之后的组合【参考：https://www.cnblogs.com/JeasonIsCoding/p/                9858950.html】
          时间复杂度： sort: nlog2(n) + n!
   思路2： 回溯思路模板 【参考：https://leetcode-cn.com/problems/permutations/solution/hui-su-suan-fa-xiang-jie-by-labuladong-2/】

*/

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        
        vector<vector<int>> queue_rank;
        backtrack(queue_rank, nums, 0, (int)nums.size());
        return queue_rank;
    }

    void backtrack(vector<vector<int>>& queue_rank, vector<int>& output, int start, int size) {  // 注意取值符号
        // 当所有数都填完了(结束标记)
        if (start == size) {
            queue_rank.emplace_back(output);
            return;
        }

        for (int i = start; i < size; i++) {
            // 动态维护数组
            swap(output[i], output[start]);
            // 递归调用
            backtrack(queue_rank, output, start+1, size);
            // 撤销操作
            swap(output[i], output[start]);
        }
    }
};


/*思路1：
vector<vector<int>> permute(vector<int>& nums) {
    sort(nums.begin(), nums.end());   // 对数组进行升序排列
    vector<vector<int>> queue_rank;

    do {
        queue_rank.emplace_back(nums);   // emplace_back替换掉push_back, 只有一次构造函数，不调用拷贝构造函数，速度最快
    } while (next_permutation(nums.begin(),nums.end()));   // 从nums的起始位到末位，进行全排列

    return queue_rank;
}
*/ 

// L 47.全排列Ⅱ

/*
去重，这里引入used[]数组，用于存放该数据是否已经被同层检索到并push进堆栈中。
关于在树层上去重和树枝上去重，树层上去重会更高效，具体解析可以看：https://leetcode-cn.com/problems/permutations-ii/solution/47-quan-pai-lie-iiche-di-li-jie-pai-lie-zhong-de-q/
时间复杂度：O(n*(n!)) -- n!每次循环调用backtracking函数； n--而对于最坏情况下，没有重复性问题,则n个数都得填进结果数组中{sort()的nlogn 可以合并或忽略}
空间复杂度：O(n)

*/

class Solution {
public:
    vector<vector<int>> result;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
       
/* 调用C++的STL库--emplace_back()

        // vector<vector<int>> queue_rank;

        // sort(nums.begin(),nums.end());

        // do {
        //     queue_rank.emplace_back(nums);
        // } while (next_permutation(nums.begin(), nums.end()));

        // return queue_rank;
*/
    sort(nums.begin(), nums.end());
    vector<bool> used(nums.size(), false);
    vector<int> vec;

    backtracking(nums, vec, used);
    return result;

    }

    void backtracking(vector<int>& nums, vector<int>& vec, vector<bool>& used) {
            // 满足要求，此时说明找到了一组
            if (vec.size() == nums.size()) {
                result.push_back(vec);
                return;
           }
            // 这里理解used[i - 1]非常重要 
            // used[i - 1] == true，说明同一树支nums[i - 1]使用过 
            // used[i - 1] == false，说明同一树层nums[i - 1]使用过
            // 如果同一树层nums[i - 1]使用过则直接跳过
            for (int i = 0; i < nums.size(); i++) {

                if (i > 0 && used[i-1] == false && nums[i] == nums[i-1] ) continue;

                if (used[i] == false) {
                    used[i] = true;
                    vec.push_back(nums[i]);
                    backtracking(nums, vec, used);
                    vec.pop_back();
                    used[i] = false;
                }
            }
    }
};

//  剑指 Offer 68 - II. 二叉树的最近公共祖先

/*
通过递归查询两个节点p,q：
1.如果某个节点等于p或q的值，则返回该节点的值给父节点，告诉它有一个节点存在其子树中；
2.如果当前节点的左右子树包含了p、q这两个节点，说明该节点就是要找的最近公共祖先；
3.如果当前节点的两个子树返回值为都为NULL，这返回空指针。
*/

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    //    if(root==NULL) return NULL;
    //    if(root->val > p->val && root->val > q->val)
    //         return lowestCommonAncestor(root->left,p,q);
    //    else if (root->val < p->val && root->val < q->val)
    //         return lowestCommonAncestor(root->right,p,q);
    //    else return root;

        if(root == NULL)return NULL;
        if(root==p||root==q) return root;
        TreeNode* left=lowestCommonAncestor(root->left,p,q);
        TreeNode* right=lowestCommonAncestor(root->right,p,q);
        if(left&&right) return root;
        return left? left : right;
    
    }
};

