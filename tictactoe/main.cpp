#include <iostream>

using namespace std;

class tictac
{
public:

    char board[3][3];
    char player = 'x';
    char comp = 'o';

    int x = 0;
    int y = 0;


    void display();
    void randomizeBoard();
    void plplacePiece();
    void aiplacePiece();
    void clearBoard();
    void play(char turn);
    int generateTree(char turn);
    int isFull();
    int spotFilled(int x, int y);
    int isWin();

    int  minmaxfn();

};

int tictac::minmaxfn()
{

}

void tictac::display()
{
    cout << board[0][0];
    cout << board[0][1];
    cout << board[0][2] << endl;
    cout << board[1][0];
    cout << board[1][1];
    cout << board[1][2] << endl;
    cout << board[2][0];
    cout << board[2][1];
    cout << board[2][2] << endl;
}

int tictac::isFull()
{
    int x;
    int y;

    for(x=0; x<3; x++)
    {
        for(y=0; y<3; y++)
        {
            if(board[x][y] == '_')
            {
                //cout << "Board is not full." << endl;
                return 0;
            }
        }
    }
    //cout << "Board is full." << endl;
    return 1;
}

int tictac::spotFilled(int x, int y)
{
    if(board[x][y] == '_')
    {
        return 0; //not filled
    }
    else
    {
        return 1; //is filled
    }
}

void tictac::clearBoard()
{
    for(x=0; x<3; x++)
    {
        for(y=0; y<3; y++)
        {
            board[x][y] = '_';
        }
    }
}

int tictac::isWin()
{
    if(((board[0][0] == board[0][1]) && (board[0][1] == board[0][2]) && (board[0][0] == player)) ||
       ((board[1][0] == board[1][1]) && (board[1][1] == board[1][2]) && (board[1][0] == player)) ||
       ((board[2][0] == board[2][1]) && (board[2][1] == board[2][2]) && (board[2][0] == player)) ||
       ((board[0][0] == board[1][0]) && (board[1][0] == board[2][0]) && (board[0][0] == player)) ||
       ((board[0][1] == board[1][1]) && (board[1][1] == board[2][1]) && (board[0][1] == player)) ||
       ((board[0][2] == board[1][2]) && (board[1][2] == board[2][2]) && (board[0][2] == player)) ||
       ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && (board[0][0] == player)) ||
       ((board[2][0] == board[1][1]) && (board[1][1] == board[0][2]) && (board[2][0] == player)))
    {
        //cout << "You win!" << endl;
        return 1;
    }
    else if(((board[0][0] == board[0][1]) && (board[0][1] == board[0][2]) && (board[0][0] == comp)) ||
       ((board[1][0] == board[1][1]) && (board[1][1] == board[1][2]) && (board[1][0] == comp)) ||
       ((board[2][0] == board[2][1]) && (board[2][1] == board[2][2]) && (board[2][0] == comp)) ||
       ((board[0][0] == board[1][0]) && (board[1][0] == board[2][0]) && (board[0][0] == comp)) ||
       ((board[0][1] == board[1][1]) && (board[1][1] == board[2][1]) && (board[0][1] == comp)) ||
       ((board[0][2] == board[1][2]) && (board[1][2] == board[2][2]) && (board[0][2] == comp)) ||
       ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && (board[0][0] == comp)) ||
       ((board[2][0] == board[1][1]) && (board[1][1] == board[0][2]) && (board[2][0] == comp)))
    {
        //cout << "You lose!" << endl;
        return 2;
    }
    else
    {
        if(isFull() == 1)
        {
            //cout << "Tie." << endl;
        }
        return 0;
    }
}

void tictac::plplacePiece()
{
    int x;
    int y;

    cout << "Where do you want to place your piece?" << endl;
    cout << "x coordinate:" << endl;
    cin >> x;
    cout << "y coordinate:" << endl;
    cin >> y;

    if (((x != 0) && (x != 1) && (x != 2)) ||
        ((y != 0) && (y != 1) && (y != 2)))
    {
        cout << "Illegal move" << endl;
    }
    else if(spotFilled(x, y) == 0)
    {
        board[x][y] = 'x';
    }
    else if(spotFilled(x, y) == 1)
    {
        cout << "Illegal move" << endl;
    }
}

void tictac::aiplacePiece()
{
    generateTree(comp);
}

int tictac::generateTree(char turn)
{
    int holdx;
    int holdy;

    if(isWin() == 1)
    {
        //display();
        //cout << "**************" << endl;
        return '10';
    }
    else if(isWin() == 2)
    {
        //display();
        //cout << "**************" << endl;
        return '-10';
    }
    else if((isWin() == 0) && (isFull() == 1))
    {
        //display();
        //cout << "**************" << endl;
        return '0';
    }

    for(x=0; x<3; x++)
    {
        for(y=0; y<3; y++)
        {
            if(board[x][y] == '_')
            {
                board[x][y] = turn;
                if(turn == 'x')
                {
                    turn = 'o';
                }
                else
                {
                    turn = 'x';
                }

                holdx = x;
                holdy = y;

                generateTree(turn);

                x = holdx;
                y = holdy;

                board[x][y] = '_';

                if(turn == 'x')
                {
                    turn = 'o';
                }
                else
                {
                    turn = 'x';
                }
            }
        }
    }
    return 0;
}

void tictac::play(char turn)
{
    if(turn == 'x')
    {
        if((isFull() == 0) && (isWin() == 0))
        {
            plplacePiece();
            return play('o');
        }
        else
        {
            return;
        }
    }
    else if(turn == 'o')
    {
        if((isFull() == 0) && (isWin() == 0))
        {
            aiplacePiece();
            return play('x');
        }
        else
        {
            return;
        }
    }
}

int main()
{
    tictac board;

    char player = 'x';
    char comp = 'o';

    board.clearBoard();
    board.display();
    board.generateTree(player);





    return 0;
}

/*
maxSearch()
return 10 if player wins
return -10 if comp wins
return 0 if tie

if spot empty
    spot = player
    score = max
    board clear
*/
