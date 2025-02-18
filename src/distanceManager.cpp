#include "distanceManager.hpp"
#include "cube.hpp"
#include <queue>
#include <memory>
#include <set>

CDistanceManager::CDistanceManager()
{
    m_Data.resize(48*48);
    for ( int i = 0; i < 48; i ++ ) {
        for ( int j = 0; j < 48; j++ ) {
            m_Data[i*48+j] = CalculateDistance_BFS(i,j);
        }
    }
}

int CDistanceManager::operator()(uint8_t id1, uint8_t id2) const
{
    return m_Data[id1*48+id2];
}

class CubeComparator {
public:
    bool operator()(const CCube& lhs, const CCube& rhs) const {
        return lhs.ToString() < rhs.ToString();
    }
};

int CDistanceManager::CalculateDistance_BFS(uint8_t id1, uint8_t id2)
{
    if ( id1%2 != id2%2 ) {
        return -1;
    }
    using CubeSP = std::shared_ptr<CCube>;
    CubeSP cube = std::make_shared<CCube>();
    using node_t = std::pair<CubeSP,int>;
    std::queue<node_t> q;
    std::set<CCube, CubeComparator> visited;
    q.push({cube,0});
    while ( ! q.empty() ) {
        node_t current = q.front();
        visited.insert(*current.first);
        q.pop();
        if ( current.second >= 5 ) {
            printf("id1: %d, id2: %d\n", id1, id2);
            return -1;
        }
        if ( current.first->GetID(id1) == id2 ) {
            // Found the solution
            return current.second;
        }
        for ( int i = 0; i < 12; i ++ ) {
            CubeSP next (new CCube(*current.first));
            next->Move(static_cast<EMove>(i));
            if ( current.first->GetPos(id2) != next->GetPos(id2)
                && visited.count(*next) == 0 ) 
            {
                q.push({next, current.second+1});
            }
        }

    }
    return -1;
}