#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>

#define MAX_ROW 50
#define MAX_COLUMN 150
#define MAX_TIME 1000
#define fastio                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(0), cout.tie(0);
#define FILES                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#define int long long
#define PMAX 25

using namespace std;

int p5[PMAX], ans[PMAX], sum[PMAX];

int decoder(string s)
{
    int number = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        int pr = s[i] - '0';
        if (s[i] == '-')
            pr = -1;
        else if (s[i] == '=')
            pr = -2;
        number += pr * p5[s.size() - i - 1];
    }
    return number;
}

void encoder(int number)
{
    for (int i = PMAX - 2; i >= 0; --i)
    {
        if (number >= 0)
        {
            if (number - p5[i] + sum[i - 1] < 0)
                continue;
            ans[i]++;
            number -= p5[i];
            if (number - p5[i] + sum[i - 1] < 0)
                continue;
            number -= p5[i];
            ans[i]++;
        }
        else
        {
            if (number + p5[i] - sum[i - 1] > 0)
                continue;
            number += p5[i];
            ans[i]--;
            if (number + p5[i] - sum[i - 1] > 0)
                continue;
            number += p5[i];
            ans[i]--;
        }
    }
    for (int i = PMAX - 2; i >= 0; --i)
    {
        if (ans[i] != 0)
        {
            for (int j = i; j >= 0; --j)
            {
                if (ans[j] >= 0)
                    std::cout << ans[j];
                else
                {
                    if (ans[j] == -1)
                        std::cout << '-';
                    else
                        std::cout << '=';
                }
            }
            break;
        }
    }
}

signed main()
{
    fastio
    FILES
    p5[0] = 1;
    sum[0] = 2;
    for (int i = 1; i <= PMAX - 2; ++i)
    {
        p5[i] = p5[i - 1] * 5;
        sum[i] = sum[i - 1] + p5[i] * 2;
    }

    string s;
    int number = 0;
    while (cin >> s)
    {
        number += decoder(s);
    }
    std::cout << number << '\n';
    encoder(number);
}
