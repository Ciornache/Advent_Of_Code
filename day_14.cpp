#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
#include <utility>

#define FILES                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

using namespace std;

class Solution
{
    struct element
    {
        int l;
        int c;
    };

private:
    ///* UTILITIES *///

    const int dx[3] = {1, 1, 1};
    const int dy[3] = {0, -1, 1};

    map<pair<int, int>, int> rocks;

    map<int, int> line;
    map<int, int> column;

    ///* UTILITIES *///

    vector<element> positions;
    int firstTask, maximumFloor, secondTask;

public:
    Solution()
    {
        firstTask = secondTask = 0;
        maximumFloor = -1;
        this->readInput();
    }
    void readInput()
    {
        string str;
        while (getline(cin, str))
        {
            positions.clear();
            for (int i = 0; i < str.size(); ++i)
            {
                if (str[i] >= '0' && str[i] <= '9')
                {
                    int l = 0, c = 0;
                    while (i < str.size() && str[i] >= '0' && str[i] <= '9')
                        l = l * 10 + str[i] - '0', i++;
                    i++;
                    while (i < str.size() && str[i] >= '0' && str[i] <= '9')
                        c = c * 10 + str[i] - '0', i++;
                    swap(l, c);
                    rocks[{l, c}] = 1;
                    column[c]++;
                    maximumFloor = max(maximumFloor, l);
                    positions.push_back({l, c});
                }
            }
            this->buildRocks();
        }
        maximumFloor += 2;
    }
    void buildRocks()
    {
        for (int i = 1; i < positions.size(); ++i)
        {
            if (positions[i].l == positions[i - 1].l)
            {
                int sign = (positions[i].c - positions[i - 1].c) / abs(positions[i].c - positions[i - 1].c);
                int col = positions[i - 1].c;
                for (int j = col; j != positions[i].c; j += sign)
                {
                    rocks[{positions[i].l, j}] = 1, column[j]++;
                    //                    cout << positions[i].l << ' ' << j << '\n';
                }
            }
            else if (positions[i].c == positions[i - 1].c)
            {
                int sign = (positions[i].l - positions[i - 1].l) / abs(positions[i].l - positions[i - 1].l);
                int lin = positions[i - 1].l;
                for (int j = lin; j != positions[i].l; j += sign)
                {
                    rocks[{j, positions[i].c}] = 1;
                    maximumFloor = max(maximumFloor, j);
                    //                    cout << j << ' ' << positions[i].c << '\n';
                }
            }
        }
    }
    void constructSandPath(int l, int c, int type)
    {
        if (type == 2)
        {
            if (l + 1 == maximumFloor)
            {
                rocks[{l, c}] = 1, column[c]++;
                secondTask++;
                return;
            }
        }
        if (!column[c] && type == 1)
        {
            cout << firstTask;
            exit(0);
        }
        bool ok = 0;
        for (int i = 0; i < 3; ++i)
        {
            int newLine = l + dx[i];
            int newColumn = c + dy[i];
            if (!rocks[{newLine, newColumn}])
            {
                ok = 1;
                constructSandPath(newLine, newColumn, type);
                break;
            }
        }
        if (!ok)
        {
            rocks[{l, c}] = 1, column[c]++;
            firstTask++;
            if (l == 0 && c == 500)
            {
                cout << firstTask + secondTask;
                exit(0);
            }
        }
    }
    void solveFirstTask()
    {
        while (1)
            this->constructSandPath(0, 500, 1);
    }
    void solveSecondTask()
    {
        while (1)
            this->constructSandPath(0, 500, 2);
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
#endif // 1
}
