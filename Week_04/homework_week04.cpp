
/* L 874. 模拟行走机器人 --方向循环

参考思路：https://leetcode-cn.com/problems/walking-robot-simulation/solution/tu-jie-mo-ni-xing-zou-ji-qi-ren-by-dekeshile/

这个问题的关键就是建立坐标系的循环问题，通过给四个方向赋代表值(1~4)，并按照顺时针的方向进行循环，作为方向性的单步运动的指引(direx、direy)。
时间复杂度：O(M + N), M为commands.size()，N为obstacles.size()
空间复杂度：O(N),存储障碍物的空间
*/

#include <utility>
#include <set>
class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int direx[] = {0, 1, 0, -1};  // 方向性的单步运动（每次只走一步）
        int direy[] = {1, 0, -1, 0};  // 以y为变量，当方向为x，则y = 0
        int curx = 0, cury = 0;     // 当前运动点的坐标
        int curdire = 0;
        int comLen = commands.size();  // 命令长度
        int ans = 0;
        set<pair<int, int>> obstacleSet;
        for (int i = 0; i < obstacles.size(); i++) {  // 存储配对好障碍物
            obstacleSet.insert(make_pair(obstacles[i][0],obstacles[i][1]));
        }

        for (int i = 0; i < comLen; i++) {      //对每个命令
            if (commands[i] == -1) curdire = (curdire + 1)%4;       // 右转情况
            else if (commands[i] == -2) curdire = (curdire + 3)%4;  // 左转情况
            else {                                                  // 当前直走(尝试)
                for (int j = 0; j < commands[i]; j++) {
                    int nx = curx + direx[curdire];
                    int ny = cury + direy[curdire];

                if (obstacleSet.find(make_pair(nx, ny))  == obstacleSet.end()) { // find函数找不到，返回null与end()的结尾null相同时
                curx = nx;
                cury = ny;
                ans = max(ans, curx*curx + cury*cury);
                }
                else{
                    break;  // 下一节点就是障碍物，则跳过当前的直走剩下的步骤
                    }
                }
            }
        }
    return ans;
    }
};

/* L 33. 搜索旋转排序数组 -- 二分法

参考解法：
https://leetcode-cn.com/problems/search-in-rotated-sorted-array/solution/jian-ji-rong-yi-li-jie-java-er-fen-fa-by-breezean/
这个问题的关键，在于如何区分：向前规范和向后规范的条件
时间复杂度：O(log n)
空间复杂度：O(1)

*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left < right) {
            int mid = (left + right)/2;
            // 当[0,mid]有序时,向后规约的条件
            if (nums[0] <= nums[mid] && (target > nums[mid] || target < nums[0]))  // 截断的是前小段(< nums.size()/2 )
                left = mid + 1;
            // 当[0,mid]发生旋转时，向后规约的条件
            else if (target > nums[mid] && target < nums[0])  //截断的是前大段 ( > nums.size()/2 ) 
                left = mid + 1;
            // 其他的情况，向前规约
            else right = mid;
        }
        return left == right && nums[left] == target ? left : -1;
    }
};

/* L 367. 有效的完全平方数 --二分查找

注意变量类型int不够大，要用long

时间复杂度：O(log n)
空间复杂度：O(1)
*/
class Solution {
public:
    bool isPerfectSquare(int num) {
        
        if (num == 1) return true;
        long left = 0, right = num;
        long mid = 0;
        while (left <= right) {
            mid = (left + right)/2;
            if (mid * mid == num) return true;
            else if ( mid * mid < num) left = mid + 1;
            else right = mid - 1; 
        }
        return false;

    }
};

/* L 69. x 的平方根 --二分查找

二分查找:
这里需要注意的就是，由于这里的返回值是舍余数的整数，所以返回的值可能在left也可能是right。
采用下面的另一种代码（注释）的，把一个在<范围的中间值存储下来，返回，就可靠很多。
时间复杂度：O(log n)
空间复杂附：O(1)

牛顿迭代法：
https://leetcode-cn.com/problems/sqrtx/solution/niu-dun-die-dai-fa-by-loafer/
时间复杂度：O(log x)，此方法是二次收敛的，相较于二分查找更快。
空间复杂度：O(1)

*/
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0 || x == 1) return x;
     long left = 1, right = x;
     long mid = 1;
     while (left <= right) {
         mid = left + (right - left)/2;
         if (mid*mid > x)  right = mid - 1;
         else left = mid + 1;
     }
     return (int)right;   
    // int l = 0, r = x, ans = -1;
    //     while (l <= r) {
    //         int mid = l + (r - l) / 2;
    //         if ((long long)mid * mid <= x) {
    //             ans = mid;
    //             l = mid + 1;
    //         } else {
    //             r = mid - 1;
    //         }
    //     }
    //     return ans;

/*
// 牛顿迭代法
    s = x;
    if (x == 0) return 0;
    return ((int)(sqrts(x)));
    }
    
    double sqrts(double x) {
        double res = (x + s/x)/2;
        if (res == x) return x;
        else return sqrts(res);
    }
*/
    }
};


/* L. 55. 跳跃游戏 --贪心算法

贪心算法： 这里需要一点技巧：从后开始进行贪心
endreachable 指向：从后开始，能到达最后一个位置的最前指针。
从数组的最后一位开始（最后一个肯定满足），只要当前的位置的步长值+前面的元素个数(以最低步长1来计算，只要最低步长都满足，那就其他情况都可以，因为只有0步长不满足) >= endreachable， 则把endreachable指针向前移动。

时间复杂度：O(n) ，遍历一次数组
空间复杂度：O(1) 

*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        // if (nums == NULL) return false;

        int endreachable = nums.size() - 1;
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (nums[i] + i >= endreachable) {
                endreachable = i;
            }
        }
        if (endreachable == 0) return true;
        else return false; 
    }
};

/* L. 53. 最大子序和 --贪心算法

贪心算法，在最大子序列中，当前面的子序列已经和为负，则舍弃，另起新的子序列
时间复杂度 ：O(n)
空间复杂度 ：O(1)
*/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {

        int select = nums[0];  // 最终输出的子序列和
        int sums = 0;          // 动态子序列和
        for (auto num : nums) {
            if (sums > 0)  sums += num;  // 前面的子序列为正，可用
            else sums = num;             // 前面的子序列为负，舍掉，换新的节点为子序列头
            select = max(sums, select);  // 输出最终的子序列和
        }
        return select;
    }
};



/* 234. 回文链表 --数组

思路：通过将链表转换存储为数组，进行首尾对比
时间复杂度：O(N)
空间复杂度：O(N)
(通过翻转链表可以将空间复杂度降低为O(1))
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        
        ListNode* cur = head;
        int length = 0;
        while (cur) {       // 获得链表的尺寸，避免每次将数据放进数组都要重新开辟空间
            length++;
            cur = cur -> next;
        }

        vector<int> vec(length, 0);  
        int index = 0;
        cur = head;
        while (cur){       // 将链表数据放入数组中
            vec[index++] = cur->val;
            cur = cur -> next;
        }

        for (int x = 0,y = vec.size() -1; x < y; x++, y--) {  // 将数组的数据，进行首尾对比，当存在首尾移动，数据不相等时，则不是回文链表（包含了单链表的情况）
            if (vec[x] != vec[y]) return false;
        }
        return true;
    }
};


/* 反转链表： 
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return true;
        ListNode* slow = head; // 慢指针，找到链表中间分位置，作为分割
        ListNode* fast = head;
        ListNode* pre = head; // 记录慢指针的前一个节点，用来分割链表
        while (fast && fast->next) {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        pre->next = nullptr; // 分割链表

        ListNode* cur1 = head;  // 前半部分
        ListNode* cur2 = reverseList(slow); // 反转后半部分，总链表长度如果是奇数，cur2比cur1多一个节点

        // 开始两个链表的比较
        while (cur1) {
            if (cur1->val != cur2->val) return false;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return true;
    }
    // 反转链表
    ListNode* reverseList(ListNode* head) {
        ListNode* temp; // 保存cur的下一个节点
        ListNode* cur = head;
        ListNode* pre = nullptr;
        while(cur) {
            temp = cur->next;  // 保存一下 cur的下一个节点，因为接下来要改变cur->next
            cur->next = pre; // 翻转操作
            // 更新pre 和 cur指针
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};

作者：carlsun-2
链接：https://leetcode-cn.com/problems/palindrome-linked-list/solution/234-hui-wen-lian-biao-shu-zu-mo-ni-fan-zhuan-hou-b/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/





