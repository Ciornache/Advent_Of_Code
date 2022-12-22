#include <bits/stdc++.h>
#define int long long
#define FILES                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#define SIZE 205

using namespace std;
string str;
vector<char> grid[SIZE];
int row, column, orient;
pair<int, int> goR[SIZE][SIZE], goC[SIZE][SIZE];
int startRow, startColumn, maxCl;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    FILES
    while (getline(cin, str))
    {
        row++;
        column = 0;
        for (int j = 0; j < str.size(); ++j)
            grid[row].push_back(str[j]), column++;
        maxCl = max(maxCl, column);
        if (str.front() >= '0' && str.front() <= '9')
            break;
    }
    column = maxCl;
    row -= 2;
    for (int i = 1; i <= row; ++i)
    {
        int sz = column - grid[i].size() + 1;
        for (int j = 1; j <= sz; ++j)
            grid[i].push_back(' ');
    }
    for (int j = 1; j <= column + 2; ++j)
    {
        grid[row + 1].push_back(' ');
        grid[0].push_back(' ');
    }
    row++;
    for (int j = 0; j < column; ++j)
    {
        vector<pair<int, int>> el;
        if (grid[1][j] != ' ')
            el.push_back({1, j});
        for (int i = 2; i <= row; ++i)
        {
            if (grid[i][j] != ' ' && grid[i - 1][j] == ' ')
                el.push_back({i, j});
            if (grid[i][j] == ' ' && grid[i - 1][j] != ' ')
            {
                i--;
                goR[i][j] = el.back();
                goR[el.back().first][el.back().second] = {i, j};
                break;
            }
        }
    }

    for (int i = 1; i <= row; ++i)
    {
        vector<pair<int, int>> el;
        if (grid[i][0] != ' ')
            el.push_back({i, 0});
        for (int j = 1; j < column; ++j)
        {
            if (grid[i][j] != ' ' && grid[i][j - 1] == ' ')
                el.push_back({i, j});
            if (grid[i][j] == ' ' && grid[i][j - 1] != ' ')
            {
                j--;
                goC[i][j] = el.back();
                goC[el.back().first][el.back().second] = {i, j};
                break;
            }
        }
    }

    int cl = 1;
    for (auto j : grid[1])
    {
        if (j == '.')
        {
            startColumn = cl;
            break;
        }
        cl++;
    }
    startRow = 1;
    int nr = 0, lt = 0;
    for (int j = 0; j < str.size(); ++j)
    {

        if (str[j] >= '0' && str[j] <= '9')
            nr = nr * 10 + str[j] - '0';
        if (str[j] == 'R' || str[j] == 'L' || str[j] == 'X')
        {
            for (int i = 1; i <= nr; ++i)
            {
                startRow += dx[orient];
                startColumn += dy[orient];
                if (grid[startRow][startColumn] == '#')
                {
                    startRow -= dx[orient], startColumn -= dy[orient];
                    break;
                }
                if ((grid[startRow][startColumn] == ' ') || (startColumn == -1) || (startRow == 0))
                {
                    startRow -= dx[orient];
                    startColumn -= dy[orient];
                    pair<int, int> el;
                    if (dx[orient])
                        el = goR[startRow][startColumn];
                    else
                        el = goC[startRow][startColumn];
                    if (grid[el.first][el.second] == '#')
                        break;

                    startRow = el.first, startColumn = el.second;
                }
            }
            if (str[j] == 'R')
                orient = (orient + 1) % 4;
            else if (str[j] == 'L')
                orient = (orient - 1 + 4) % 4;
            lt++;
            nr = 0;
        }
    }
    cout << startRow * 1000 + (startColumn + 1) * 4 + orient;
}
