#ifndef __DISTANCE_MANAGER_HPP__
#define __DISTANCE_MANAGER_HPP__

#include <cstdint>
#include <vector>

class CDistanceManager {
public:
    CDistanceManager();
    int operator()(uint8_t id1, uint8_t id2) const;
private:
    int CalculateDistance_BFS(uint8_t id1, uint8_t id2);
private:
    std::vector<uint8_t> m_Data;
};

#endif // __DISTANCE_MANAGER_HPP__
