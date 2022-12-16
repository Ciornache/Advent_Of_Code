#include <bits/stdc++.h>

#define MAX 20000
#define SIZE 4
#define WANTED_LINE 4000000
#define FILES                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#define int long long

using namespace std;

struct element
{
    int line;
    int column;
};
class Solution
{

private:
    const int dx[SIZE] = {-1, 1, 0, 0};
    const int dy[SIZE] = {0, 0, -1, 1};
    vector<element> beacon;
    vector<element> sensor;
    vector<pair<int, int>> interval;
    map<pair<int, int>, bool> block;
    int firstTask;

public:
    bool cmp(element a, element b)
    {
        if (a.line != b.line)
            return a.line < b.line;
        return a.column < b.column;
    }
    Solution()
    {
        this->readInput();
        firstTask = 0;
    }
    void readInput()
    {
        string str;
        while (getline(cin, str))
        {
            int cnt = 0;
            for (int i = 0; i < str.size(); ++i)
            {
                element el;
                el.line = el.column = 0;
                if (str[i] == '=')
                {
                    cnt++;
                    i++;
                    bool minus = false;
                    while ((i < str.size() && str[i] >= '0' && str[i] <= '9') || str[i] == '-')
                    {
                        if (str[i] == '-')
                        {
                            minus = true;
                            i++;
                            continue;
                        }
                        el.column = el.column * 10 + str[i++] - '0';
                    }
                    i += 4;
                    if (minus)
                        el.column = -el.column;
                    minus = false;
                    while (i < str.size() && str[i] >= '0' && str[i] <= '9')
                    {
                        el.line = el.line * 10 + str[i++] - '0';
                        if (str[i] == '-')
                        {
                            minus = true;
                            i++;
                        }
                    }

                    if (minus)
                        el.line = -el.line;
                    if (cnt == 1)
                        sensor.push_back(el);
                    else
                        beacon.push_back(el);
                }
            }
        }
    }
    void processSensors(int ln)
    {
        for (int i = 0; i < beacon.size(); ++i)
            simulate(ln, i);
    }
    void simulate(int ln, int i)
    {
        int manhattanDistance = abs(beacon[i].line - sensor[i].line) + abs(beacon[i].column - sensor[i].column);
        int destination = sensor[i].line + manhattanDistance;
        int destination2 = sensor[i].line - manhattanDistance;
        if (destination >= ln && ln >= sensor[i].line)
        {
            int diff = abs(destination - (ln));
            interval.push_back({sensor[i].column - diff, sensor[i].column + diff});
        }
        else if (destination2 <= ln && ln <= sensor[i].line)
        {
            int diff = abs(destination2 - (ln));
            interval.push_back({sensor[i].column - diff, sensor[i].column + diff});
            if (interval.back().first > interval.back().second)
                swap(interval.back().first, interval.back().second);
        }
    }
    bool inside(int x, int y, int z, int k)
    {
        if (x > z)
            swap(x, z), swap(y, k);
        else if (y > k)
            swap(y, k);
        if (y >= z)
            return 1;
        return 0;
    }
    void getResult(int j)
    {
        sort(interval.begin(), interval.end());
        vector<element> res;
        for (int i = 0; i < interval.size(); ++i)
        {
            int x = interval[i].first, y = interval[i].second;
            i++;
            while (i < interval.size() && inside(x, y, interval[i].first, interval[i].second))
            {
                x = min(x, interval[i].first);
                y = max(y, interval[i].second);
                i++;
            }
            firstTask += (y - x + 1);

            res.push_back({x, y});
            i--;
        }
        if (res.size() != 1)
        {
            cout << (res[0].column + 1) * 4000000 + j;
            exit(0);
        }
        interval.clear();
    }
    void solveSecondTask()
    {
        for (int i = 1; i <= WANTED_LINE; ++i)
        {
            this->processSensors(i);
            this->getResult(i);
        }
        cout << firstTask;
    }
    void solveFirstTask()
    {
        this->processSensors(WANTED_LINE);
        this->getResult(WANTED_LINE);
        cout << firstTask;
    }
};
signed main()
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
