#include <ics46/factory/DynamicFactory.hpp>
#include "JabodeyAI.hpp"
#include <iostream>
using namespace std;

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, nguyenk8::JabodeyAI, "JabodeyAI (Required)");

pair<int, int> nguyenk8::JabodeyAI::chooseMove(const OthelloGameState& state)
{
int turn;
if (state.isBlackTurn())
    turn = 1;
else
    turn = 0;

int score;
int best_score = -9000;

pair<int, int> best_move;

vector<pair<int, int>> available_moves;
for (int x = 0; x < state.board().width(); ++x)
    for (int y = 0; y < state.board().height(); ++y)
        if (state.isValidMove(x,y))
            {
            available_moves.push_back(pair<int, int> (x, y));
            }

for(auto move = available_moves.begin(); move != available_moves.end(); ++move)
{
std::unique_ptr<OthelloGameState> copy = state.clone();
copy -> makeMove(move->first, move->second);
score = search(*copy, 3, turn);
if (score >= best_score)
    {
    best_move.first = move->first;
    best_move.second = move->second;
    }

}
return best_move;

}

int nguyenk8::JabodeyAI::search(const OthelloGameState& state, int depth, int turn)
{
int score;
if (depth == 0)
    return eval(state, turn);

else
    if ((turn == 1 && state.isBlackTurn()) || (turn == 0 && state.isWhiteTurn()))
        {
        int max = -9000;
        for(int x = 0; x < state.board().width(); ++x)
            for(int y = 0; y < state.board().height(); ++y)
                if(state.isValidMove(x,y))
                    {
                    unique_ptr<OthelloGameState> copy = state.clone();
                    copy -> makeMove(x,y);
                    score = search(*copy, depth - 1, turn);
                    }
        if (score > max)
            {
            return score;
            }
        return max;
        }

    else
        {
        int min = 9000;
        for(int x = 0; x < state.board().width(); ++x)
            for(int y = 0; y < state.board().height(); ++y)
                if(state.isValidMove(x,y))
                    {
                    unique_ptr<OthelloGameState> copy = state.clone();
                    copy -> makeMove(x,y);
                    score = search(*copy, depth - 1, turn);
                    }
        if (score < min)
            {
            return score;
            }
        return min;
        }
}


int nguyenk8::JabodeyAI::eval(const OthelloGameState& state, int turn)
{
if (turn == 1 && state.isBlackTurn())
    return state.blackScore() - state.whiteScore();
else
    return state.whiteScore() - state.blackScore();
}
