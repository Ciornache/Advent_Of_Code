#include <bits/stdc++.h>

#define FILES                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

using namespace std;
struct element
{
    int value;
    int initialPosition;
};
vector<element> arr;
vector<element> fArr;
int x;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    FILES
    while (cin >> x)
        arr.push_back({x, arr.size() + 1});
    for (int i = 1; i <= arr.size(); ++i)
    {
        int pos = 0;
        for (int j = 0; j < arr.size(); ++j)
        {
            if (arr[j].initialPosition == i)
            {
                pos = j;
                break;
            }
        }
        if (arr[pos].value == 0)
            continue;
        int sign = arr[pos].value / abs(arr[pos].value);
        int cnt = abs(arr[pos].value);
        while (cnt)
        {
            if (sign < 0)
            {
                if (pos == 0)
                {
                    for (int j = 1; j < arr.size(); ++j)
                        swap(arr[j], arr[j - 1]);
                    pos = arr.size() - 1;
                }
                swap(arr[pos], arr[pos - 1]);
                pos--;
            }
            else
            {
                if (pos == arr.size() - 1)
                {
                    for (int j = arr.size() - 2; j >= 0; --j)
                        swap(arr[j], arr[j + 1]);
                    pos = 0;
                }
                swap(arr[pos], arr[pos + 1]);
                pos++;
            }
            cnt--;
        }
    }
    for (int i = 0; i < arr.size(); ++i)
    {
        if (arr[i].value == 0)
        {
            for (int j = i + 1; j < arr.size(); ++j)
                fArr.push_back(arr[j]);
            for (int j = 0; j <= i; ++j)
                fArr.push_back(arr[j]);
        }
    }
    int n = fArr.size();
    cout << fArr[1000 % n - 1].value + fArr[2000 % n - 1].value + fArr[3000 % n - 1].value;
}
