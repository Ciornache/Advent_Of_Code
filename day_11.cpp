#include <bits/stdc++.h>

#define int long long
#define SIZE 8
#define FILES freopen("input.in","r",stdin);\
              freopen("output.out","w",stdout);
#define mod 9699690 ///lcm of all the division numbers

using namespace std;

class Solution
{
    struct Item
    {
        Item * nextItem;
        int worryLevel, worryChange;
        char oper;
    };

    struct Path
    {
        int monkey, divisionTest;
        bool type;
    };

public:
    vector <Path> edges[SIZE];
    Item * monkey[SIZE];
    Item * roots[SIZE];
    int inspected[SIZE];
    Solution()
    {
        for(int i = 0; i < SIZE; ++i)
        {
            monkey[i] = new Item;
            monkey[i]->worryLevel = monkey[i]->worryChange = 0;
            monkey[i]->nextItem = nullptr;
            roots[i] = monkey[i];
        }

        memset(inspected, false, sizeof(inspected));

        this->readInput();
    }
    void readInput()
    {
        string str;
        while(getline(cin, str))
        {
            int monkeyIndex = str[str.size() - 2] - '0';
            vector<int> Items = this->getItems();
            for(auto i : Items)
            {
                Item * currentItem = new Item;

                monkey[monkeyIndex]->worryLevel = i;
                monkey[monkeyIndex]->nextItem = currentItem;

                currentItem->worryChange = currentItem->worryLevel = 0;
                currentItem->nextItem = nullptr;

                monkey[monkeyIndex] = monkey[monkeyIndex]->nextItem;
            }
            pair<char,int> operation = this->getOperation();
            Item * root = roots[monkeyIndex];
            while(root)
            {
                root->oper = operation.first;
                root->worryChange = operation.second;
                root = root->nextItem;
            }
            getline(cin, str);
            int div = 0;
            for(int i = 0; i < str.size(); ++i)
            {
                int number = 0;
                while(i < str.size() && str[i] >= '0' && str[i] <= '9')
                    number = number * 10 + str[i] - '0', i++;
                if(number)
                    div = number;
            }
            getline(cin, str);
            edges[monkeyIndex].push_back({str.back() - '0', div, 1});
            getline(cin, str);
            edges[monkeyIndex].push_back({str.back() - '0', div, 0});
            getline(cin, str);
        }
    }
    vector<int> getItems()
    {
        string str;
        getline(cin, str);

        vector<int> Items;
        for(int i = 0; i < str.size(); ++i)
        {
            int number = 0;
            while(i < str.size() && str[i] >= '0' && str[i] <= '9')
                number = number * 10 + str[i] - '0', i++;
            if(number)
                Items.push_back(number);
        }
        return Items;
    }
    pair<char,int> getOperation()
    {
        string str;
        getline(cin, str);
        pair<char,int> response;
        for(int i = 0; i < str.size(); ++i)
        {
            if(str[i] == '+' || str[i] == '*')
                response.first = str[i];
            while(i < str.size() && str[i] >= '0' && str[i] <= '9')
                response.second = response.second * 10 + str[i] - '0', i++;
        }
        return response;
    }
    void completeRound(int task)
    {
        for(int i = 0; i < SIZE; ++i)
        {
//            for(int j = 0; j < SIZE; ++j)
//            {
//                Item * root = roots[j];
//                while(root->nextItem)
//                {
//                    cout << root->worryLevel << ' ';
//                    root = root->nextItem;
//                }
//                cout << '\n';
//            }
//            cout << '\n';
            Item * root = roots[i];
            while(root->nextItem)
            {
                inspected[i]++;

                this->performOperation(root, task);

                for(auto j : edges[i])
                {
                    if((root->worryLevel % j.divisionTest && j.type == 0) || (root->worryLevel % j.divisionTest == 0 && j.type == 1))
                    {
                        Item * newItem = new Item;

                        monkey[j.monkey]->nextItem = newItem;
                        monkey[j.monkey]->worryLevel = root->worryLevel;

                        newItem->worryChange = monkey[j.monkey]->worryChange;
                        newItem->oper = monkey[j.monkey]->oper;
                        newItem->nextItem = nullptr;

                        monkey[j.monkey] = monkey[j.monkey]->nextItem;

                    }
                }
                root = root->nextItem;
            }
            roots[i]->nextItem = nullptr, roots[i]->worryLevel = 0;

            monkey[i] = roots[i];
        }
    }
    void performOperation(Item * i, int task)
    {
//        cout << i->worryLevel << ' ' << i->worryChange << '\n';
        int opt = 0;
        if(i->worryChange == 0)
            opt = i->worryLevel;
        else opt = i->worryChange;

        switch(i->oper)
        {
        case '+' :
            i->worryLevel + opt;
        case '*':
            i->worryLevel = i->worryLevel * opt;
        }

        switch(task)
        {
        case 1:
            i->worryLevel = i->worryLevel / 3;
        case 2:
            i->worryLevel = i->worryLevel % mod;
        }
    }
    void solveFirstTask()
    {
        for(int i = 1; i <= 20; ++i)
            this->completeRound(1);

        sort(inspected, inspected + SIZE, greater<int>());
        cout << inspected[0] * inspected[1] << '\n';
    }
    void solveSecondTask()
    {
        for(int i = 1; i <= 10000; ++i)
            this->completeRound(2);

        sort(inspected, inspected + SIZE, greater<int>());
        cout << inspected[0] * inspected[1] << '\n';
    }
};

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    FILES
    Solution solver;
#if 1
    solver.solveFirstTask();
#else
    solver.solveSecondTask();
#endif
}
