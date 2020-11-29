/*
    L 56. 合并区间 -- 快慢指针+排序

    时间复杂度:O(nlog n)，n为区间数，主要时间开销就是sort排序，线性扫描的时间不大
    空间复杂度: O(logn)，n为区间数，这里排除了储存答案的ans，只包含了开辟出来的i,j,和t。
*/
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
      vector<vector<int>> ans;
      sort(intervals.begin(), intervals.end());
      for (int i = 0; i < intervals.size();  ) {  // 慢指针，指向循环次数(也就是合并后的区间数)
          int j = i + 1;  // 快指针，指向当前循环中，可合并的区间号
          int t = intervals[i][1];
          while (j < intervals.size() && t >= intervals[j][0]) {  // 当多区间合并时
              t = max(t, intervals[j][1]);
              j++;
          }
          ans.push_back({intervals[i][0], t});
          i = j;
        }
        return ans;
    }
};


/*
    L 198. 打家劫舍 -- dp

    跟爬楼梯问题类似，递推方程：f[k] = max(f[k-1], f[k-2] + nums[k-1])
    时间复杂度： O(N)
    空间复杂度： O(N)/O(1)
*/

class Solution {
public:
    int rob(vector<int>& nums) {
/* 空间优化
        if (nums.size() == 0) return 0;
        int pre_num = 0, curr_num = nums[0];       
        for (int i = 2; i <= nums.size(); i++) {
            int dp = max(curr_num, pre_num + nums[i-1]);
            pre_num = curr_num;
            curr_num = dp;
        }
        return curr_num;
*/
    if (nums.size() == 0) return 0;

        vector<int> dp(nums.size()+1, 0);
        dp[0] = 0;
        dp[1] = nums[0];
        
        for (int i = 2; i <= nums.size(); i++) {
            int dp[i] = max(dp[i-1], dp[i-2] + nums[i-1]);
        }
        return dp[nums.size()];    
    } 
};


/*
    L 121. 买卖股票的最佳时机 -- dp
    这个题目采用动态规划，前i天的最大利润为：max_val(i) = max(prices[i] - min_val(i-1), max_val(i-1))
    时间复杂度:O(N)
    空间复杂度:O(1)
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;
        int max_val = 0;
        int min_val = prices[0];

        for (int i = 1; i < prices.size(); i++) {
            max_val = max(prices[i] - min_val, max_val);
            min_val = min(prices[i], min_val);
        }  
        return max_val;
    }
};


/*
    L 709. 转换成小写字母
    C++的string 是mutable（可修改的），而python 和java的string都是不可修改的
*/
class Solution {
public:
    string toLowerCase(string str) {
        int size = str.size();
        for (int i = 0; i < size; i++) {
            if (str[i] - 'A' <= 26 && str[i] - 'A' >= 0) 
                str[i] = 'a' + (str[i] - 'A');
        }
        return str;
    }
};


/*
    L 58. 最后一个单词的长度 -- istringstream
    内存I/O——istringstream：
    这个类的对象可以直接从string中读取数据，istringstream是基于空格来提取字符串的，从而完成从字符串到其它类型的改变。
*/

class Solution {
public:
    int lengthOfLastWord(string s) {
      istringstream in(s);
      string st;
      while(in>>st);  //一直到st的所有字符串都提取完了结束（从头开始）
      return st.size();

    }
};
