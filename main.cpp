#include <iostream>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::cin;

#define DEBUG 0

#if DEBUG == 1
    #define debugOutput(x) cout << x
#else
    #define debugOutput(x)
#endif


enum Prediction
{
    LOSE,
    WIN
};

int depth = 0; // For string formatting of debug printouts

enum Prediction findWinningMove(std::vector<int> state, int & sticks, int & pile);
bool losingState(std::vector<int> myState);
bool tookLast(std::vector<int> myState);

int main()
{

Prediction prediction;

std::vector<int> myState;
myState.push_back(0);
myState.push_back(0);
myState.push_back(0);
int number = -1;

cout << "Enter amount of sticks in the first  pile: "; cin >> myState[0];
cout << "Enter amount of sticks in the second pile: "; cin >> myState[1];
cout << "Enter amount of sticks in the third  pile: "; cin >> myState[2];

int sticks = 0;
int pile = -1;

prediction = findWinningMove(myState, sticks, pile);

if (prediction == WIN)
{
    cout << "You're gonna win. Take " << sticks << " stick" << (sticks > 1 ? "s" : "")
    << " from pile " << pile << endl;
}
else
{
    cout << "You might lose this one. Just take a random stick and try to psyche your opponent" << endl;
}
}

enum Prediction findWinningMove(std::vector<int> myState, int & sticks, int & pile)
{
    debugOutput(std::string(depth, ' ') << "let's examine " << myState[0] << " " <<
        myState[1] << " "  << myState[2] << endl);

    if (losingState(myState))
    {
        debugOutput(std::string(depth, ' ') << "losing state reached: " << myState[0] << " " <<
            myState[1] << " "  << myState[2] << endl);
        return LOSE;
    }

    for (int i = 0; i < 3; i++) //all piles
    {
        for (int j = myState[i]; j > 0; j--) // try first to take a large amount of sticks. Depth first.
        {
            debugOutput(std::string(depth, ' ') << "taking " << j << " sticks from pile " << i << endl);
            myState[i] -= j;
            if (tookLast(myState))
            {
                debugOutput(std::string(depth, ' ') << "took too many, let's try again" << endl);
                myState[i] += j; // comon, at least leave a few
                continue;
            }

            depth += 10;
            if (findWinningMove(myState, sticks, pile) == LOSE)
            {
                pile = i;
                sticks = j;
                debugOutput(std::string(depth, ' ') << "Put your opponent in: " << myState[0] <<
                    " " << myState[1] << " "  << myState[2] << " to win " << endl);
                depth -= 10;
                return WIN;
            }
            depth -= 10;
            myState[i] += j; // Not happy with the outcome, let's try another move
        }
    }
    // if you can't make it to the (0, 0, 1) state before your opponent you lose
    debugOutput(std::string(depth, ' ') << "did not find a good move" << endl);
    return LOSE;
}

bool losingState(std::vector<int> myState)
{
    int zeros, ones = 0;
    for (int i = 0; i < 3; i++)
    {
        if (myState[i] == 0)
        {
            zeros++;
        }
        else if (myState[i] == 1)
        {
            ones++;
        }
    }

    return (zeros == 2 && ones == 1);
}

bool tookLast(std::vector<int> myState)
{
    return std::all_of(myState.begin(), myState.end(), [](int i){return i == 0;});
}
