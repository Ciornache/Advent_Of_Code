#include <bits/stdc++.h>

using namespace std;
string s, s2;
int ans, first, last, first2, last2;
char c;
int main()
{
    ifstream cin("tx.in");
    ofstream cout("tx.out");
    while (cin >> first >> c >> last >> c >> first2 >> c >> last2)
    {
        if (first > first2)
            swap(first, first2), swap(last, last2);
        else if (last > last2)
            swap(last, last2);

        if (last >= first2)
            ans++;
    }
    cout << ans;
}
