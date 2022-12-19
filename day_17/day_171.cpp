#include <bits/stdc++.h>

#define MAX_ROW 1000000
#define LAST_LAP 2022
#define SIZE 6
#define FILES                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
using namespace std;

int currentRow = MAX_ROW, heatIndex;
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
void simulateRock(int index)
{
    int maximumCurrentRow = currentRow - 4;
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
        maximumCurrentRow++;
    }
    for (int j = 0; j < stone[index].size(); ++j)
    {
        int row = maximumCurrentRow + dx[index][j] + 1;
        int column = stone[index][j];
        currentRow = min(currentRow, row);
        fallenRocks[{row, column}] = 1;
        stone[index][j] = cpStone[index][j];
    }
}
int main()
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
        simulateRock(rock % 5);
    cout << MAX_ROW - currentRow + 1;
}
