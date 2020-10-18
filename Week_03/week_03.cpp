
// L 46.ȫ����
/* ˼·1�� STL�е�ȫ���з�����next_permutation
          �ڽ���Ӧ��STL��ȫ���з���֮ǰ����Ҫ�����������������(sort)������ֻ�������ʼ����֮�����ϡ��ο���https://www.cnblogs.com/JeasonIsCoding/p/                9858950.html��
          ʱ�临�Ӷȣ� sort: nlog2(n) + n!
   ˼·2�� ����˼·ģ�� ���ο���https://leetcode-cn.com/problems/permutations/solution/hui-su-suan-fa-xiang-jie-by-labuladong-2/��

*/

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        
        vector<vector<int>> queue_rank;
        backtrack(queue_rank, nums, 0, (int)nums.size());
        return queue_rank;
    }

    void backtrack(vector<vector<int>>& queue_rank, vector<int>& output, int start, int size) {  // ע��ȡֵ����
        // ����������������(�������)
        if (start == size) {
            queue_rank.emplace_back(output);
            return;
        }

        for (int i = start; i < size; i++) {
            // ��̬ά������
            swap(output[i], output[start]);
            // �ݹ����
            backtrack(queue_rank, output, start+1, size);
            // ��������
            swap(output[i], output[start]);
        }
    }
};


/*˼·1��
vector<vector<int>> permute(vector<int>& nums) {
    sort(nums.begin(), nums.end());   // �����������������
    vector<vector<int>> queue_rank;

    do {
        queue_rank.emplace_back(nums);   // emplace_back�滻��push_back, ֻ��һ�ι��캯���������ÿ������캯�����ٶ����
    } while (next_permutation(nums.begin(),nums.end()));   // ��nums����ʼλ��ĩλ������ȫ����

    return queue_rank;
}
*/ 

// L 47.ȫ���Т�

/*
ȥ�أ���������used[]���飬���ڴ�Ÿ������Ƿ��Ѿ���ͬ���������push����ջ�С�
������������ȥ�غ���֦��ȥ�أ�������ȥ�ػ����Ч������������Կ���https://leetcode-cn.com/problems/permutations-ii/solution/47-quan-pai-lie-iiche-di-li-jie-pai-lie-zhong-de-q/
ʱ�临�Ӷȣ�O(n*(n!)) -- n!ÿ��ѭ������backtracking������ n--�����������£�û���ظ�������,��n��������������������{sort()��nlogn ���Ժϲ������}
�ռ临�Ӷȣ�O(n)

*/

class Solution {
public:
    vector<vector<int>> result;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
       
/* ����C++��STL��--emplace_back()

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
            // ����Ҫ�󣬴�ʱ˵���ҵ���һ��
            if (vec.size() == nums.size()) {
                result.push_back(vec);
                return;
           }
            // �������used[i - 1]�ǳ���Ҫ 
            // used[i - 1] == true��˵��ͬһ��֧nums[i - 1]ʹ�ù� 
            // used[i - 1] == false��˵��ͬһ����nums[i - 1]ʹ�ù�
            // ���ͬһ����nums[i - 1]ʹ�ù���ֱ������
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

//  ��ָ Offer 68 - II. �������������������

/*
ͨ���ݹ��ѯ�����ڵ�p,q��
1.���ĳ���ڵ����p��q��ֵ���򷵻ظýڵ��ֵ�����ڵ㣬��������һ���ڵ�����������У�
2.�����ǰ�ڵ����������������p��q�������ڵ㣬˵���ýڵ����Ҫ�ҵ�����������ȣ�
3.�����ǰ�ڵ��������������ֵΪ��ΪNULL���ⷵ�ؿ�ָ�롣
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

