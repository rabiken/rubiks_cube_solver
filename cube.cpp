#include "cube.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

std::string ToString(EMove moveID)
{
    switch(moveID) {
    case EMove::U:
        return "U";
    case EMove::D:
        return "D";
    case EMove::R:
        return "R";
    case EMove::L:
        return "L";
    case EMove::F:
        return "F";
    case EMove::B:
        return "B";
    case EMove::U_Anti:
        return "U'";
    case EMove::D_Anti:
        return "D'";
    case EMove::R_Anti:
        return "R'";
    case EMove::L_Anti:
        return "L'";
    case EMove::F_Anti:
        return "F'";
    case EMove::B_Anti:
        return "B'";
    default:
        return "";
    }
}

CCube::CCube()
{
    for (int i = 0; i < 6; i ++ ) {
        m_Faces[i] = CFace(i);
    }
}
CCube::CCube(const CCube& other)
{
    for (int i = 0; i < 6; i ++ ) {
        m_Faces[i] = other.m_Faces[i];
    }
}
void CCube::operator=(const CCube& other)
{
    for (int i = 0; i < 6; i ++ ) {
        m_Faces[i] = other.m_Faces[i];
    }
}

void CCube::Move(EMove moveID) {
    switch(moveID) {
    case EMove::U:
        Move_U(); break;
    case EMove::D:
        Move_D(); break;
    case EMove::R:
        Move_R(); break;
    case EMove::L:
        Move_L(); break;
    case EMove::F:
        Move_F(); break;
    case EMove::B:
        Move_B(); break;
    case EMove::U_Anti:
        Move_U_Anti(); break;
    case EMove::D_Anti:
        Move_D_Anti(); break;
    case EMove::R_Anti:
        Move_R_Anti(); break;
    case EMove::L_Anti:
        Move_L_Anti(); break;
    case EMove::F_Anti:
        Move_F_Anti(); break;
    case EMove::B_Anti:
        Move_B_Anti(); break;

    default:  break;
    }
}
void CCube::Move_U()
{
    Rotate_Type1(0,3,1,2,4, true);
}
void CCube::Move_D()
{
    Rotate_Type2(5,2,1,3,4, true);
}
void CCube::Move_R()
{
    Rotate_Type1(1,5,2,0,3, true);
}
void CCube::Move_L()
{
    Rotate_Type2(4,0,2,5,3, true);
}
void CCube::Move_F()
{
    Rotate_Type1(2,4,0,1,5, true);
}
void CCube::Move_B()
{
    Rotate_Type2(3,1,0,4,5, true);
}
    
void CCube::Move_U_2()
{
    Move_U();
    Move_U();
}
void CCube::Move_D_2()
{
    Move_D();
    Move_D();
}
void CCube::Move_R_2()
{
    Move_R();
    Move_R();
}
void CCube::Move_L_2()
{
    Move_L();
    Move_L();
}
void CCube::Move_F_2()
{
    Move_F();
    Move_F();
}
void CCube::Move_B_2()
{
    Move_B();
    Move_B();
}
    
void CCube::Move_U_Anti()
{
    Rotate_Type1(0,3,1,2,4, false);
}
void CCube::Move_D_Anti()
{
    Rotate_Type2(5,2,1,3,4, false);
}
void CCube::Move_R_Anti()
{
    Rotate_Type1(1,5,2,0,3, false);
}
void CCube::Move_L_Anti()
{
    Rotate_Type2(4,0,2,5,3, false);
}
void CCube::Move_F_Anti()
{
    Rotate_Type1(2,4,0,1,5, false);
}
void CCube::Move_B_Anti()
{
    Rotate_Type2(3,1,0,4,5, false);
}

std::string CCube::shaffle(int shaffleCnt)
{
    std::string moves = "";
    int prev_number = -1;
    for (int i = 0; i < shaffleCnt; i ++ ) {
        int r;
        do {
            r = rand() % 6;
        } while (r == prev_number);
        prev_number = r;
        int r2 = rand() % 3;
        switch(r) {
        case 0:
            switch(r2) {
            case 0:
                Move_U();
                moves += "U";
                break;
            case 1:
                Move_U_2();
                moves += "UU";
                break;
            case 2:
                Move_U_Anti();
                moves += "U'";
                break;
            }
            break;
        case 1:
            switch(r2) {
            case 0:
                Move_D();
                moves += "D";
                break;
            case 1:
                Move_D_2();
                moves += "DD";
                break;
            case 2:
                Move_D_Anti();
                moves += "D'";
                break;
            }
            break;
        case 2:
            switch(r2) {
            case 0:
                Move_R();
                moves += "R";
                break;
            case 1:
                Move_R_2();
                moves += "RR";
                break;
            case 2:
                Move_R_Anti();
                moves += "R'";
                break;
            }
            break;
        case 3:
            switch(r2) {
            case 0:
                Move_L();
                moves += "L";
                break;
            case 1:
                Move_L_2();
                moves += "LL";
                break;
            case 2:
                Move_L_Anti();
                moves += "L'";
                break;
            }
            break;
        case 4:
            switch(r2) {
            case 0:
                Move_F();
                moves += "F";
                break;
            case 1:
                Move_F_2();
                moves += "FF";
                break;
            case 2:
                Move_F_Anti();
                moves += "F'";
                break;
            }
            break;
        case 5:
            switch(r2) {
            case 0:
                Move_B();
                moves += "B";
                break;
            case 1:
                Move_B_2();
                moves += "BB";
                break;
            case 2:
                Move_B_Anti();
                moves += "B'";
                break;
            }
            break;
        }
    }
    return moves;
}
/**
 * @brief Print 2D representation of the cube
 * Mapping of the faces is as follows:
 *    [3]
 * [4][0][1][5]
 *    [2]
 * Direction of the face is as follows:
 *    [>]
 * [>][^][>][v]
 *    [<]
 * 
 */
void CCube::print2D()
{
    CFace faces[6];
    for (int i = 0; i < 6; i ++ ) {
        faces[i] = m_Faces[i];
    }
    faces[3].Rotate(true);
    faces[4].Rotate(true);
    faces[1].Rotate(true);
    faces[5].Rotate(true);
    faces[5].Rotate(true);
    faces[2].Rotate(false);

    for (int i = 0; i < 3; i ++ ) {
        faces[3].Print_Stripe(i, 3, 3);
        std::cout << std::endl;
    }
    for ( int i = 0; i < 3; i ++ ) {
        faces[4].Print_Stripe(i, 0, 4);
        faces[0].Print_Stripe(i, 0, 0);
        faces[1].Print_Stripe(i, 0, 1);
        faces[5].Print_Stripe(i, 0, 5);
        std::cout << std::endl;
    }
    for ( int i = 0; i < 3; i ++ ) {
        faces[2].Print_Stripe(i, 3, 2);
        std::cout << std::endl;
    }
}

void CCube::Rotate_Type1(int f0, int f1, int f2, int f3, int f4, bool clockwise)
{
    if ( clockwise ) {
        m_Faces[f0].Rotate(true);
        uint8_t tmp1[3];
        uint8_t tmp2[3];
        m_Faces[f1].Get_R(tmp1, true);
        m_Faces[f2].Get_D(tmp2, true);
        m_Faces[f2].Set_D(tmp1, true);
        std::swap(tmp1, tmp2);

        m_Faces[f3].Get_R(tmp2, true);
        m_Faces[f3].Set_R(tmp1, true);
        std::swap(tmp1, tmp2);

        m_Faces[f4].Get_U(tmp2, true);
        m_Faces[f4].Set_U(tmp1, true);
        std::swap(tmp1, tmp2);

        m_Faces[f1].Set_R(tmp1, true);
    }
    else {
        m_Faces[f0].Rotate(false);
        uint8_t tmp1[3];
        uint8_t tmp2[3];
        m_Faces[f1].Get_R(tmp1, true);
        m_Faces[f4].Get_U(tmp2, true);
        m_Faces[f4].Set_U(tmp1, true);
        std::swap(tmp1, tmp2);

        m_Faces[f3].Get_R(tmp2, true);
        m_Faces[f3].Set_R(tmp1, true);
        std::swap(tmp1, tmp2);

        m_Faces[f2].Get_D(tmp2, true);
        m_Faces[f2].Set_D(tmp1, true);
        std::swap(tmp1, tmp2);

        m_Faces[f1].Set_R(tmp1, true);
    
    }
}
void CCube::Rotate_Type2(int f0, int f1, int f2, int f3, int f4, bool clockwise)
{
    if ( clockwise ) {
        m_Faces[f0].Rotate(true);
        uint8_t tmp1[3];
        uint8_t tmp2[3];
        m_Faces[f1].Get_L(tmp1, true);
        m_Faces[f2].Get_U(tmp2, true);
        m_Faces[f2].Set_U(tmp1, true);
        std::swap(tmp1, tmp2);

        m_Faces[f3].Get_L(tmp2, true);
        m_Faces[f3].Set_L(tmp1, true);
        std::swap(tmp1, tmp2);

        m_Faces[f4].Get_D(tmp2, true);
        m_Faces[f4].Set_D(tmp1, true);
        std::swap(tmp1, tmp2);

        m_Faces[f1].Set_L(tmp1, true);
    }
    else {
        m_Faces[f0].Rotate(false);
        uint8_t tmp1[3];
        uint8_t tmp2[3];
        m_Faces[f1].Get_L(tmp1, true);
        m_Faces[f4].Get_D(tmp2, true);
        m_Faces[f4].Set_D(tmp1, true);
        std::swap(tmp1, tmp2);

        m_Faces[f3].Get_L(tmp2, true);
        m_Faces[f3].Set_L(tmp1, true);
        std::swap(tmp1, tmp2);

        m_Faces[f2].Get_U(tmp2, true);
        m_Faces[f2].Set_U(tmp1, true);
        std::swap(tmp1, tmp2);

        m_Faces[f1].Set_L(tmp1, true);
    }
}

const CFace& CCube::GetFace(int face) const
{
    return m_Faces[face];
}
CFace& CCube::GetFace(int face)
{
    if ( face < 0 || face >= 6 ) {
        throw std::out_of_range("Invalid face"); 
    }
    return m_Faces[face];
}
int CCube::GetID(int pos) const
{
    if ( pos < 0 || pos >= 48 ) {
        throw std::out_of_range("Invalid position");
    }
    return m_Faces[pos/8].GetID(pos%8);
}
int CCube::GetPos(int id) const {
    if ( id < 0 || id >= 48 ) {
        throw std::out_of_range("Invalid id");
    }
    for (int i = 0; i < 6; i ++ ) {
        for ( int j = 0; j < 8; j ++ ) {
            if ( m_Faces[i].GetID(j) == id ) {
                return i*8 + j;
            }
        }
    }
    return -1;
}
std::string CCube::ToString() const
{
    std::string str;
    for (int i = 0; i < 6; i ++ ) {
        str += m_Faces[i].ToString();
    }
    return str;
}
bool CCube::operator== (const CCube& other) const
{
    for (int i = 0; i < 6; i ++ ) {
        if ( m_Faces[i] != other.m_Faces[i] ) {
            return false;
        }
    }
    return true;
}
bool CCube::operator!= (const CCube& other) const
{
    return !(*this == other);
}