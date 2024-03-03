#include <bits/stdc++.h>
using namespace std;

class Snake;
class Ladder;
class Player;
class Board;

int dice()
{
    int random_no = rand() % 6 + 1;
    return random_no;
}
class Snake
{
    int head;
    int tail;

public:
    Snake(int head, int tail)
    {
        this->head = head;
        this->tail = tail;
    }
    int getHead()
    {
        return head;
    }
    int getTail()
    {
        return tail;
    }
};

class Ladder
{
    int start;
    int end;

public:
    Ladder(int start, int end)
    {
        this->start = start;
        this->end = end;
    }
    int getStart()
    {
        return start;
    }
    int getEnd()
    {
        return end;
    }
};

class Player
{
    string name;
    int positionOnBoard;

public:
    Player(string name)
    {
        this->name = name;
        positionOnBoard = 0;
    }
    string getName()
    {
        return name;
    }
    int getPositionOnBoard()
    {
        return positionOnBoard;
    }
    void setPosition(int positionOnBoard)
    {
        this->positionOnBoard = positionOnBoard;
    }
};

class Board
{
    vector<Snake> snakes;
    vector<Ladder> ladders;

public:
    Board(vector<pair<int, int>> snakeDetail, vector<pair<int, int>> ladderDetail)
    {

        for (int i = 0; i < snakeDetail.size(); i++)
        {
            Snake snake(snakeDetail[i].first, snakeDetail[i].second);
            snakes.push_back(snake);
        }
        for (int i = 0; i < ladderDetail.size(); i++)
        {
            Ladder ladder(ladderDetail[i].first, ladderDetail[i].second);
            ladders.push_back(ladder);
        }
    }
    void snakeRecur(int &position)
    {
        for (int i = 0; i < snakes.size(); i++)
        {
            if (snakes[i].getHead() == position)
            {
                position = snakes[i].getTail();
                snakeRecur(position);
            }
        }
    }
    void ladderRecur(int &position)
    {
        for (int i = 0; i < ladders.size(); i++)
        {
            if (ladders[i].getStart() == position)
            {
                position = ladders[i].getEnd();
                ladderRecur(position);
            }
        }
    }
    int move(int position, int dice_value)
    {
        int next_position = dice_value + position;
        if (next_position > 100)
            return position;

        snakeRecur(next_position);
        ladderRecur(next_position);

        return next_position;
    }
};

int main()
{
    int s, l, p, head, tail, start, end;
    string name;

    vector<pair<int, int>> snakeDetail;
    vector<pair<int, int>> ladderDetail;

    cin >> s;
    for (int i = 0; i < s; i++)
    {
        cin >> head >> tail;
        snakeDetail.push_back({head, tail});
    }

    cin >> l;
    for (int i = 0; i < l; i++)
    {
        cin >> start >> end;
        ladderDetail.push_back({start, end});
    }

    Board board(snakeDetail, ladderDetail);
    cin >> p;

    vector<Player> players;
    for (int i = 0; i < p; i++)
    {
        cin >> name;
        Player player(name);
        players.push_back(player);
    }
    while (1)
    {
        bool winner = false;
        for (auto &p : players)
        {
            int dice_value = dice();

            int positionOnBoard = p.getPositionOnBoard();
            int next_position = board.move(positionOnBoard, dice_value);

            p.setPosition(next_position);

            if (next_position == 100)
            {
                winner = true;
                cout << p.getName() << " wins the game\n";
                break;
            }
            else
                cout << p.getName() << " rolled a " << dice_value << " and moved from " << positionOnBoard << " to " << next_position << "\n";
        }
        if (winner)
            break;
    }
}
