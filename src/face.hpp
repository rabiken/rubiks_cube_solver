#ifndef __FACE_HPP__
#define __FACE_HPP__

#include <cstdint>
#include <vector>
#include <string>

class CFace {
public:
    CFace(int color = 0xff);
    CFace(const std::vector<uint8_t>& colors);
    // Copy Constructor
    CFace(const CFace& other);
    void operator=(const CFace& other);

    void Rotate(bool clockwise);
    void Set_U(const uint8_t data[3], bool clockwise);
    void Set_D(const uint8_t data[3], bool clockwise);
    void Set_R(const uint8_t data[3], bool clockwise);
    void Set_L(const uint8_t data[3], bool clockwise);

    void Get_U(uint8_t data[3], bool clockwise);
    void Get_D(uint8_t data[3], bool clockwise);
    void Get_R(uint8_t data[3], bool clockwise);
    void Get_L(uint8_t data[3], bool clockwise);

    uint8_t GetID(int index) const;
    uint8_t& GetID(int index);

    void Print(int center) const;
    void Print_Stripe(int stripe, int space, uint8_t center) const;
    std::string ToString() const;

    bool operator== (const CFace& other) const;
    bool operator!= (const CFace& other) const;
    // Members
    uint8_t m_IDs[8] = {0xff};
};

#endif  // __FACE_HPP__