#include <iostream>
#include <fstream>
#include <map>

#define FILES                        \
    freopen("input.in", "r", stdin); \
    freopen("output.out", "w", stdout);
#define START_LINE 16
#define START_COLUMN 12

using namespace std;

class Solution
{
private:
    struct Node
    {
        Node *child;
        int line, column;
    };
    Node *root;
    map<pair<int, int>, bool> firstTask, secondTask;

public:
    Solution()
    {
        this->buildRope();
    }
    void buildRope()
    {
        root = new Node;
        Node *prev = root;
        root->line = START_LINE;
        root->column = START_COLUMN;
        for (int i = 1; i <= 9; ++i)
        {
            Node *node = new Node;
            node->line = START_LINE;
            node->column = START_COLUMN;
            prev->child = node;
            prev = node;
        }
    }
    void walkThroughGrid()
    {
        char dir;
        int steps;

        while (cin >> dir >> steps)
        {
            for (int i = 1; i <= steps; ++i)
            {
                root->line += (dir == 'D' ? 1 : (dir == 'U' ? -1 : 0));
                root->column += (dir == 'R' ? 1 : (dir == 'L' ? -1 : 0));
                Node *head = root;
                for (int j = 1; j <= 9; ++j)
                {
                    Node *tail = head->child;
                    this->updateNode(head, tail);
                    head = tail;
                    if (j == 1)
                        firstTask[{head->line, head->column}] = 1;
                }
                secondTask[{head->line, head->column}] = 1;
            }
        }
    }
    void updateNode(Node *head, Node *tail)
    {
        int diffLin = head->line - tail->line;
        int diffCol = head->column - tail->column;
        if (abs(diffLin) + abs(diffCol) >= 2)
        {
            if (abs(diffLin) == 1 && abs(diffCol) == 1)
                return;

            if (diffLin > 0)
                tail->line++;
            else if (diffLin < 0)
                tail->line--;

            if (diffCol > 0)
                tail->column++;
            else if (diffCol < 0)
                tail->column--;
        }
    }
    void solveFirstTask()
    {
        this->walkThroughGrid();
        cout << firstTask.size();
    }
    void solveSecondTask()
    {
        this->walkThroughGrid();
        cout << secondTask.size();
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    FILES
    Solution solver;
    solver.solveSecondTask();
}
