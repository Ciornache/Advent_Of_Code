#include <bits/stdc++.h>

using namespace std;
string rucksack;
int ans;
int main()
{
    ifstream cin("txt.in");
    ofstream cout("txt.out");
    while (getline(cin, rucksack))
    {
        map<char, int> mp, mp2, mp3;
        for (auto i : rucksack)
            mp[i]++;
        getline(cin, rucksack);
        for (auto i : rucksack)
            mp2[i]++;
        getline(cin, rucksack);
        for (auto i : rucksack)
            mp3[i]++;
        for (int i = 'a'; i <= 'z'; ++i)
            if (mp[i] && mp2[i] && mp3[i])
                ans += i - 'a' + 1;
        for (int i = 'A'; i <= 'Z'; ++i)
            if (mp[i] && mp2[i] && mp3[i])
                ans += i - 'A' + 27;
    }
    cout << ans;
}
