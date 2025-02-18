#include <iostream>
#include "cube.hpp"
#include <cassert>

int main () {
    srand(time(NULL));

    std::cout << "Test for CFace" << std::endl;
    CFace face = std::vector<uint8_t>{0, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8};
    CFace faceRef = face;

    face.Print(8);
    std::cout << "Rotate clockwise" << std::endl;
    face.Rotate(true);
    face.Print(8);
    std::cout << "Rotate anti-clockwise" << std::endl;
    face.Rotate(false);
    face.Print(8);
    assert(face == faceRef);
    uint8_t input[3] = {0, 8, 16};
    std::cout << "Set_U(clockwise)" << std::endl;
    face.Set_U(input, true);
    face.Print(8);
    std::cout << "Set_U(anti-clockwise)" << std::endl;
    face.Set_U(input, false);
    face.Print(8);
    std::cout << "Set_D(clockwise)" << std::endl;
    face.Set_D(input, true);
    face.Print(8);
    std::cout << "Set_D(anti-clockwise)" << std::endl;
    face.Set_D(input, false);
    face.Print(8);
    std::cout << "Set_R(clockwise)" << std::endl;
    face.Set_R(input, true);
    face.Print(8);
    std::cout << "Set_R(anti-clockwise)" << std::endl;
    face.Set_R(input, false);
    face.Print(8);
    std::cout << "Set_L(clockwise)" << std::endl;
    face.Set_L(input, true);
    face.Print(8);
    std::cout << "Set_L(anti-clockwise)" << std::endl;
    face.Set_L(input, false);
    face.Print(8);

    CCube cube;
    std::cout << "Print after the construction of the cube\n" << std::endl;
    cube.print2D();

    cube.shaffle(100);
    std::cout << "Print after shaffling the cube\n" << std::endl;
    cube.print2D();

    CCube cube_U;
    std::cout << "Move_U" << std::endl;
    cube_U.Move_U();
    cube_U.print2D();

    CCube cube_D;
    std::cout << "Move_D" << std::endl;
    cube_D.Move_D();
    cube_D.print2D();

    CCube cube_R;
    std::cout << "Move_R" << std::endl;
    cube_R.Move_R();
    cube_R.print2D();

    CCube cube_L;
    std::cout << "Move_L" << std::endl;
    cube_L.Move_L();
    cube_L.print2D();

    CCube cube_F;
    std::cout << "Move_F" << std::endl;
    cube_F.Move_F();
    cube_F.print2D();

    CCube cube_B;
    std::cout << "Move_B" << std::endl;
    cube_B.Move_B();
    cube_B.print2D();

    CCube refCube;

    std::cout << "Move_U_Anti" << std::endl;
    cube_U.Move_U_Anti();
    cube_U.print2D();
    assert(cube_U == refCube);

    std::cout << "Move_D_Anti" << std::endl;
    cube_D.Move_D_Anti();
    cube_D.print2D();
    assert(cube_D == refCube);

    std::cout << "Move_R_Anti" << std::endl;
    cube_R.Move_R_Anti();
    cube_R.print2D();
    assert(cube_R == refCube);

    std::cout << "Move_L_Anti" << std::endl;
    cube_L.Move_L_Anti();
    cube_L.print2D();
    assert(cube_L == refCube);

    std::cout << "Move_F_Anti" << std::endl;
    cube_F.Move_F_Anti();
    cube_F.print2D();
    assert(cube_F == refCube);

    std::cout << "Move_B_Anti" << std::endl;
    cube_B.Move_B_Anti();
    cube_B.print2D();
    assert(cube_B == refCube);

    for ( int i = 0; i < 10; i ++ ) {
        cube.shaffle(10);
        std::cout << "Shaffle " << i << std::endl;
        cube.print2D();
    }
    return 0;
}
