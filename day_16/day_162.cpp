#include <bits/stdc++.h>

#define FILES                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#define SIZE 27 * 27 + 5
#define MIN_SIZE 27
using namespace std;
string str;
vector<int> valve[SIZE];
int pressure[SIZE], answer, minDist[SIZE][SIZE], dp[SIZE][SIZE][MIN_SIZE][MIN_SIZE];
bool check[SIZE];
int convertToInt(char a, char b)
{
    return (a - 'A' + 1) * 26 + b - 'A' + 1;
}
set<int> valves;
void solveFirstTask(int node, int time, int totalPressure, int elephant, int sTime)
{
    answer = max(answer, totalPressure);
    if (time == 26)
        return;
    dp[node][elephant][time][sTime] = totalPressure;
    for (auto i : valves)
    {
        int newTime = time + minDist[node][i] + 1;
        if (!check[i] && newTime <= 26 && pressure[i] > 0)
        {
            int newTotalPressure = totalPressure + (26 - newTime) * pressure[i];
            for (auto j : valves)
            {
                if (i != j)
                {
                    int newTime2 = sTime + minDist[elephant][j] + 1;
                    if (!check[j] && newTime2 <= 26 && newTotalPressure + (26 - newTime2) * pressure[j] > dp[i][j][newTime][newTime2] && pressure[j] > 0)
                    {
                        check[i] = check[j] = 1;
                        solveFirstTask(i, newTime, newTotalPressure + (26 - newTime2) * pressure[j], j, newTime2);
                        check[i] = check[j] = 0;
                    }
                }
            }
        }
    }
}
void minimumDistance(int node, int dist, int root)
{
    queue<pair<int, int>> q;
    q.push({node, dist});
    while (!q.empty())
    {
        node = q.front().first;
        dist = q.front().second;
        minDist[root][node] = dist;
        check[node] = 1;
        for (auto i : valve[node])
        {
            if (!check[i])
            {
                q.push({i, dist + 1});
                check[i] = 1;
            }
        }
        q.pop();
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    FILES
    while (getline(cin, str))
    {
        int currentValve = 0;
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
            {
                char c = str[i + 1];
                if (c >= 'A' && c <= 'Z')
                {
                    int valveIndex = convertToInt(str[i], c);
                    if (!currentValve)
                        currentValve = valveIndex;
                    else
                        valve[currentValve].push_back(valveIndex), valve[valveIndex].push_back(currentValve);

                    i++;
                }
            }
            if (str[i] >= '0' && str[i] <= '9')
                pressure[currentValve] = pressure[currentValve] * 10 + str[i] - '0';
        }
        valves.insert(currentValve);
    }
    for (auto i : valves)
    {
        memset(check, false, sizeof(check));
        minimumDistance(i, 0, i);
    }
    memset(check, false, sizeof(check));
    solveFirstTask(27, 0, 0, 27, 0);
    cout << answer;
}
