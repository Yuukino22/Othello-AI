#ifndef MYOTHELLOAI_HPP
#define MYOTHELLOAI_HPP
#include "OthelloAI.hpp"
#include <vector>


namespace yifengx4
{
    class MyOthelloAI : public OthelloAI
    {
    public:
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;

        //return a vector of all valid move
        std::vector<std::pair<int, int>> allValidMove(std::unique_ptr<OthelloGameState>& s);

        //return the point of every potential state
        int evaluation(std::unique_ptr<OthelloGameState>& s, bool bOrw);

        int search(std::unique_ptr<OthelloGameState>& s, int depth, bool bOrw);
    };

    
}

#endif