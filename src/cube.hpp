#ifndef __CUBE_HPP__
#define __CUBE_HPP__

#include <vector>
#include <string>
#include "face.hpp"

enum class EMove {
    U, D, R, L, F, B,
    U_Anti, D_Anti, R_Anti, L_Anti, F_Anti, B_Anti,
    None
};
std::string ToString(EMove move);

class CCube
{
public:
    CCube();
    CCube(const CCube& other);
    void operator=(const CCube& other);
    void Move(EMove moveID);
    void Move_U();
    void Move_D();
    void Move_R();
    void Move_L();
    void Move_F();
    void Move_B();
    
    void Move_U_2();
    void Move_D_2();
    void Move_R_2();
    void Move_L_2();
    void Move_F_2();
    void Move_B_2();
    
    void Move_U_Anti();
    void Move_D_Anti();
    void Move_R_Anti();
    void Move_L_Anti();
    void Move_F_Anti();
    void Move_B_Anti();

    std::string shaffle(int shaffleCnt);
    void print2D();

    const CFace& GetFace(int face) const;
    CFace& GetFace(int face);
    int GetID(int pos) const;
    int GetPos(int id) const;
    std::string ToString() const;
    bool operator== (const CCube& other) const;
    bool operator!= (const CCube& other) const;
private:
    void Rotate_Type1(int f0, int f1, int f2, int f3, int f4, bool clockwise = true);
    void Rotate_Type2(int f0, int f1, int f2, int f3, int f4, bool clockwise = true);
private: // Members
    CFace m_Faces[6];
};

#endif // __CUBE_HPP__