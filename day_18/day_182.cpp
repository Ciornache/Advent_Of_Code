#include <bits/stdc++.h>

#define FILES                         \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

using namespace std;

struct cube
{
    int width;
    int length;
    int height;
    bool operator<(const cube &a) const
    {
        if (a.width != width)
            return width < a.width;
        if (a.length != length)
            return a.length < length;
        return a.height > height;
    }
    friend ostream &operator<<(ostream &os, cube &a)
    {
        os << a.width << ' ' << a.length << ' ' << a.height << '\n';
        return os;
    }
    void setCube(int x, int y, int z)
    {
        width = x;
        length = y;
        height = z;
    }
    bool operator==(const cube &a)
    {
        return (a.width == width && a.length == length && a.height == height);
    }
};
cube Lowest, Highest;
map<cube, bool> space, emptyCubes, impCubes;
map<cube, bool> hey;
map<cube, int> component;
vector<cube> allCubes;
set<cube> airCubes;
string str;
int answer;
vector<int> dl;
vector<bool> type;
void extractNumber(int &a, int &j)
{
    while (j < str.size() && str[j] >= '0' && str[j] <= '9')
        a = a * 10 + str[j++] - '0';
    j++;
}
bool dfs(int w, int l, int h, int edges)
{
    emptyCubes[{w, l, h}] = 1;
    component[{w, l, h}] = edges;
    int total = 0;
    int totalCubes = 0;
    vector<cube> neigh;
    bool ok2 = 0;
    for (int face1 = -1; face1 < 2; ++face1)
    {
        for (int face2 = -1; face2 < 2; ++face2)
        {
            for (int face3 = -1; face3 < 2; ++face3)
            {
                int sum = abs(face1) + abs(face2) + abs(face3);
                if (sum == 1)
                {
                    cube newCube = {w + face1, l + face2, h + face3};
                    if (space[newCube])
                        total++, totalCubes++;
                    else if (impCubes[newCube] && emptyCubes[newCube])
                        total++;
                    if (component[newCube])
                        ok2 |= (type[component[newCube]] == 0);
                    if (!space[newCube] && !emptyCubes[newCube])
                        neigh.push_back(newCube);
                }
            }
        }
    }
    if (w > Highest.width || l > Highest.length && h > Highest.height)
        ok2 = 1;
    if (w < Lowest.width || l < Lowest.length && h < Lowest.height)
        ok2 = 1;
    if (ok2 == 0)
    {
        bool ok = 0;
        for (auto i : neigh)
        {
            if (!emptyCubes[{i.width, i.length, i.height}])
                ok |= dfs(i.width, i.length, i.height, edges);
        }
        type[edges] = (type[edges] & !ok);
        dl.back() += totalCubes;
        return ok;
    }
    type[edges] = (type[edges] & !ok2);
    return ok2;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    FILES
    while (cin >> str)
    {
        cube cb;
        cb.setCube(0, 0, 0);
        int i = 0;
        extractNumber(cb.width, i);
        extractNumber(cb.length, i);
        extractNumber(cb.height, i);
        if (space[cb])
            cout << cb;
        space[cb] = hey[cb] = 1;
        allCubes.push_back(cb);
    }
    Lowest = {0, 0, 0};
    Highest = {22, 22, 22};
    for (auto i : allCubes)
    {
        int availableCubes = 6;
        for (int face1 = -1; face1 < 2; ++face1)
        {
            for (int face2 = -1; face2 < 2; ++face2)
            {
                for (int face3 = -1; face3 < 2; ++face3)
                {
                    int sum = abs(face1) + abs(face2) + abs(face3);
                    if (sum == 1)
                    {
                        cube newCube = {i.width + face1, i.length + face2, i.height + face3};
                        availableCubes -= space[newCube];
                        hey[newCube] = 1;
                        if (!space[newCube])
                        {
                            impCubes[newCube] = 1, airCubes.insert(newCube);
                            cube g = {6, 11, 8};
                        }
                    }
                }
            }
        }
        answer += availableCubes;
    }
    dl.push_back(0);
    type.push_back(1);
    for (auto i : airCubes)
    {
        if (!emptyCubes[i])
        {
            dl.push_back(0);
            type.push_back(1);
            dfs(i.width, i.length, i.height, dl.size() - 1);
            if (type.back())
                answer -= dl.back();
        }
    }
    cout << answer;
}
