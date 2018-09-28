#include "OthelloAI.hpp"
using namespace std;

namespace nguyenk8
{
    class JabodeyAI: public OthelloAI
    {
    public: 
        virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
        virtual int search(const OthelloGameState& state, int depth, int turn);
        virtual int eval(const OthelloGameState& state, int turn);
    };
}
