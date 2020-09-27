/*
L.283 移动零

思路1: 逐一检查该vector内每一元素是否为0,不为0的放进新的数组;等到剩下全为0的空位时,
再将后面的空位补0;
时间复杂度:O(n)
空间复杂度:O(1)  //数组是有限的

思路2: 双指针,保证新的数组前面都是非零的数字,一旦当前的数字为0,则与后面的数字交换;如果当前
的数字非0,则与自己交换(不变);(可以试着对[1,0,0,2]这个数组进行理解)
时间复杂度:O(n)
空间复杂度:O(1)
*/

//思路1:
 void moveZeroes(vector<int>& nums) {
        int j = 0;
        // move all the nonzero elements advance
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                nums[j++] = nums[i];
            }
        }
        for (;j < nums.size(); j++) {
            nums[j] = 0;
        }
    }

//思路2:(remember)
void moveZeroes(vector<int>& nums) {
    for(int the_pre_pointer=0,the_zero_pointer=0;the_pre_pointer<nums.size();the_pre_pointer++) {
        if(nums[the_pre_pointer]!=0) {
            swap(nums[the_zero_pointer++],nums[the_pre_pointer]);
        }
    }
}

/*
L.26 删除排序数组中的重复项

通过引入双索引，j在前（被动式，只能跟着x来走），i在后（主动式，会递增）。当j,i索引值不同时，则将j索引至i的位置；
当i,j索引值相同时，则此循环内不操作，等下一循环再进行比较和更新索引。
这一系列的目的，就是使j的索引为不重复的元素的最后一个.

*/
//代码:

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
    
    if(nums.size()<2) return nums.size();
    int j=0;
    for(int i=1;i<nums.size();i++){
        if(nums[j]!=nums[i]) 
            nums[++j]=nums[i];  //使j索引为不重复的元素的最后一个
    }
    return ++j;  
    }
};

/*
 [641] 设计循环双端队列
 主要是C++的STL库的队列子函数（需要注意接下来的学习）
*/

// @lc code=start
class MyCircularDeque {
public:
    vector<int> num;
    int cap;
    int size;
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) {
        size=k;
        cap=0;
    }
    
    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if(cap>=size) return false;
        num.insert(num.begin(),value);
        cap++;
        return true;
    }
    
    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if(cap>=size) return false;
        num.push_back(value);
        cap++;
        return true;
    }
    
    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if(cap==0) return false;
        num.erase(num.begin());
        cap--;
        return true;
    }
    
    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if(cap==0) return false;
        num.pop_back();
        cap--;
        return true;
    }
    
    /** Get the front item from the deque. */
    int getFront() {
        if(cap!=0) return num[0];
        return -1;
    }
    
    /** Get the last item from the deque. */
    int getRear() {
        if(cap!=0) return num[cap-1];
        return -1;
    }
    
    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return cap==0;
    }
    
    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return cap==size;
    }
};



/*
L.11盛最多水的容器
思路1: 直接双重循环进行遍历比较,取最大的那个值
时间复杂度: O(n^2)
空间复杂度: O(n)

思路2: 从最两端的值开始,使得宽最大化,然后逐渐往内进行收敛,定住高值,往内移动低值(已经使得宽变小了,就一定得让高度变大,所以移动低值,才可能使得高度变大)
这个排除掉左边柱子的操作，就是双指针代码里的 left++。left 和 right两个指针中间的区域都是还未排除掉的区域。
随着不断的排除，left 和 right 都会往中间移动。当 left 和 right 相遇，算法就结束了。
时间复杂度: O(logn)
空间复杂度: O(n)

*/
// 思路1:
int maxArea(vector<int>& height) {
        int maxd=0;
        for(int i=0;i<(height.size()-1);i++) {  //注意背诵这句
            for(int j=i+1;j<height.size();j++) {  //注意背诵这句
                int area=(j-i)*min(height[i],height[j]);
                maxd=max(maxd,area);
            }
        } 
        return maxd;   
    }

// 思路2:
int maxArea(vector<int>& height) {
      int val=0;
      int left=0;
      int right=height.size()-1;
      while(left<right) {
          val=max(val,min(height[left],height[right])*(right-left));
          if(height[left]<height[right]) 
                left++;
          else right--;
      }
        return val;   
    }



/* 
L.15 三数之和

思路1: 通过将三数之和转换为遍历一次(获得第一个数字)+两数之和为(sum-nums[i])的程序整合
关键难点是可能有多个和为 target 的数对儿,还不能重复,所以,当 sum == target 条件的 if 分支，当给 res 加入一次结果后，low和high不应该改变的同时，
还应该跳过所有重复的元素：

参考的解题思路:
链接：https://leetcode-cn.com/problems/3sum/solution/yi-ge-fang-fa-tuan-mie-by-labuladong/


思路2: 通过直接求sum-nums[i]的情况
https://leetcode.com/problems/3sum/discuss/7402/Share-my-AC-C%2B%2B-solution-around-50ms-O(N*N)-with-explanation-and-comments
*/
//思路1:
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end()); //将该数组从小到大进行排列
        int n=nums.size();
        int three_sum_target=0;  //输入三数之和,这里以0为例
        vector<vector<int>> res; //双层vector,二维

        for(int i=0;i<n;i++) {
            vector<vector<int>>tuples=twosumtarget(nums,i+1,three_sum_target-nums[i]); //调用2sum

            for(vector<int>& tuple:tuples) {
                tuple.push_back(nums[i]); //将nums[i]放入tuple容器中,与turples并列
                res.push_back(tuple);     //输出turple(turples+nums[i])
            }
            while(i<n-1 && nums[i]==nums[i+1]) 
                i++;
        }
        return res;
    }

private:
    vector<vector<int>> twosumtarget(vector<int>& nums,int start,int target) {
        int low=start,high=nums.size()-1; 
        vector<vector<int>> res;

        while (low<high) {
            int sum=nums[low]+nums[high];
            int left=nums[low],right=nums[high];
            if (sum<target) {
                while (low<high && nums[low]==left) low++;  //跳过所有重复的元素
            }
            else if (sum>target) {
                while (low<high && nums[high]==right) high--;
            }
            else {
                res.push_back({left,right});
                while (low<high && nums[low]==left) low++;
                while (low<high && nums[high]==right) high--;
            }
        }
        return res;
    }
};

//思路2: 
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int> > res;

    std::sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++) {
        
        int target = -nums[i];
        int front = i + 1;
        int back = nums.size() - 1;

        while (front < back) {

            int sum = nums[front] + nums[back];
            
            // Finding answer which start from number num[i]
            if (sum < target)
                front++;

            else if (sum > target)
                back--;

            else {
                vector<int> triplet(3, 0);
                triplet[0] = nums[i];
                triplet[1] = nums[front];
                triplet[2] = nums[back];
                res.push_back(triplet);
                
                // Processing duplicates of Number 2
                // Rolling the front pointer to the next different number forwards
                while (front < back && nums[front] == triplet[1]) front++;

                // Processing duplicates of Number 3
                // Rolling the back pointer to the next different number backwards
                while (front < back && nums[back] == triplet[2]) back--;
            }
            
        }

        // Processing duplicates of Number 1
        while (i + 1 < nums.size() && nums[i + 1] == nums[i]) 
            i++;

    }
    
    return res;
    }


/* L.141 环形链表

思路1: 快慢指针
快指针一次2步,慢指针一次1步,当快指针遇到NULL,则没有环形,输出false;当快指针与慢指针的值相等的时候,则有环形(表示追上了),
输出true

思路2: set
遍历链表,一旦遇到NULL,则退出循环,返回false
一旦set.count(cur)==1,表示之前已经遍历过这个节点了,则返回false
*/

//思路1:

 bool hasCycle(ListNode *head) {
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast && fast->next) {
            fast=fast->next->next;
            slow=slow->next;
            if(slow==fast) return true;
        }
        return false;
    }

//思路2: 

 bool hasCycle(ListNode *head) {
    unordered_set<ListNode*> set;
    ListNode* cur=head;
    while(cur) {
        if(set.count(cur)==1) return true;
        set.insert(cur);
        cur=cur->next;
        }
    return false;
    }



/* L.20 有效的括号

思路：哈希表+栈
1. 首先设定哈希表,依次保存三个开括号`(分别对应1,2,3)`与三个闭括号`(分别对应4,5,6)`,以及栈`(只放入开括号,遇到对应闭括号,则出栈)`还有最后一个正确bool值,判断是否正确`(比如第一个就是闭括号,必然错误)`,且默认为真
2. for遍历string字符串
   1. 如果为开括号,入栈
   2. 否则栈非空时,且接下来的为对应闭括号,则出栈
   3. 否则(此时隐含表达为'这是个闭括号'),则bool值为假
3. 如果栈非空时,则说明闭括号少了,bool为假
4. 返回bool值
*/
    bool isValid(string s) {
        
		//哈希表,存储,以及栈
        unordered_map<char,int> m{{'(',1},{'[',2},{'{',3},{')',4},{']',5},{'}',6}};
        stack <char> st;
        //用来判断如果第一个字符就是闭括号怎么办
        bool isTrue =true;
        //遍历string s
        for(char& c:s) {
        	//如果为开括号,将其入栈
            if(1<=m[c]&&m[c]<=3)st.push(c);
            //以下两行都是错的,而且两行语法就错了,意味着不能正确出栈了
            //else if(!st.empty() && m.find(m[c]-3)!=m.end() )st.pop();
            //else if(!st.empty() && st.top()==m[c]-3)st.pop();
            //如果栈非空,且栈顶元素与接下来的字符(闭括号)相对应,出栈
            else if(!st.empty() && m[st.top()]==m[c]-3 )st.pop();
            //否则俩个条件都不满足,意味着一开始就是个闭括号,或者闭括号多了,没有对应开括号在栈里面
            else 
            {
                isTrue=false;
                break;//这里别忘了啊
            }
        }
        //如果for遍历完后,栈非空,意味着开括号多了,则非法
        if(!st.empty()) isTrue=false;
		//返回bool值即可
        return isTrue;
    }

/* L.155 最小栈

思路：辅助栈
    使用一个辅助栈，将当前要入栈的元素与辅助栈顶的元素进行比较，并更新辅助栈顶的最小值
    当一个元素要出栈的时候，也顺便把辅助栈的栈顶元素一并弹出
    在任意一个时刻，辅助栈顶的元素始终是最小的栈值


*/
// 思路1：

class MinStack {
    stack<int> min_stack;
    stack<int> x_stack;
public:
    /** initialize your data structure here. */
    MinStack() {
        min_stack.push(INT_MAX);
    }
    
    void push(int x) {
        x_stack.push(x);
        min_stack.push(min(min_stack.top(),x));       
    }
    
    void pop() {
    x_stack.pop();
    min_stack.pop();    
    }
    
    int top() {
        return x_stack.top();       
    }
    
    int getMin() {
        return min_stack.top();        
    }
};