#include <bits/stdc++.h>

#define SIZE 205
#define FILES freopen("input.in","r",stdin);\
              freopen("output.out","w",stdout);

using namespace std;
class Solution
{

private:
    ///*        Utilities         */
    struct element
    {
        int line;
        int column;
    };
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};

    ///*        Utilities         */

    char grid[SIZE][SIZE];
    int startLine, startColumn;
    int finishLine, finishColumn;
    int n, m, steps[SIZE][SIZE];
    queue<element> q;
    vector<element> lowestElevation;

public:
    Solution()
    {
        this->readInput();
        for(int i = 1; i < SIZE; ++i)
            for(int j = 1; j < SIZE; ++j)
                steps[i][j] = 1e9;
    }
    void readInput()
    {
        string str;
        while(getline(cin, str))
        {
            n++;
            m = 0;
            for(int i = 0; i < str.size(); ++i)
            {
                m++;
                grid[n][m] = str[i];
                if(str[i] == 'S')
                {
                    this->startLine = n, this->startColumn = m;
                    grid[n][m] = 'a';
                }
                else if(str[i] == 'E')
                {
                    this->finishLine = n, this->finishColumn = m;
                    grid[n][m] = 'z';
                }
                if(grid[n][m] == 'a')
                    lowestElevation.push_back({n, m});
            }
        }
    }
    bool inside(int i, int j)
    {
        return i >= 1 && i <= n && j >= 1 && j <= m;
    }
    int bfs(int type)
    {
        if(type == 2)
        {
            for(auto i : lowestElevation)
            {
                q.push({i.line, i.column});
                steps[i.line][i.column] = 0;
            }
        }
        else if(type == 1)
        {
            q.push({startLine, startColumn});
            steps[startLine][startColumn] = 0;
        }
        while(!q.empty())
        {
            int x = q.front().line;
            int y = q.front().column;
            q.pop();
            for(int k = 0; k < 4; ++k)
            {
                int i = x + dx[k];
                int j = y + dy[k];
                if(inside(i, j) && grid[x][y] - grid[i][j] >= -1 && steps[i][j] > steps[x][y] + 1)
                {
                    steps[i][j] = steps[x][y] + 1;
                    q.push({i, j});
                }
            }
        }
        return steps[finishLine][finishColumn];
    }
    void solveFirstTask()
    {
        int answer = this->bfs(1);
        cout << answer << '\n';
    }
    void solveSecondTask()
    {
        int answer = this->bfs(2);
        cout << answer << '\n';
    }
};
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    FILES
    Solution solver;
    #if 1
        solver.solveFirstTask();
    #else
        solver.solveSecondTask();
    #endif

}
