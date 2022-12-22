#include <bits/stdc++.h>

#define FILES                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#define SIZE 25
#define MAX_ROBOT 16
#define MAX_ORE 16
#define MAX_CLAY 22
#define MAX_OBSIDIAN 28
#define MAX_TIME 32

using namespace std;
int id, ore, clay, answer = 1, bp;
pair<int, int> obsidian, geode;
string str;
int dfs(int _ore, int _clay, int _obsidian, int _geode, int time, int totalOre, int totalClay, int totalObsidian, int totalGeode)
{

    int newTotalOre = totalOre + _ore;
    int newTotalClay = totalClay + _clay;
    int newTotalObsidian = totalObsidian + _obsidian;
    int newTotalGeode = totalGeode + _geode;
    if (time == MAX_TIME)
        return newTotalGeode;
    int answer = 0;
    bool ok = 0;
    if (totalOre >= geode.first && totalObsidian >= geode.second)
    {
        int maxGeodes = dfs(_ore, _clay, _obsidian, _geode + 1, time + 1, newTotalOre - geode.first, newTotalClay, newTotalObsidian - geode.second, newTotalGeode);
        answer = max(answer, maxGeodes);
        return answer;
    }
    if (totalOre >= ore && _ore < MAX_ROBOT && time <= MAX_ORE)
    {
        int maxGeodes = dfs(_ore + 1, _clay, _obsidian, _geode, time + 1, newTotalOre - ore, newTotalClay, newTotalObsidian, newTotalGeode);
        answer = max(answer, maxGeodes);
    }
    if (totalOre >= clay && _clay < MAX_ROBOT && time <= MAX_CLAY)
    {
        int maxGeodes = dfs(_ore, _clay + 1, _obsidian, _geode, time + 1, newTotalOre - clay, newTotalClay, newTotalObsidian, newTotalGeode);
        answer = max(answer, maxGeodes);
    }
    if (totalOre >= obsidian.first && totalClay >= obsidian.second && _obsidian < MAX_ROBOT && time <= MAX_OBSIDIAN)
    {
        int maxGeodes = dfs(_ore, _clay, _obsidian + 1, _geode, time + 1, newTotalOre - obsidian.first, newTotalClay - obsidian.second, newTotalObsidian, newTotalGeode);
        answer = max(answer, maxGeodes);
    }
    int cnt = 1e9, cnt2 = 0;
    if (_ore < MAX_ROBOT && totalOre < ore)
    {
        while (newTotalOre < ore)
            newTotalOre += _ore, cnt2++;
        if (time + cnt2 + 1 <= MAX_ORE)
            answer = max(answer, dfs(_ore, _clay, _obsidian, _geode, time + cnt2 + 1, newTotalOre, newTotalClay + _clay * cnt2, newTotalObsidian + _obsidian * cnt2, newTotalGeode + _geode * cnt2)), ok = 1;
        newTotalOre -= cnt2 * _ore;
    }
    if (_obsidian < MAX_ROBOT && _clay > 0 && _ore > 0 && (totalClay < obsidian.second || totalOre < obsidian.first))
    {
        cnt2 = 0;
        while ((newTotalClay < obsidian.second || newTotalOre < obsidian.first))
            newTotalOre += _ore, newTotalClay += _clay, cnt2++;
        if (time + cnt2 + 1 <= MAX_OBSIDIAN)
            answer = max(answer, dfs(_ore, _clay, _obsidian, _geode, time + cnt2 + 1, newTotalOre, newTotalClay, newTotalObsidian + cnt2 * _obsidian, newTotalGeode + cnt2 * _geode)), ok = 1;
        newTotalOre -= cnt2 * _ore;
        newTotalClay -= cnt2 * _clay;
    }
    if (_clay < MAX_ROBOT && totalOre < clay)
    {
        cnt2 = 0;
        while (newTotalOre < clay)
            newTotalOre += _ore, cnt2++;
        if (time + cnt2 + 1 <= MAX_CLAY)
            answer = max(answer, dfs(_ore, _clay, _obsidian, _geode, time + cnt2 + 1, newTotalOre, newTotalClay + cnt2 * _clay, newTotalObsidian + cnt2 * _obsidian, newTotalGeode + cnt2 * _geode)), ok = 1;
        newTotalOre -= cnt2 * _ore;
    }
    if ((totalOre < geode.first || totalObsidian < geode.second) && _obsidian > 0)
    {
        cnt2 = 0;
        while ((newTotalObsidian < geode.second || newTotalOre < geode.first))
            newTotalOre += _ore, newTotalObsidian += _obsidian, cnt2++;
        if (time + cnt2 + 1 <= MAX_TIME)
            answer = max(answer, dfs(_ore, _clay, _obsidian, _geode, time + cnt2 + 1, newTotalOre, newTotalClay + cnt2 * _clay, newTotalObsidian, newTotalGeode + cnt2 * _geode)), ok = 1;
        newTotalOre -= cnt2 * _ore;
        newTotalObsidian -= cnt2 * _obsidian;
    }
    if (time > MAX_OBSIDIAN && time < MAX_TIME)
        answer = max(answer, dfs(_ore, _clay, _obsidian, _geode, time + 1, newTotalOre, newTotalClay, newTotalObsidian, newTotalGeode));

    return answer;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    FILES
    while (getline(cin, str))
    {
        int cnt = 0;
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] >= '0' && str[i] <= '9')
            {
                cnt++;
                int x = 0;
                while (i < str.size() && str[i] >= '0' && str[i] <= '9')
                    x = x * 10 + str[i++] - '0';
                if (cnt == 1)
                    id = x;
                else if (cnt == 2)
                    ore = x;
                else if (cnt == 3)
                    clay = x;
                else if (cnt > 3)
                {
                    int y = 0;
                    while (i < str.size() && str[i] < '0' || str[i] > '9')
                        i++;
                    while (i < str.size() && str[i] >= '0' && str[i] <= '9')
                        y = y * 10 + str[i++] - '0';
                    if (cnt == 4)
                        obsidian = {x, y};
                    else
                        geode = {x, y};
                }
            }
        }
        int maximumGeodes = dfs(1, 0, 0, 0, 1, 0, 0, 0, 0);
        answer *= maximumGeodes;
        bp++;
        if (bp == 3)
            break;
    }
    cout << answer;
}
