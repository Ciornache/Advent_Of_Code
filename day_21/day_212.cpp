#include <bits/stdc++.h>
#define int long long
#define FILES                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

using namespace std;

map<string, vector<pair<string, int>>> adj;
map<string, int> children, value, cp;
map<string, char> oper;
map<string, pair<int, int>> src;
string str;
set<string> allVertex;
queue<string> q;
int run()
{
    children = cp;
    for (auto i : allVertex)
        if (!children[i])
            q.push(i);
    while (!q.empty())
    {
        string currVertex = q.front();
        q.pop();
        for (auto j : adj[currVertex])
        {
            children[j.first]--;
            if (j.second == 1)
                src[j.first].second = value[currVertex];
            else
                src[j.first].first = value[currVertex];
            if (!children[j.first])
            {
                if (oper[j.first] == '*')
                    value[j.first] = src[j.first].first * src[j.first].second;
                if (oper[j.first] == '+')
                    value[j.first] = src[j.first].first + src[j.first].second;
                if (oper[j.first] == '-')
                    value[j.first] = src[j.first].first - src[j.first].second;
                if (oper[j.first] == '/')
                    value[j.first] = src[j.first].first / src[j.first].second;
                q.push(j.first);
            }
        }
    }
    return src["root"].first;
}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    FILES
    while (getline(cin, str))
    {
        bool ok = 0;
        for (int i = 0; i < str.size(); ++i)
            if (strchr("+-*/", str[i]))
                ok = 1;
        if (!ok)
        {
            string vertex = str.substr(0, 4);
            allVertex.insert(vertex);
            string number = str.substr(6, str.size() - 6 + 1);
            int nr = 0;
            for (int j = 0; j < number.size(); ++j)
                nr = nr * 10 + number[j] - '0';
            value[vertex] = nr;
        }
        else
        {
            string vertex = str.substr(0, 4);
            allVertex.insert(vertex);
            children[vertex] += 2;
            string firstChildren = str.substr(6, 4);
            string secondChildren = str.substr(str.size() - 4, 4);
            adj[firstChildren].push_back({vertex, 0});
            adj[secondChildren].push_back({vertex, 1});
            char operation = str[11];
            oper[vertex] = operation;
        }
    }

    for (auto i : allVertex)
    {
        if (!children[i])
            q.push(i);
        cp[i] = children[i];
    }
    while (!q.empty())
    {
        string currVertex = q.front();
        q.pop();
        for (auto j : adj[currVertex])
        {
            children[j.first]--;
            if (j.second == 1)
                src[j.first].second = value[currVertex];
            else
                src[j.first].first = value[currVertex];
            if (!children[j.first])
            {
                if (oper[j.first] == '*')
                    value[j.first] = src[j.first].first * src[j.first].second;
                if (oper[j.first] == '+')
                    value[j.first] = src[j.first].first + src[j.first].second;
                if (oper[j.first] == '-')
                    value[j.first] = src[j.first].first - src[j.first].second;
                if (oper[j.first] == '/')
                    value[j.first] = src[j.first].first / src[j.first].second;
                q.push(j.first);
            }
        }
    }
    int target = src["root"].second;
    int st = 1, dr = 4000000000000, sol = 0;
    while (st <= dr)
    {
        int mid = (st + dr) >> 1;
        value["humn"] = mid;
        int val = run();
        if (val > target)
            st = mid + 1;
        else if (val <= target)
            dr = mid - 1, sol = mid;
    }
    cout << sol;
}
