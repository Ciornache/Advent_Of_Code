#include <bits/stdc++.h>
#define MAX 100001
#define mod 10007
#define int long long
using namespace std;
string cmd;
map<string, int> mp;
map<string, int> fsum;
stack<string> st;
int ans = 1e9, s;
vector<int> pr;
signed main()
{
    ifstream cin("tx.in");
    ofstream cout("tx.out");

    while (getline(cin, cmd))
    {
        if (cmd[0] == '$')
        {
            if (cmd[2] == 'c' && cmd[3] == 'd')
            {
                if (cmd[4] != '.' && cmd[5] != '.')
                {
                    string s;
                    for (int i = 5; i < cmd.size(); ++i)
                        s += cmd[i];
                    if (s == "/")
                    {
                        while (!st.empty())
                        {
                            string x = st.top();
                            st.pop();
                            if (!st.empty())
                                mp[st.top()] += mp[x];
                            if (mp[x] < MAX)
                                ans += mp[x];
                            if (x != "/")
                                pr.push_back(mp[x]);
                            mp[x] = 0;
                        }
                    }
                    st.push(s);
                }
                else
                {

                    string x = st.top();
                    st.pop();
                    if (!st.empty())
                        mp[st.top()] += mp[x];
                    if (mp[x] < MAX)
                        ans += mp[x];
                    if (x != "/")
                        pr.push_back(mp[x]);
                    mp[x] = 0;
                }
            }
        }
        else
        {
            for (int i = 0; i < cmd.size(); ++i)
            {
                int nr = 0;

                while (i < cmd.size() && cmd[i] >= '0' && cmd[i] <= '9')
                    nr = nr * 10 + cmd[i] - '0', i++;
                if (nr)
                    /// cout << nr << ' ' << st.top() << '\n';
                    mp[st.top()] += nr, s += nr;
            }
        }
        /// cout << st.top() << ' ' << fsum[st.top()] << ' ' << mp[st.top()] << '\n';
    }
    while (!st.empty())
    {
        string x = st.top();
        st.pop();
        if (!st.empty())
            mp[st.top()] += mp[x];
        if (mp[x] < MAX)
            ans += mp[x];
        pr.push_back(mp[x]);
        if (x != "/")
            mp[x] = 0;
    }
    cout << s << '\n';
    for (auto i : pr)
    {
        if (70000000 - s + i >= 30000000)
            ans = min(ans, i);
    }
    cout << ans;
}
