// L 547. 朋友圈 --并查集
/*
思路: 利用并查集:
    并查集主要有两个操作，一个是find，一个是union；
    find的作用是找到一个元素所在集合的代表元素，主要是一个递归的过程；
    union的作用就是将两个元素分别所在的集合合并成一个集合，就是将其中一个元素的代表元素变成另一个元素的代表元素
    时间复杂度: O(N^2)
    空间复杂度: O(N)
*/
class Solution {
public: 
    int find(vector<int> &Vec,int n) {
        if(Vec[n]==-1)
            return n;
        return find(Vec,Vec[n]);
    }

    void Union(vector<int> &Vec,int m,int n){
        int parent_m=find(Vec,m);
        int parent_n=find(Vec,n);
        if(parent_m!=parent_n)
            Vec[parent_m]=parent_n;
    }

    int findCircleNum(vector<vector<int>>& M) {
        int N=M.size();
        vector<int> parent(N,-1);
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                if(M[i][j]==1 && i!=j)
                    Union(parent,i,j);
            }
        }
        int count=0;
        for(int i=0;i<N;++i)
            if(parent[i]==-1)
                count++;
        return count;
    }
};


// L 328. 奇偶链表
/*
    一个值得细细琢磨的链表题，通过开辟三个临时起始节点，进行奇偶节点的交替
    时间复杂度：O(N)
    空间复杂度：O(1)   
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
       if (head == nullptr) return head;

       ListNode* evenHead = head->next;
       ListNode* odd = head;   // 以起始节点作为初始节点
       ListNode* even = evenHead;
       while (even != nullptr && even->next != nullptr) {
           odd->next = even->next;  //把偶节点的下一节点给奇节点的下一节点
           odd = odd->next;  //将上一步的下一节点转为当前节点给下一步循环
           even->next = odd->next;  
           even = even->next;
       }
       odd->next = evenHead;  //将偶节点起始节点接到奇节点末端
       return head;  
    }
};


// L 212. 单词搜索 II --Trie树
/*
    采用Trie树对字符串列表进行搜索
    【初始化字典树的时候，如果当前节点是某个单词的最后一个字母，会cur->word=word。
    后面搜索的时候，根据这个word是否为空来判断是不是字典树里的单词】
    时间复杂度:O(M43^(L-1))
    空间复杂度:O(N)
    M为二维字符数组的单元个数，L为每个字符串的平均长度，N为字典中的字符数
*/
class TrieNode {
public:
        string word = "";
        vector<TrieNode*> nodes;
        TrieNode(): nodes(26, 0){}
};

class Solution {
    int rows, cols;
    vector<string> res;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        rows = board.size();
        cols = rows ? board[0].size() : 0; // 判断(rows!=0 ?)
        if (rows == 0 || cols == 0) return res;

        // 将word放进字典树模板
        TrieNode* root = new TrieNode();
        for (string word : words) {
            TrieNode* cur = root;
            for (int i = 0; i < word.size(); i++) {
                int idx = word[i] - 'a';
                if (cur->nodes[idx] == 0) cur->nodes[idx] = new TrieNode(); // 在TrieNode找不到这个字符(按ASSCI-'a'来代表)，则把这个字符放入节点中
                cur = cur->nodes[idx];  // 判断这个节点是不是一个字典里的单词
            }
            cur->word = word;  //
        }
        // 在二维数组中进行DFS调用
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)  dfs(board, root, i, j);
        }
        return res;
    }

    void dfs(vector<vector<char>>& board, TrieNode* root, int x, int y) {
        char c = board[x][y];

        // 递归边界
        if (c == '.' || root->nodes[c-'a'] == 0) return; //这个字符搜索过了 或者 在这个查询单元board[x][y]中, TrieNode 没有这个字符,直接返回进行下一个单元查询
        root = root->nodes[c - 'a']; //把这个字符的指针存给root
        if (root->word != "") {   // 如果这个字符存在
            res.push_back(root->word); // 把这个字符push进res
            root -> word = "";  // root->word清空
        }
        board[x][y] = '.';  // 查找过的标注
        if (x > 0) dfs(board, root, x-1, y);
        if (y > 0) dfs(board, root, x, y-1);
        if (x+1 < rows) dfs(board, root, x+1, y);
        if (y+1 < cols) dfs(board, root, x, y+1);
        board[x][y] = c;
    }
};


// L 91. 解码方法 -- DP
/*
    本题的解法，其实围绕着两个点：当当前的数字字符为'0'时，则只有当前一个字符为'1'或'2'的时候，构成二位数的唯一解码，方法数与前一次的方法数相同；当当前的数字字符为'1'~'6'且前一个字符为'2' || 前一个字符为'1', 则可进行两次解码，为前前一次+前一次（按照当前轮的上一次来看）方法之和；
    其他的情况，就是当前值为'7'~'9' && 前一字符不为'1'的情况，这种条件下，只有唯一解码，方法数与上一次相同(无需变化)。
    时间复杂度: O(N)
    空间复杂度: O(1)

*/

class Solution {
public:
    int numDecodings(string s) {
       int pre = 1, curr = 1, tmp = 1; //pre为前一次方法数，curr为当前的方法数，tmp为中转数

       if (s[0] == '0') return 0;
       
       for (int i = 1; i < s.size(); i++) {
           tmp = curr;
           if (s[i] == '0') { 
                if(s[i-1] == '1' || s[i-1] == '2') curr = pre;
                else return 0;
                }
            else if (s[i-1] == '1' || (s[i] <= '6' && s[i] >= '1' && s[i-1] == '2'))
                curr = curr + pre;
            pre = tmp;
       
    }
    return curr;
    }
};


// L 152. 乘积最大子数组 --DP

/*
    与53.最大子序和相似的思路，差别在于：这里子序列的局部最优，不一定就是全局最优。因为相乘的情况，存在负负得正的情况，而求和，为单调的情况，max{局部最优}就是全局最优。
    所以这里需要维护两个值，一个当前局部最小值min_F，一个当前局部最大值max_F，再进行全局求最优。
    时间复杂度：O(N)
    空间复杂度：O(1)
*/

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int max_F = nums[0], min_F = nums[0], target = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            int max_0 = max_F, min_0 = min_F;  //需要存储两个值，不然到min_F,使用的max_F就被更新了
            max_F = max(nums[i], max(nums[i]*max_0, nums[i]*min_0)); // 需要对当前值也进行比较，防止存在0值
            min_F = min(nums[i], min(nums[i]*min_0, nums[i]*max_0));
            target = max(max_F, target);
        }
        return target;
    }
};

