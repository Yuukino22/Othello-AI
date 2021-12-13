#include <ics46/factory/DynamicFactory.hpp>
#include "MyOthelloAI.hpp"
#include <vector>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, yifengx4::MyOthelloAI, "Happy Lunar New Year (Required)");


std::pair<int, int> yifengx4::MyOthelloAI::chooseMove(const OthelloGameState& state)
{
    int e = -2147483648; //the min int.
    std::pair<int, int> result;
    bool bOrw = state.isBlackTurn();
    std::unique_ptr<OthelloGameState> newCopy = state.clone();
    std::vector<std::pair<int, int>> validMove = allValidMove(newCopy);
    for (std::pair<int, int> oneMove: validMove)
    {
        std::unique_ptr<OthelloGameState> newState = state.clone();
        newState->makeMove(oneMove.first, oneMove.second);
        int eval = search(newState, 25, bOrw);
        if (eval > e)
        {
            e = eval;
            result.first = oneMove.first;
            result.second = oneMove.second;
        }
    }
    return result;
}

std::vector<std::pair<int, int>> yifengx4::MyOthelloAI::allValidMove(std::unique_ptr<OthelloGameState>& s)
{
    std::vector<std::pair<int, int>> result;
    const OthelloBoard& b = s->board();
    for (int i = 0; i < b.width(); i++)
    {
        for (int j = 0; j < b.height(); j++)
        {
            if(s->isValidMove(i, j))
            {
                result.push_back(std::make_pair(i,j));
            }
        }
    }
    return result;
}

int yifengx4::MyOthelloAI::evaluation(std::unique_ptr<OthelloGameState>& s, bool bOrw)
{
    if(bOrw)
    {
        int result =  s->blackScore() - s->whiteScore();
        const OthelloBoard& b = s->board();
        int w = b.width() - 1;
        int h = b.height() - 1;
        if (b.cellAt(0,0) == OthelloCell::black)
        {
            result += 100;
        }
        if (b.cellAt(w,0) == OthelloCell::black)
        {
            result += 100;
        }
        if (b.cellAt(0,h) == OthelloCell::black)
        {
            result += 100;
        }
        if (b.cellAt(w,h) == OthelloCell::black)
        {
            result += 100;
        }
        if (b.cellAt(0,0) == OthelloCell::white)
        {
            result -= 100;
        }
        if (b.cellAt(w,0) == OthelloCell::white)
        {
            result -= 100;
        }
        if (b.cellAt(0,h) == OthelloCell::white)
        {
            result -= 100;
        }
        if (b.cellAt(w,h) == OthelloCell::white)
        {
            result -= 100;
        }
        return result;
    }
    else
    {
        int result =  s->whiteScore() - s->blackScore();
        const OthelloBoard& b = s->board();
        int w = b.width() - 1;
        int h = b.height() - 1;
        if (b.cellAt(0,0) == OthelloCell::black)
        {
            result -= 100;
        }
        if (b.cellAt(w,0) == OthelloCell::black)
        {
            result -= 100;
        }
        if (b.cellAt(0,h) == OthelloCell::black)
        {
            result -= 100;
        }
        if (b.cellAt(w,h) == OthelloCell::black)
        {
            result -= 100;
        }
        if (b.cellAt(0,0) == OthelloCell::white)
        {
            result += 100;
        }
        if (b.cellAt(w,0) == OthelloCell::white)
        {
            result += 100;
        }
        if (b.cellAt(0,h) == OthelloCell::white)
        {
            result += 100;
        }
        if (b.cellAt(w,h) == OthelloCell::white)
        {
            result += 100;
        }
        return result;
    }
    
    return -1;
}

int yifengx4::MyOthelloAI::search(std::unique_ptr<OthelloGameState>& s, int depth, bool bOrw)
{
    int minEval = 2147483647; //the max int
    int maxEval = -2147483648;//the min int
    if (depth == 0)
    {
        return evaluation(s, bOrw);
    }
    else
    {
        if (bOrw && s->isBlackTurn())
        {
            std::vector<std::pair<int, int>> validMove = allValidMove(s);
            for (std::pair<int, int> oneMove: validMove)
            {
                std::unique_ptr<OthelloGameState> newState = s->clone();
                newState->makeMove(oneMove.first, oneMove.second);
                int eval = search(newState, depth - 1, bOrw);
                if(eval > maxEval)
                {
                    maxEval = eval;
                }
                return maxEval;
            }
        }
        else if (!bOrw && s->isWhiteTurn())
        {
            std::vector<std::pair<int, int>> validMove = allValidMove(s);
            for (std::pair<int, int> oneMove: validMove)
            {
                std::unique_ptr<OthelloGameState> newState = s->clone();
                newState->makeMove(oneMove.first, oneMove.second);
                int eval = search(newState, depth - 1, bOrw);
                if(eval > maxEval)
                {
                    maxEval = eval;
                }
                return maxEval;
            }
        }
        else
        {
            std::vector<std::pair<int, int>> validMove = allValidMove(s);
            for (std::pair<int, int> oneMove: validMove)
            {
                std::unique_ptr<OthelloGameState> newState = s->clone();
                newState->makeMove(oneMove.first, oneMove.second);
                int eval = search(newState, depth - 1, bOrw);
                if(eval < minEval)
                {
                    minEval = eval;
                }
                return minEval;
            }
        }
    }
    //If the game has end before the depth == 0, then we should return the evaluation of the current state always.
    return evaluation(s, bOrw);
}

