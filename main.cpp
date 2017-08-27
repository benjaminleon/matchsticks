#include "brain.hpp"
using std::cout;
using std::endl;
using std::cin;

int main()
{
    std::vector<int> state = {0, 0, 0};
    cout << "Enter amount of sticks in a pile: ";  cin >> state[0];
    cout << "Enter amount of sticks in another pile: "; cin >> state[1];
    cout << "Enter amount of sticks in anotherother pile: ";  cin >> state[2];

    Brain brain;

    if (brain.findWinningMove(state) == WIN)
    {
        std::string ordinal = "";
        switch (brain._pile)
        {
            case 0: ordinal = "first"; break;
            case 1: ordinal = "second"; break;
            case 2: ordinal = "third"; break;
            default: ordinal = "non-existing"; break;
        }

        cout << "You're gonna win. Take " << brain._sticks <<
        " stick" << (brain._sticks > 1 ? "s" : "") <<  " from the " << ordinal << " pile" << endl;
    }
    else
    {
        cout << "You might lose this one" << endl;
    }
}
