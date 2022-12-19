#include <bits/stdc++.h>

#define MAX_ROW 1000000
#define LAST_LAP 2022 * 3
#define SIZE 6
#define int long long
#define FILES                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
using namespace std;

int currentRow = MAX_ROW, heatIndex, cycle[2000];
const int chX[4] = {-1, 1, 0, 0};
const int chY[4] = {0, 0, -1, 1};
vector<int> stone[SIZE] = {{3, 4, 5, 6}, {4, 3, 4, 5, 4}, {5, 5, 3, 4, 5}, {3, 3, 3, 3}, {3, 4, 3, 4}};
vector<int> cpStone[SIZE] = {{3, 4, 5, 6}, {4, 3, 4, 5, 4}, {5, 5, 3, 4, 5}, {3, 3, 3, 3}, {3, 4, 3, 4}};
vector<int> dx[SIZE] = {{-1, -1, -1, -1}, {-3, -2, -2, -2, -1}, {-3, -2, -1, -1, -1}, {-4, -3, -2, -1}, {-2, -2, -1, -1}};
vector<int> pattern;
map<pair<int, int>, bool> fallenRocks;
char push;
bool checkForGround(int index, int maxRow)
{
    for (int j = 0; j < stone[index].size(); ++j)
    {
        int newRow = maxRow + dx[index][j] + 2;
        int newColumn = stone[index][j];
        if (fallenRocks[{newRow, newColumn}])
            return true;
    }
    return false;
}
void simulateRock(int index, int lap)
{
    int maximumCurrentRow = currentRow - 4;
    int depth = 0;
    while (maximumCurrentRow < MAX_ROW)
    {
        bool ok = 1;
        for (int j = 0; j < stone[index].size(); ++j)
        {
            stone[index][j] += pattern[heatIndex];
            int row = maximumCurrentRow + dx[index][j] + 1;
            ok &= (stone[index][j] >= 1 && stone[index][j] <= 7);
            ok &= (fallenRocks[{row, stone[index][j]}] == 0);
        }
        if (!ok)
        {
            for (int j = 0; j < stone[index].size(); ++j)
                stone[index][j] -= pattern[heatIndex];
        }
        bool finish = checkForGround(index, maximumCurrentRow);
        heatIndex++;
        heatIndex %= pattern.size();
        if (finish)
            break;
        depth++;
        maximumCurrentRow++;
        //        if(index == 2)
        //        {
        //            cout << pattern[heatIndex - 1] << '\n';
        //            for(int j = 0; j < stone[index].size(); ++j)
        //                cout << maximumCurrentRow + dx[index][j] + 1 << ' ' << stone[index][j] << '\n';
        //            cout << '\n';
        //        }
    }
    cout << lap << ' ' << (MAX_ROW - maximumCurrentRow) << '\n';
    for (int j = 0; j < stone[index].size(); ++j)
    {
        int row = maximumCurrentRow + dx[index][j] + 1;
        int column = stone[index][j];
        currentRow = min(currentRow, row);
        fallenRocks[{row, column}] = 1;
        //        cout << row << ' ' << column << '\n';
        stone[index][j] = cpStone[index][j];
    }
    //    cout << "\n\n";
    cycle[(lap - 318 > 0 ? lap - 318 : 0) % 1745] = (MAX_ROW - maximumCurrentRow - 438) % 2778;
}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    FILES
    while (cin >> push)
    {
        pattern.push_back(1);
        if (push == '<')
            pattern.back() *= -1;
    }
    for (int rock = 0; rock < LAST_LAP; ++rock)
        simulateRock(rock % 5, rock);
    int answer = 438;
    int last = 1000000000000;
    cout << cycle[0] << '\n';
    cout << 1LL * (last / 1745) * 2778 + answer + cycle[((last - 318) % 1745 + 1745) % 1745];
}
