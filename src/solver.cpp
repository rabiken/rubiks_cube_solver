#include "solver.hpp"
#include "node.hpp"
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <memory>
#include <iostream>

using NodeSP = std::shared_ptr<TNode>;
class NodeSPGreater {
public:
    bool operator() (const NodeSP& lhs, const NodeSP& rhs) const {
        return lhs->m_PVal > rhs->m_PVal;
    }
};
using pq_t = std::priority_queue<NodeSP, std::vector<NodeSP>, NodeSPGreater>;

std::vector<uint8_t> GetGoalPanels(const CCube& goal, const std::vector<bool>& mask ) {
    std::vector<uint8_t> res(48, 0xff);
    for (int i = 0; i < 6; i ++ ) {
        for (int j = 0; j < 8; j ++ ) {
            if ( !mask[i*8+j] ){
                res[i*8+j] = 0xff;
                continue;
            }
            res[i*8+j] = goal.GetFace(i).GetID(j);
        }
    }
    return res;
}
int CalculateBlockWeight(const std::vector<bool>& mask) {
    int res = 0;
    for ( int i = 0; i < 48; i ++ ) {
        if ( !mask[i] ) {
            continue;
        }
        if ( i % 2 == 0 ) {
            res += 2;
        }
        else {
            res += 3;
        }
    }
    return res;
}
class NodeComparator {
public:
    bool operator() (const NodeSP& lhs, const NodeSP& rhs) const {
        return lhs->m_Cube.ToString() < rhs->m_Cube.ToString();
    }
};
bool CSolver::Solve_AStar(CCube& result, std::string& solution, const CCube& problem, const CCube& goal, const std::vector<bool>& mask) const
{
    pq_t openList;
    std::set<NodeSP, NodeComparator> visited;
    NodeSP start (new TNode(problem));
    std::vector<uint8_t> goalPanels = GetGoalPanels(goal, mask);
    // const int blockWeight = CalculateBlockWeight(mask);
    // const int costPerMove = (2*12+3*8) * blockWeight / (6*8*3);
    // const int blockWeight = CalculateBlockWeight(mask);
    // const float costPerMove = (2*12+3*8) * blockWeight / (6*8*3);
    const float costPerMove = 1.0;
    printf("costPerMove: %f\n", costPerMove);
    start->m_G = 0.0;
    start->m_H = start->CalculateHeuristic(goalPanels);
    start->m_PVal = start->m_H + start->m_G;
    openList.push(start);
    visited.insert(start);
    bool found = false;
    while (!openList.empty()) {
        NodeSP current = openList.top();
        // printf("current PVal: %f\n", current->m_PVal);
        openList.pop();
        if (current->AchievedGoal(goalPanels)) {
            found = true;
            std::cout << "Found the solution!" << std::endl;
            printf("Cost: %d\n", current->m_G);
            result = current->m_Cube;
            solution = current->GetPath();
            current->m_Cube.print2D();
            break;
        }
        // visited.insert(current);
        for (int i = 0; i < 12; i ++ ) {
            NodeSP next = std::make_shared<TNode>(current->m_Cube);
            next->m_Parent = current;
            next->m_Move = static_cast<EMove>(i);
            next->m_Cube.Move(static_cast<EMove>(i));
            next->m_G = current->m_G + costPerMove;// (2*12+3*8);
            // next->m_H = next->CalculateHeuristic2(goalPanels, costPerMove);
            next->m_H = next->CalculateHeuristic(goalPanels);
            next->m_PVal = next->m_G + next->m_H;
            if ( visited.count(next) == 0) {
                openList.push(next);
                visited.insert(next);
            }
        }
    }
    return found;
}

// bool CSolver::Solve_IDAStar(CCube& result, std::string& solution, const CCube& problem, const CCube& goal, const std::vector<bool>& mask) const
// {
//     // IDA* algorithm
//     int blockWeight = CalculateBlockWeight(mask);
//     const int costPerMove = (2*12+3*8) * blockWeight / (6*8*3);

//     NodeSP root (new TNode(problem));
//     std::vector<uint8_t> goalPanels = GetGoalPanels(goal, mask);
//     root->m_H = root->CalculateHeuristic(goalPanels);
//     root->m_G = 0;
//     int threshold = root->m_PVal = root->m_H + root->m_G;
//     while (true) {
//         int nextThreshold = INT_MAX;
//         bool found = Search_IDAStar(result, solution, root, goalPanels, threshold, nextThreshold, costPerMove);
//         if (found) {
//             return true;
//         }
//         if (nextThreshold == INT_MAX) {
//             return false;
//         }
//         threshold = nextThreshold;
//     }
// }

// bool CSolver::Search_IDAStar
//         ( CCube& result, std::string& solution, const NodeSP& current, 
//           const std::vector<uint8_t>& goalPanels, 
//           int threshold, int& nextThreshold,
//           int costPerMove ) const
// {
//     printf("threadhold: %d\n", threshold);
//     if (current->m_PVal > threshold) {
//         nextThreshold = std::min(nextThreshold, current->m_G + current->m_PVal);
//         return false;
//     }
//     if (current->AchievedGoal(goalPanels)) {
//         result = current->m_Cube;
//         solution = current->GetPath();
//         return true;
//     }
//     int minCost = INT_MAX;
//     for (int i = 0; i < 12; i++) {
//         NodeSP next (new TNode(current->m_Cube));
//         next->m_Parent = current;
//         next->m_Move = static_cast<EMove>(i);
//         next->m_Cube.Move(static_cast<EMove>(i));
//         next->m_G = current->m_G + costPerMove;
//         next->m_H = next->CalculateHeuristic(goalPanels);
//         if (!current->isInPath(*next)) {
//             bool found = Search_IDAStar(result, solution, next, goalPanels, threshold, nextThreshold, costPerMove);
//             if (found) {
//                 return true;
//             }
//             minCost = std::min(minCost, next->m_PVal);
//         }
//     }
//     nextThreshold = minCost;
//     return false;
// }