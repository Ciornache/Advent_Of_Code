#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>

#define MAX_ROW 50
#define MAX_COLUMN 150
#define MAX_TIME 1000
#define fastio                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(0), cout.tie(0);
#define FILES                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#define int long long

using namespace std;

int dp[MAX_ROW + 5][MAX_COLUMN + 5][MAX_TIME + 5];
bool position[MAX_ROW + 5][MAX_COLUMN + 5][MAX_TIME + 5];

class Solution
{
private:
    const int dx[5] = {-1, 1, 0, 0, 0},
              dy[5] = {0, 0, -1, 1, 0};
    struct element
    {
        int row, column, time;
        bool operator<(const element &a) const
        {
            return dp[row][column][time] > dp[a.row][a.column][a.time];
        }
    };

    struct moveBy
    {
        int row, column;
        int diffRow, diffColumn, time;
    };

    vector<string> grid;
    int startRow = 1, startColumn = 2;
    int endRow, endColumn, maxTime, n, m;

public:
    Solution()
    {
        readInput();
        endRow = grid.size(), endColumn = grid[0].size() - 1;
        for (int i = 1; i <= MAX_ROW; ++i)
        {
            for (int j = 1; j <= MAX_COLUMN; ++j)
            {
                for (int k = 0; k <= MAX_TIME; ++k)
                    dp[i][j][k] = 1e9;
            }
        }
        maxTime = (grid[0].size() - 2) * (grid.size() - 2) / __gcd(grid[0].size() - 2, grid.size() - 2);
        n = grid.size(), m = grid[0].size();
    }

    void readInput()
    {
        std::string row;
        int currentRow = 1;
        while (getline(std::cin, row))
        {
            char *p = strchr("aeiou", 'o');
            grid.push_back(row);
            for (int i = 0; i < row.size(); ++i)
            {
                position[currentRow][i + 1][0] = (strchr("#><^v", row[i]) != NULL);
                if (row[i] == '#')
                {
                    for (int j = 1; j <= MAX_TIME; ++j)
                        position[currentRow][i + 1][j] = 1;
                }
            }
            currentRow++;
        }
    }

    void simulateWind()
    {
        queue<moveBy> q;
        for (int i = 1; i <= min(1LL * MAX_ROW, (long long)(grid.size())); ++i)
        {
            for (int j = 1; j <= min(1LL * MAX_COLUMN, (long long)(grid[0].size())); ++j)
            {
                if (strchr("<>^v", grid[i - 1][j - 1]))
                {
                    int diffRow = 0, diffCol = 0;
                    if (grid[i - 1][j - 1] == '<')
                        diffCol = -1;
                    else if (grid[i - 1][j - 1] == '>')
                        diffCol = 1;
                    else if (grid[i - 1][j - 1] == '^')
                        diffRow = -1;
                    else
                        diffRow = 1;
                    q.push({i, j, diffRow, diffCol, 0});
                }
            }
        }

        while (!q.empty())
        {
            moveBy mov = q.front();

            if (mov.row == n)
                mov.row = 2;
            if (mov.row == 1)
                mov.row = n - 1;

            if (mov.column == m)
                mov.column = 2;
            if (mov.column == 1)
                mov.column = m - 1;

            q.pop();
            if (mov.time > maxTime)
                continue;

            position[mov.row][mov.column][mov.time % maxTime] = 1;
            q.push({mov.row + mov.diffRow, mov.column + mov.diffColumn, mov.diffRow, mov.diffColumn, mov.time + 1});
        }

        //        for(int i = 1;i <= maxTime; ++i)
        //        {
        //            for(int j = 1;j <= n; ++j)
        //            {
        //                for(int k = 1;k <= m; ++k)
        //                {
        //                    if(position[j][k][i])
        //                        std::cout << '#';
        //                    else
        //                        std::cout << '.';
        //                }
        //                std::cout << '\n';
        //            }
        //            std::cout << '\n';
        //        }
    }
    inline bool inGrid(int i, int j)
    {
        return i >= 1 && i <= n && j >= 1 && j <= m;
    }

    int traverseGrid()
    {
        //        std::cout << n << ' ' << m << ' ' << maxTime << '\n';
        std::priority_queue<element> pq;
        dp[startRow][startColumn][0] = 0;
        pq.push({startRow, startColumn, 0});

        while (!pq.empty())
        {
            int row = pq.top().row;
            int column = pq.top().column;
            int time = pq.top().time;

            if (row == endRow && column == endColumn)
                return dp[row][column][time];

            pq.pop();

            int newTime = (time + 1) % maxTime;

            //            if(time == 5)
            //                std::cout << row << ' ' << column << ' ' << time << ' ' << newTime << ' ' << position[3][4][0] << '\n';

            for (int i = 0; i < 5; ++i)
            {
                int newRow = row + dx[i], newColumn = column + dy[i];
                if (inGrid(newRow, newColumn) && !position[newRow][newColumn][newTime])
                {
                    if (dp[newRow][newColumn][newTime] > dp[row][column][time] + 1)
                    {
                        dp[newRow][newColumn][newTime] = dp[row][column][time] + 1;
                        pq.push({newRow, newColumn, newTime});
                    }
                }
            }
        }

        return 0;
    }

    void solveFirstTask()
    {
        simulateWind();

        std::cout << traverseGrid();
    }
};

signed main()
{
    fastio
        FILES
            Solution *solver = new Solution;
    solver->solveFirstTask();
}
