#include <bits/stdc++.h>

#define NUMBER_OF_ITERATIONS 10
#define NUMBER_OF_DIRECTIONS 4
#define MAX 100
#define FILES freopen("input.txt", "r", stdin);\
              freopen("output.txt", "w", stdout);
#define fastio ios_base::sync_with_stdio(0);\
               cin.tie(0), cout.tie(0);


struct moveBy
{
    int diffRow;
    int diffCol;
};

struct position
{
    int line;
    int column;
};

std::vector <moveBy> coordinates[NUMBER_OF_DIRECTIONS] = {{
        {-1, -1}, {-1, 0}, {-1, 1}
    },
    {{1, -1}, {1, 0}, {1, 1}},
    {{-1, -1}, {0, -1}, {1, -1}},
    {{-1, 1}, {0, 1}, {1, 1}}
};

int currentCoordinates[4] = {0, 1, 2, 3};

const moveBy makeMove[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int numberOfFreeTiles;

std::string input;

std::vector<position> elf;

using namespace std;

pair<int,int> allDirections[10] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

int rows, columns;
char grid[MAX + 5][MAX + 5];

struct cmp
{
    bool operator()(position a, position b) const
    {
        if(a.line != b.line)
            return a.line < b.line;
        return a.column < b.column;
    }
};

map<position, int, cmp> elfLocations;

bool elvesInSurrounding(int row, int column)
{
    for(int i = 0; i < 8; ++i)
    {
        row += allDirections[i].first;
        column += allDirections[i].second;
        if(elfLocations[ {row, column}])
            return true;
        row -= allDirections[i].first;
        column -= allDirections[i].second;
    }
    return false;
}

int getDirections(position elf)
{

    int firstIndex = 5;

    bool location = elvesInSurrounding(elf.line, elf.column);
    if(!location)
        return -1;

    for(int i = 0; i < NUMBER_OF_DIRECTIONS; ++i)
    {
        position elfCopy = elf;

        bool ok2 = 1;

        for(auto _direction : coordinates[i])
        {
            elfCopy.line += _direction.diffRow;
            elfCopy.column += _direction.diffCol;

            ok2 &= (!elfLocations[elfCopy]);

            elfCopy = elf;
        }

//        if(elf.line == 6 && elf.column == 3)
//            std::cout << ok2 << ' ' << i << '\n';

        if(ok2)
            firstIndex = min(firstIndex, i);
    }


//    if(elf.line ==  1 && elf.column == 9)
//        std::cout << firstIndex << ' ' << currentCoordinates[firstIndex] << " HERE\n";

    if(firstIndex == 5)
        return -1;

    return currentCoordinates[firstIndex];
}

void cyclePositions(int direction)
{
    for(int i = 0; i < NUMBER_OF_DIRECTIONS; ++i)
    {
        if(currentCoordinates[i] == direction)
        {
            for(int j = i + 1; j < NUMBER_OF_DIRECTIONS; ++j)
            {
                swap(coordinates[j], coordinates[j - 1]);
                swap(currentCoordinates[j], currentCoordinates[j - 1]);
            }
        }
    }
}

void moveElves(vector<position> * elf)
{
    vector<int> directions;

    map<position, int, cmp> nextPosition;
    for(int i = 0; i < elf->size(); ++i)
    {
        int direction = getDirections((*elf)[i]);

        directions.push_back(direction);

        if(direction == -1)
            continue;

        position elfCopy = (*elf)[i];
        elfCopy.line += makeMove[direction].diffRow;
        elfCopy.column += makeMove[direction].diffCol;
        nextPosition[elfCopy]++;

//        std::cout << elfCopy.line << ' ' << elfCopy.column << '\n';
    }


//    std::cout << '\n';

    for(int i = 0; i < elf->size(); ++i)
    {

        position elfCopy = (*elf)[i];

        if(directions[i] == -1)
        {
//            std::cout << (*elf)[i].line << ' ' << (*elf)[i].column << '\n';
            continue;
        }

        elfCopy.line += makeMove[directions[i]].diffRow;
        elfCopy.column += makeMove[directions[i]].diffCol;
        if(nextPosition[elfCopy] > 1)
        {
//            std::cout << (*elf)[i].line << ' ' << (*elf)[i].column << '\n';
            continue;
        }
        elfLocations[(*elf)[i]] = 0;
        (*elf)[i] = elfCopy;
        elfLocations[(*elf)[i]] = 1;
//
//        std::cout << elfCopy.line << ' ' << elfCopy.column << '\n';

    }

    for(auto direction : directions)
    {
        if(direction != -1)
        {
            cyclePositions(direction);
            break;
        }
    }
    std::cout << '\n';
}

void minimumRectangleArea()
{
    std::cout << rows << ' ' << columns << ' ' << elf.size() << '\n';

    int leftRow = 105, leftColumn = 105, rightRow = 0, rightColumn = 0;

    for(auto elfIndex : elfLocations)
    {
        if(elfIndex.second)
        {
            leftRow = min(leftRow, elfIndex.first.line);
            leftColumn = min(leftColumn, elfIndex.first.column);
            rightRow = max(rightRow, elfIndex.first.line);
            rightColumn = max(rightColumn, elfIndex.first.column);
        }
    }

    std::cout << leftRow << ' ' << leftColumn << ' ' << rightRow << ' ' << rightColumn << '\n';

    for(int i = leftRow; i <= rightRow; ++i)
    {
        for(int j = leftColumn; j <= rightColumn; ++j)
        {
            if(!elfLocations[ {i, j}])
                numberOfFreeTiles++;
        }
    }
}

void read()
{
    while(getline(cin, input))
    {
        rows++;
        for(int c = 0; c < input.size(); ++c)
            grid[rows][c + 1] = input[c];
        columns = input.size();
    }
}

void init()
{
    for(int i = 1; i <= rows; ++i)
    {
        for(int j = 1; j <= columns; ++j)
        {
            if(grid[i][j] == '#')
            {
                elf.push_back({i, j});
                elfLocations[ {i, j}]++;
            }
        }
    }
}

int main()
{
    FILES
    fastio
    read();
    init();

    for(int i = 0; i < elf.size(); ++i)
        std::cout << elf[i].line << ' ' << elf[i].column << '\n';

    std::cout << '\n';

    for(int iterationIndex = 1; iterationIndex <= NUMBER_OF_ITERATIONS; ++iterationIndex)
        moveElves(&elf);

    minimumRectangleArea();

    std::cout << numberOfFreeTiles;
}
