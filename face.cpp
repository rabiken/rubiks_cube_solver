#include "face.hpp"
#include <iostream>
// public:
// Constructors
CFace::CFace(int color)
{
    for (int i = 0; i < 8; i ++ ) {
        m_IDs[i] = color*8 + i;
    }
}
CFace::CFace(const std::vector<uint8_t>& colors)
{
    for (int i = 0; i < 8; i ++ ) {
        m_IDs[i] = colors[i];
    }
}
// Copy Constructor
CFace::CFace(const CFace& other)
{
    for (int i = 0; i < 8; i ++ ) {
        m_IDs[i] = other.m_IDs[i];
    }
}
// Operators
void CFace::operator=(const CFace& other)
{
    for (int i = 0; i < 8; i ++ ) {
        m_IDs[i] = other.m_IDs[i];
    }
}

// Methods
void CFace::Rotate(bool clockwise)
{
    if ( clockwise ) {
        uint8_t tmp1, tmp2 = m_IDs[0];
        for (int i = 0; i < 4; i ++ ) {
            tmp1 = tmp2;
            tmp2 = m_IDs[((i+1)*2)%8];
            m_IDs[((i+1)*2)%8] = tmp1;
        }
        tmp2 = m_IDs[1];
        for ( int i = 0; i < 4; i ++ ) {
            tmp1 = tmp2;
            tmp2 = m_IDs[(((i+1)*2+1)%8)];
            m_IDs[(((i+1)*2+1)%8)] = tmp1;
        }
    }
    else {
        uint8_t tmp1, tmp2 = m_IDs[0];
        for (int i = 0; i < 4; i ++ ) {
            tmp1 = tmp2;
            tmp2 = m_IDs[((8-(i+1)*2)%8)];
            m_IDs[((8-(i+1)*2)%8)] = tmp1;
        }
        tmp2 = m_IDs[1];
        for ( int i = 0; i < 4; i ++ ) {
            tmp1 = tmp2;
            tmp2 = m_IDs[7-2*i];
            m_IDs[7-2*i] = tmp1;
        }
    }
}
void CFace::Set_U(const uint8_t data[3], bool clockwise)
{
    int base = 0;
    if ( clockwise ) {
        for (int i = 0; i < 3; i ++ ) {
            m_IDs[(base + i)%8] = data[i];
        }
    } else {
        for ( int i = 0; i < 3; i ++ ) {
            m_IDs[(base+i)%8] = data[2-i];
        }
    }
}
void CFace::Set_D(const uint8_t data[3], bool clockwise)
{
    const int base = 4;
    if ( clockwise ) {
        for (int i = 0; i < 3; i ++ ) {
            m_IDs[(base + i)%8] = data[i];
        }
    } else {
        for ( int i = 0; i < 3; i ++ ) {
            m_IDs[(base + 2 - i)%8] = data[i];
        }
    }
}
void CFace::Set_R(const uint8_t data[3], bool clockwise)
{
    const int base = 2;
    if ( clockwise ) {
        for (int i = 0; i < 3; i ++ ) {
            m_IDs[(base + i)%8] = data[i];
        }
    } else {
        for ( int i = 0; i < 3; i ++ ) {
            m_IDs[(base + 2 - i)%8] = data[i];
        }
    }
}
void CFace::Set_L(const uint8_t data[3], bool clockwise)
{
    const int base = 6;
    if ( clockwise ) {
        for (int i = 0; i < 3; i ++ ) {
            m_IDs[(base + i)%8] = data[i];
        }
    } else {
        for ( int i = 0; i < 3; i ++ ) {
            m_IDs[(base + 2 - i)%8] = data[i];
        }
    }
}

void CFace::Get_U(uint8_t data[3], bool clockwise)
{
    const int base = 0;
    if ( clockwise ) {
        for (int i = 0; i < 3; i ++ ) {
            data[i] = m_IDs[(base + i)%8];
        }
    } else {
        for ( int i = 0; i < 3; i ++ ) {
            data[2 - i] = m_IDs[(base + 2-i)%8];
        }
    }
}
void CFace::Get_D(uint8_t data[3], bool clockwise)
{
    const int base = 4;
    if ( clockwise ) {
        for (int i = 0; i < 3; i ++ ) {
            data[i] = m_IDs[(base + i)%8];
        }
    } else {
        for ( int i = 0; i < 3; i ++ ) {
            data[2 - i] = m_IDs[(base + 2-i)%8];
        }
    }
}
void CFace::Get_R(uint8_t data[3], bool clockwise)
{
    const int base = 2;
    if ( clockwise ) {
        for (int i = 0; i < 3; i ++ ) {
            data[i] = m_IDs[(base + i)%8];
        }
    } else {
        for ( int i = 0; i < 3; i ++ ) {
            data[2 - i] = m_IDs[(base + 2 - i)%8];
        }
    }
}
void CFace::Get_L(uint8_t data[3], bool clockwise)
{
    const int base = 6;
    if ( clockwise ) {
        for (int i = 0; i < 3; i ++ ) {
            data[i] = m_IDs[(base + i)%8];
        }
    } else {
        for ( int i = 0; i < 3; i ++ ) {
            data[2 - i] = m_IDs[(base + 2 - i)%8];
        }
    }
}

void CFace::Print_Stripe(int stripe, int space, uint8_t center) const
{
    if ( stripe < 0 || stripe > 2 ) {
        throw std::out_of_range("Index out of range");
        return;
    }
    for ( int i = 0; i < space; i ++ ) {
        std::cout << "   ";
    }
    if ( stripe == 0 ) {
        for ( int i = 0; i < 3; i ++ ) {
            std::cout << "[" << (int)m_IDs[i]/8 << "]";
        }
    }
    else if ( stripe == 1 ) {
        std::cout << "[" << (int)m_IDs[7]/8 << "]";
        std::cout << "[" << (int)center << "]";
        std::cout << "[" << (int)m_IDs[3]/8 << "]";
    }
    else {
        for ( int i = 0; i < 3; i ++ ) {
            std::cout << "[" << (int)m_IDs[6 - i]/8 << "]";
        }
    }
}

void CFace::Print(int center) const
{
    for ( int i = 0; i < 3; i ++ ) {
        Print_Stripe(i, 0, center);
        std::cout << std::endl;
    }
}

uint8_t CFace::GetID(int index) const
{
    if ( index < 0 || index > 7 ) {
        throw std::out_of_range("Index out of range");
        return 0xff;
    }
    return m_IDs[index];
}
uint8_t& CFace::GetID(int index)
{
    if ( index < 0 || index > 7 ) {
        throw std::out_of_range("Index out of range");
        return m_IDs[0];
    }
    return m_IDs[index];
}
std::string CFace::ToString() const
{
    std::string str;
    for ( int i = 0; i < 8; i ++ ) {
        str += std::to_string(m_IDs[i]);
    }
    return str;
}
bool CFace::operator==(const CFace& other) const
{
    for ( int i = 0; i < 8; i ++ ) {
        if ( m_IDs[i] != other.m_IDs[i] ) {
            return false;
        }
    }
    return true;
}
bool CFace::operator!= (const CFace& other) const
{
    return !(*this == other);
}
