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
        return a.height < height;
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
};

map<cube, bool> space;
vector<cube> allCubes;
string str;
int answer;
void extractNumber(int &a, int &j)
{
    while (j < str.size() && str[j] >= '0' && str[j] <= '9')
        a = a * 10 + str[j++] - '0';
    j++;
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
        space[cb] = 1;
        allCubes.push_back(cb);
    }
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
                    }
                }
            }
        }
        answer += availableCubes;
    }
    cout << answer;
}
