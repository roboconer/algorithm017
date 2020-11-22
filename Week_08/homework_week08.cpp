/***************************
 * 简单排序
 *
 * *************************/
 
// C++ 选择排序，从小到大
vector<int> selectionSort(vector<int>& arr) {
   int len = arr.size();
   int minIndex, temp;
   for (int i = 0; i < len -1; i++) {  // 只需循环n-1次，最后一次只剩下一个数(最大的数)
       minIndex = i;
       for (int j = i + 1； j < len; j++) {
           if (arr[j] < arr[minIndex]) {  // 寻找最小的数
               minIndex = j;   // 将最小数的索引保存
           }
       }
       temp = arr[i];
       arr[i] = arr[minIndex];
       arr[minIndex] = temp;  // 将最小数与前面的数交换
   }
   return arr;
}

// C++ 插入排序，从小到大
vector<int> insertionSort(vector<int>& arr) {
   int len = arr.size();
   int preIndex, current; 
   for (int i = 0; i < len; i++) {  
       preIndex = i - 1;
       current = arr[i];
       while (preIndex >= 0 && arr[preIndex] > current) {
           arr[preIndex + 1] = arr[preIndex]; //如果该元素（已排序）大于新元素，将该元素移到下一位置
           preIndex--;  // 继续在已经排序的前面部分往前寻找，直到找到已排序的元素小于或者等于新元素的位置
       }
       arr[preIndex + 1] = current;  // 将这个新元素插到该位置后面
   }
   return arr;
}

// C++（从小到大冒泡排序）
vector<int> bubbleSort(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {  //每次一重循环，都是让最大的元素挪到最后
        for (int j = 0; j < arr.size(); j++) {
            if (arr[j] > arr[j + 1]) {  // 相邻元素两两交换，大的数放到后面
                int temp = arr[j+1];  
                arr[j+1] = arr[j]; 
                arr[j] = temp;
            }
        }
    }
    return arr;
}


/* L. 146 LRU 缓存机制(https://leetcode-cn.com/problems/lru-cache/solution/146-lru-huan-cun-ji-zhi-by-kiko-q/)

*/
class LRUCache {
    list<pair<int, int>> l;  // 单向链表
    // 这里使用unordered_map而不使用vector(可以直接用find()函数来直接寻找key)或者map，是因为vector的find()和erase()都是时间复杂度O(n);map是基于二叉树实现的，时间复杂度为O(log n)
    unordered_map<int, list<pair<int, int>>::iterator > mp;
    int cap; 

public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if (mp.find(key) != mp.end()) {  //.end()就是null，也就是说，在mp找得到key的情况下
            int res = (*mp[key]).second; 
            l.erase(mp[key]);  // 把旧的节点擦除
            l.push_front(make_pair(key, res)); //把新的节点放入链表头
            // vector无法使用push_front():时间复杂度高，所以需要list
            mp[key] = l.begin(); // 更新mp[k]的值(有可能res改变了)
            return res;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {  // mp已经有key的状态值了
            l.erase(mp[key]);
            l.push_front(make_pair(key, value));
            mp[key] = l.begin();
        }
        else {   // 新的key状态值
            if (l.size() == cap) {  //缓存区已经满了，需要LRU
                mp.erase(l.back().first);  //把链表的最后一个清掉
                l.pop_back();  // 把链表的链尾pop
            }
            l.push_front(make_pair(key, value)); // 将新的key和val存入链头
            mp[key] = l.begin();  // 存储mp[key]的值
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


/* L. 338. 比特位计数 --位运算+DP(https://leetcode-cn.com/problems/counting-bits/solution/338-bi-te-wei-ji-shu-wei-yun-suan-dp-by-kiko-q/)
*/
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> bits(num+1, 0);
        for (int i = 1; i <= num; i++) {
            bits[i] += bits[i & (i - 1)] + 1; //动态递归，每次清掉最后一位1之后，就用前面的数目+1(清掉的那位1)
        }
        return bits;
    }
};


/* L 190. 颠倒二进制位 -- 位运算(https://leetcode-cn.com/problems/reverse-bits/solution/190-dian-dao-er-jin-zhi-wei-wei-yun-suan-by-kiko-q/)

    通过一个建立一个uint32_t的数据来存储转换后的结果，每次将n的最后一位取出来之后，就将n右移一位，
    并将store左移一位，实现颠倒。
*/
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
    uint32_t store = 0;  // 存储转换后的结果
    for (int i = 0; i < 32; i++ ) {
        store = (store << 1) + (n & 1) ;  // 将n的最后一位加到store上去，并将上一次的数据左移1位
        n = n >> 1;  // 将n右移一位，因为这个位已经被取了
    }       
    return store;
    }
};


/*L 37. 解数独 --递归回溯(https://leetcode-cn.com/problems/sudoku-solver/solution/37-jie-shu-du-di-gui-hui-su-by-kiko-q/)

*/

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtracking (board);
    }

private:
    bool backtracking(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); i++) {  //遍历行
            for (int j = 0; j < board[0].size(); j++) {  // 遍历列
                if (board[i][j] != '.') continue;  // 存在着数字，跳过当前
                for (char k = '1'; k <= '9'; k++) {
                    if (isValid(board, i, j, k)) {  // 这个位置可以放置k
                        board[i][j] = k;
                        if (backtracking(board)) return true; // 找到合适的一组立即返回
                        board[i][j] = '.';  // 回溯，撤销k
                    }
                }
                return false;  // 9个数都试过了，不行，输出结果false               
            }
        }
    return true;  // 遍历完，没有返回false,说明找到了合适的解，返回true
    }

    bool isValid(vector<vector<char>>& board, int row, int col, char val) {
        for (int i = 0; i < 9; i++) {  // 判断行里是否重复
            if (board[row][i] == val)  return false;
        }

        for (int j = 0; j < 9; j++) {  // 判断列里是否重复
            if (board[j][col] == val)  return false;
        }

        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;

        for (int i = startRow; i < startRow + 3; i++) {  //  判断9方格是否重复
            for (int j = startCol; j < startCol + 3; j++) {
                if (board[i][j] == val) return false;
            }
        }
        return true;
    }
};

