#include "brain.hpp"

Brain::Brain()
{
    std::vector<int> endState {0, 0, 0};
    notes.emplace(endState, WIN);
    _sticks = -1;
    _pile = -1;
}

enum Prediction Brain::findWinningMove(std::vector<int> state)
{
    Prediction lookup = checkNote(state);
    if (lookup != DUNNO)
    {
        return lookup;
    }

    for (int pileIdx = 0; pileIdx < 3; pileIdx++)
    {
        for (int sticks = state[pileIdx]; sticks > 0; sticks--)
        {
            state[pileIdx] -= sticks;
            if (findWinningMove(state) == LOSE)
            {
                notes.emplace(state, LOSE);
                _sticks = sticks;
                _pile = pileIdx;
                return WIN;
            }

            notes.emplace(state, WIN);
            state[pileIdx] += sticks; // Not happy with the outcome, let's try another move
        }
    }
    return LOSE;  // did not find a single good move
}

enum Prediction Brain::checkNote(std::vector<int> state)
{
    auto it = notes.find(state);
    if (it == notes.end())
    {
        return DUNNO;
    }
    else
    {
        return it->second;
    }
}