#ifdef BRAIN_HPP
#else

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

enum Prediction
{
    LOSE,
    WIN,
    DUNNO
};

class Brain
{
public:
    Brain();
    enum Prediction findWinningMove(std::vector<int> state);
    enum Prediction checkNote(std::vector<int> state);
    int _sticks;
    int _pile;
private:
    std::map<std::vector<int>, enum Prediction> notes;
    std::vector<int> state;
};

#endif