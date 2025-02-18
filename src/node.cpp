#include "node.hpp"
#include <stdexcept>

TNode::TNode()
{
}
TNode::TNode(const CCube& cube)
: m_Cube(cube)
{
}
float TNode::CalculateHeuristic(const std::vector<uint8_t>& goalPanels) const
{
    int bestH_Sum = 0;      // Best Heuristic Sum(Too Good)
    // int correctFS_Cnt = 0;   // Correct Face Score Counter(#block*6)
    // int wrongFS_Cnt = 0;     // Wrong Face Score Counter(#block*6)
    for (int i = 0; i < 48; i ++ ) {
        if (goalPanels[i] != 0xff ) {
            int dist = CalculateDistance(i, m_Cube.GetPos(goalPanels[i]));
            // if ( dist == 0 ) {
            //     if ( i%2 == 0 ) {
            //         // correctFS_Cnt += 2;
            //     }
            //     else {
            //         // correctFS_Cnt += 3;
            //     }
            // }
            // else {
                if ( i%2 == 0 ) {
                    bestH_Sum += dist*2;
                }
                else {
                    bestH_Sum += dist*3;
                }
            // }
        }
    }
    // const float correctBlocks = correctFS_Cnt/6.0;
    // const float wrongBlocks = wrongFS_Cnt/6.0;
    // if ( correctBlocks/(correctBlocks+wrongBlocks) > 0.95) {
    //     printf("more than 95%% of correctness: %f%%\n", correctBlocks/(correctBlocks+wrongBlocks)*100);
    // }
    const float h1 = bestH_Sum/6.0;
    // How much does the future move bother the correct blocks
    // const float botheringDegree = 1.0 - std::pow(2.0/3.0, h1);
    // return h1;//+botheringDegree*correctBlocks;
    return h1;
    // return h1*(1+correctBlocks/24);
    // return h1;//*(1+correctBlocks/24/2);
    // return h1*(1/(correctBlocks+wrongBlocks)+botheringDegree);
    // return h1 * (correctBlocks + wrongBlocks * botheringDegree) / (correctBlocks + wrongBlocks);
}
// int TNode::CalculateHeuristic2(const std::vector<uint8_t>& goalPanels, int costPerMove) const
// {
//     int h_min = this->CalculateHeuristic(goalPanels);
//     for ( int i = 0; i < 12; i ++ ) {
//         TNode node(m_Cube);
//         node.m_Move = static_cast<EMove>(i);
//         node.m_Cube.Move(node.m_Move);
//         int h = costPerMove + node.CalculateHeuristic(goalPanels);
//         if ( h < h_min ) {
//             h_min = h;
//         }
//     }
//     return h_min;
// }

std::string TNode::GetPath() const
{
    std::string path;
    NodeSP current = std::make_shared<TNode>(*this);
    while (current->m_Parent) {
        path = ToString(current->m_Move) + path;
        current = current->m_Parent;
    }
    return path;
}
bool TNode::AchievedGoal(const std::vector<uint8_t>& goalPanels) const
{
    for (int i = 0; i < 48; i ++ ) {
        if ( goalPanels[i] > 47 ) {
            continue;
        }
        if (m_Cube.GetID(i) != goalPanels[i]) {
            return false;
        }
    }
    return true;
}
bool TNode::isInPath(const TNode& other) const
{
    if ( this->m_Cube == other.m_Cube ) {
        return true;
    }
    return m_Parent && m_Parent->isInPath(other);
}
bool TNode::operator==(const TNode& other) const
{
    return m_Cube == other.m_Cube;
}

CDistanceManager TNode::m_DistanceTable = CDistanceManager();

int TNode::CalculateDistance(uint8_t id1, uint8_t id2) const
{
    if( id1 > 47 || id2 > 47 ) {
        throw std::out_of_range("Invalid id");
        return -1;
    }
    return m_DistanceTable(id1, id2);
}