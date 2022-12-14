#include <bits/stdc++.h>
#define FILES freopen("input.in","r",stdin);\
              freopen("output.out","w",stdout);
using namespace std;

class Solution
{

public:

    int cycleIndex;
    int strength;
    int answer;
    const int cycles[6] = {20, 60, 100, 140, 180, 220};

    Solution()
    {
        strength = 1;
        cycleIndex = answer = 0;
    }

    void solvefirstTask()
    {

        string cmd;

        while(getline(cin, cmd))
        {
            int size = cmd.size();
            int prevCycleIndex = cycleIndex;
            if(size == 4)
            {
                cycleIndex += 1;
                this->searchSignal(prevCycleIndex, cycleIndex, answer);
                continue;
            }
            else
            {
                cycleIndex += 2;
                this->searchSignal(prevCycleIndex, cycleIndex, answer);
                string part = cmd.substr(5, cmd.size() - 5);
                int modify = this->getValue(part);
                this->strength += modify;
            }
        }

        cout << answer << '\n';
    }
    void solvesecondTask()
    {
        string cmd;
        while(getline(cin, cmd))
        {
            int size = cmd.size();
            int prevCycleIndex = cycleIndex;
            if(size == 4)
            {
                if(cycleIndex > 0 && cycleIndex % 40 == 0)
                    cout << '\n';
                this->drawPixel(cycleIndex);
                cycleIndex += 1;
                continue;
            }
            else
            {
                for(int i = prevCycleIndex; i < prevCycleIndex + 2; ++i)
                {
                    if(i > 0 && i % 40 == 0)
                        cout << '\n';
                    this->drawPixel(i);

                }
                cycleIndex += 2;
                string part = cmd.substr(5, cmd.size() - 5);
                int modify = this->getValue(part);
                this->strength += modify;
            }
        }
    }
    void drawPixel(int pos)
    {
        pos %= 40;
        int l = this->strength - 1, r = this->strength + 1;
//        cout << pos << ' ' << l << ' ' << r << '\n';
        if(pos >= l && pos <= r)
            cout << '#';
        else cout << ' ';
    }
    void searchSignal(int prevSignal, int currSignal, int &answer)
    {
        for(int i = 0; i < 6; ++i)
        {
            if(cycles[i] > prevSignal && cycles[i] <= currSignal)
            {
                answer += this->strength * cycles[i];
            }
        }
    }
    int getValue(string pars)
    {
        int sign = 1, number = 0;
        for(auto i : pars)
        {
            if(i == '-')
                sign = -sign;
            else number = number * 10 + i - '0';
        }
        return sign * number;
    }
};
int main()
{
    FILES
    Solution solver;
#if 0
    solver.solvefirstTask();
#else
    solver.solvesecondTask();
#endif // 1
}
