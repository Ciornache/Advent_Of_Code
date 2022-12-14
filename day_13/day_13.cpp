#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

#define SIZE 205
#define FILES                        \
    freopen("input.in", "r", stdin); \
    freopen("output.out", "w", stdout);

using namespace std;

class Solution
{
private:
    string str;
    string str2;
    int firstTask;
    vector<pair<string, string>> pairs;

public:
    Solution()
    {
        this->readInput();
        firstTask = 0;
    }
    void readInput()
    {
        while (getline(cin, str))
        {
            getline(cin, str2);
            pairs.push_back({str, str2});
            getline(cin, str);
        }
    }
    vector<int> convertToList(string a)
    {
        vector<int> lis;
        stack<int> s[SIZE];
        int depth = 0;
        for (int i = 0; i < a.size(); ++i)
        {
            if (a[i] == '[')
            {
                depth++;
                s[depth].push(-1);
            }
            if (a[i] == ']')
            {
                vector<int> r;
                while (!s[depth].empty())
                {
                    r.push_back(s[depth].top());
                    s[depth].pop();
                }
                depth--;
                reverse(r.begin(), r.end());
                for (int j = 0; j < r.size(); ++j)
                    s[depth].push(r[j]);
            }
            if (a[i] >= '0' && a[i] <= '9')
            {
                s[depth].top() = 0;
                while (i < a.size() && a[i] >= '0' && a[i] <= '9')
                    s[depth].top() = s[depth].top() * 10 + a[i] - '0', i++;
                s[depth].push(-1);
                i--;
            }
        }
        while (!s[0].empty())
        {
            lis.push_back(s[0].top());
            s[0].pop();
        }
        reverse(lis.begin(), lis.end());
        return lis;
    }
    void solveFirstTask()
    {
        for (int i = 0; i < pairs.size(); ++i)
        {
            vector<int> firstList = convertToList(pairs[i].first);
            vector<int> secondList = convertToList(pairs[i].second);
            bool ok = compareLists(firstList, secondList);

            if (ok)
            {
                firstTask += i + 1;
                cout << pairs[i].first << '\n'
                     << pairs[i].second << "\n\n";
                for (auto i : firstList)
                    cout << i << ' ';
                cout << '\n';
                for (auto i : secondList)
                    cout << i << ' ';
                cout << "\n\n";
            }
        }
        cout << firstTask << '\n';
    }
    bool compareLists(vector<int> a, vector<int> b)
    {
        int i = 0, j = 0;
        while (i < a.size() && j < b.size())
        {
            while (i < a.size() && a[i] == -1)
                i++;
            while (j < b.size() && b[j] == -1)
                j++;
            if (i == a.size() && j == b.size())
            {
                if (a.size() > b.size())
                    return 0;
                else
                    return 1;
                continue;
            }
            if (i < a.size() && j < b.size())
            {
                if (a[i] > b[j])
                    return 0;
                else if (b[j] > a[i])
                    return 1;
            }
            if (i < a.size() && j == b.size())
                return 0;
            if (j < b.size() && i == a.size())
                return 1;
        }
    }
};
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    FILES
    Solution solver;
    solver.solveFirstTask();
    // cout << "HELLO WORLD";
}