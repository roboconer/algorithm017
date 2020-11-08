
// L. 63. 不同路径 II --dp动态递归 ()

/*
    从下往上推，每次到达一个点，总是要么从左边来，要么从上边来，所以形成了递推公式：
    obs[x][y] = obs[x][y-1] + obs[x-1][y]
    先初始化第一行和第一列的情况（开辟二维数组来存储每一个网格的路径数），然后往上进行递推
    时间复杂度： O(NM)
    空间复杂度： O(NM)
*/
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        
        if (obstacleGrid.size() == 0) return 0;
        
        int grid_x = obstacleGrid.size();
        int grid_y = obstacleGrid[0].size();

        // int obs[grid_x][grid_y];
        /*
        静态数组的size必须在编译期就确定下来，这明显是变量，不能通过编译
        */
        vector<vector<long long>> obs(grid_x+1, vector<long long>(grid_y+1));
        for (int i = 0; i < grid_x && obstacleGrid[i][0] == 0; i++) { //初始化第一列
            obs[i][0] = 1;
        }

        for (int k = 0; k < grid_y && obstacleGrid[0][k] == 0; k++) { //初始化第一行
            obs[0][k] = 1;
        }

        for (int x = 1; x < grid_x; x++) {
            for (int y = 1; y < grid_y; y++) {
                if (obstacleGrid[x][y] == 0)   //当当前没有障碍物时，往上进行递推
                    obs[x][y] = obs[x][y-1] + obs[x-1][y];
            }
        }
        return obs[grid_x-1][grid_y-1];

        

    }
};


// L. 62. 不同路径-- dp (https://leetcode-cn.com/problems/unique-paths/)

/*
与63. 不同路径 II的解题思路一致
*/

class Solution {
public:
    int uniquePaths(int m, int n) {

      vector<vector<long long>> obs(m+1,vector<long long> (n+1)); //vector的有效范围为半开半闭区间[)
      for (int x = 0; x < m; x++) {
          obs[x][0] = 1;
      }   
      for (int y = 0; y < n; y++ ) {
          obs[0][y] = 1;
      }

      for (int x = 1; x < m; x++) {
          for (int y = 1; y < n; y++) {
              obs[x][y] = obs[x-1][y] + obs[x][y-1];
          }
      }

      return obs[m-1][n-1];
      
    }
};


// L. 64 最小路径和 --dp(https://leetcode-cn.com/problems/minimum-path-sum/)

/*
    同62题的思路，只是有所区别的是：
    在初始化首行和首列的时候，需要进行叠加前面一步的数值
*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int grid_x = grid.size();
        int grid_y = grid[0].size();
        if (grid_x == 0) return 0;

        int dp[grid_x][grid_y];
        memset(dp, 0, sizeof(dp));
        // vector<vector<int>> dp ((grid_x+1), vector<int> (grid_y+1));

        dp[0][0] = grid[0][0];
        for (int x = 1; x < grid_x; x++) {
            dp[x][0] = grid[x][0] + dp[x-1][0]; //叠加
        }
        for (int y = 1; y < grid_y; y++) {
            dp[0][y] = grid[0][y] + dp[0][y-1];
        }        

        for (int x = 1; x < grid_x; x++) {
            for (int y = 1; y < grid_y; y++) {
                dp[x][y] = min(dp[x-1][y], dp[x][y-1]) + grid[x][y];
            }
        }
        return dp[grid_x-1][grid_y-1];
    }
};


// L. 120. 三角形最小路径和--DP (https://leetcode-cn.com/problems/triangle/)

/*
    DP思路： 从下往上，当前级到下面的最小路径和 = 当前的节点值 + 下面的最小路径和。
    DP方程： f(i)(j) = min( f(i+1)(j) + f(i+1)(j) ) + triangle[i][j]
    时间复杂度: O(m*n)
    空间复杂度: O(1)
*/

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        for (int i = triangle.size() - 2; i >=0; i--) {
            for (int j = 0; j < triangle[i].size(); j++) {
                triangle[i][j] = min(triangle[i+1][j], triangle[i+1][j+1]) + triangle[i][j];
            }
        }    
        return triangle[0][0];
    }
};


// L. 1143. 最长公共子序列 -- dp(https://leetcode-cn.com/problems/longest-common-subsequence/)

/*
    1、最小子问题：每个最后的字符进行对比，相同的话，则最长子序列为【前面的(n-1)最长子系列+1】。
    2、迭代：用一个二维数组来存储，直至输出最后一个，最为返回。
    时间复杂度:O(mn)
    空间复杂度：O(mn)
*/

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        

        int num_1 = text1.size();
        int num_2 = text2.size();
        if (num_1 == 0 || num_2 == 0) return 0;
        int dp[num_1+1][num_2+1];
        memset(dp, 0, sizeof(dp));

        for (int x = 1; x <= num_1; x++) {
            for (int y = 1; y <= num_2; y++) {
                if (text1[x-1] == text2[y-1]) 
                    dp[x][y] = dp[x-1][y-1] + 1;
                else dp[x][y] = max(dp[x-1][y], dp[x][y-1]);
            }
        }
        return dp[num_1][num_2];

    }
};


