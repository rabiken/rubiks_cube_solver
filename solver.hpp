#ifndef __SOLVER_HPP__
#define __SOLVER_HPP__

#include <string>
#include "cube.hpp"
#include "node.hpp"

class CSolver {
public:
    CSolver() = default;
    ~CSolver() = default;

    bool Solve_AStar(CCube& result, std::string& solution, const CCube& problem, 
        const CCube& goal, const std::vector<bool>& mask) const;
    // bool Solve_IDAStar(CCube& result, std::string& solution, const CCube& problem, 
    //     const CCube& goal, const std::vector<bool>& mask) const;
private:
    // bool Search_IDAStar
    //     ( CCube& result, std::string& solution, const NodeSP& current, 
    //       const std::vector<uint8_t>& goalPanels, 
    //       int threshold, int& nextThreshold, 
    //       int costPerMove ) const;
};

#endif // __SOLVER_HPP__
