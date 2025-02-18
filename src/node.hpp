#ifndef __NODE_HPP__
#define __NODE_HPP__

#include "cube.hpp"
#include "distanceManager.hpp"
#include <memory>
#include <array>
#include <string>

// struct TNode;
struct TNode {
public:
    TNode();
    TNode(const CCube& cube);
    // int CalculateCost(const std::vector<uint8_t>& goalPanels) const;
    float CalculateHeuristic(const std::vector<uint8_t>& getGoalPanels) const;
    // int CalculateHeuristic2(const std::vector<uint8_t>& getGoalPanels, int costPerMove) const;
    std::string GetPath() const;
    bool AchievedGoal(const std::vector<uint8_t>& goalPanels) const;
    bool isInPath(const TNode& other) const;
    bool operator==(const TNode& other) const;
private:
    int CalculateDistance(uint8_t id1, uint8_t id2) const;
public:
    CCube m_Cube;
    int m_G = 0; // Cost value
    float m_H = 0; // Heuristic value
    float m_PVal = 0; // Priority value
    std::shared_ptr<TNode> m_Parent = nullptr;
    EMove m_Move = EMove::None;   // The previous move
    static CDistanceManager m_DistanceTable;
};
using NodeSP = std::shared_ptr<TNode>;

#endif // __NODE_HPP__
