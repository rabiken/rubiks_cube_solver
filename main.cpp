#include "solver.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>


std::vector<bool> mask_1st() {
    std::vector<bool> mask(48, false);
    for ( int i = 0; i < 4; i ++ ) {
        mask[i*2+1] = true;  
    }
    mask[3*8+2] = true;
    mask[1*8+5] = true;
    mask[2*8+3] = true;
    mask[4*8+1] = true;
    return mask;
}
std::vector<bool> mask_2nd_1() {
    std::vector<bool> mask = mask_1st();
    mask[0] = true;
    mask[3*8+4] = mask[4*8+0] = true;
    return mask;
}
std::vector<bool> mask_2nd_2() {
    std::vector<bool> mask = mask_2nd_1();
    mask[2] = mask[3*8+2] = mask[1*8+6] = true;
    return mask;
}
std::vector<bool> mask_2nd_3() {
    std::vector<bool> mask = mask_2nd_2();
    mask[4] = mask[1*8+4] = mask[2*8+4] = true;
    return mask;
}
std::vector<bool> mask_2nd_4() {
    std::vector<bool> mask = mask_2nd_3();
    mask[6] = mask[2*8+2] = mask[4*8+2] = true;
    return mask;
}
std::vector<bool> mask_3rd_1() {
    std::vector<bool> mask = mask_2nd_4();
    mask[3*8+1] = mask[1*8+7] = true;
    return mask;
}
std::vector<bool> mask_3rd_2() {
    std::vector<bool> mask = mask_3rd_1();
    mask[1*8+3] = mask[2*8+5] = true;
    return mask;
}
std::vector<bool> mask_3rd_3() {
    std::vector<bool> mask = mask_3rd_2();
    mask[2*8+1] = mask[4*8+3] = true;
    return mask;
}
std::vector<bool> mask_3rd_4() {
    std::vector<bool> mask = mask_3rd_3();
    mask[4*8+7] = mask[3*8+5] = true;
    return mask;
}
std::vector<bool> mask_4th_1() {
    std::vector<bool> mask = mask_3rd_4();
    mask[2*8+7] = mask[5*8+1] = true;
    return mask;
}
std::vector<bool> mask_4th_2() {
    std::vector<bool> mask = mask_4th_1();
    mask[1*8+1] = mask[5*8+3] = true;
    return mask;
}
std::vector<bool> mask_4th_3() {
    std::vector<bool> mask = mask_4th_2();
    mask[3*8+7] = mask[5*8+5] = true;
    return mask;
}
std::vector<bool> mask_4th_4() {
    std::vector<bool> mask = mask_4th_3();
    mask[4*8+5] = mask[5*8+7] = true;
    return mask;
}
std::vector<bool> mask_5th_1() {
    std::vector<bool> mask = mask_4th_4();
    mask[5*8+0] = mask[2*8+0] = mask[4*8+4] = true;
    return mask;
}
std::vector<bool> mask_5th_2() {
    std::vector<bool> mask = mask_5th_1();
    mask[5*8+4] = mask[3*8+0] = mask[1*8+0] = true;
    return mask;
}
std::vector<bool> mask_5th_3() {
    std::vector<bool> mask = mask_5th_2();
    mask[5*8+2] = mask[1*8+2] = mask[2*8+6] = true;
    return mask;
}
std::vector<bool> mask_5th_4() {
    std::vector<bool> mask = mask_5th_3();
    mask[5*8+6] = mask[4*8+6] = mask[3*8+6] = true;
    return mask;
}


int main () 
{
    std::srand(std::time(nullptr));
    CSolver solver;
    std::string solution;
    CCube problem;
    std::cout << "Type the number of shuffles: ";
    int n = 0;
    std::cin >> n;
    std::string shaffleMoves = problem.shaffle(n);
    printf("Shaffle Moves:\n%s\n", shaffleMoves.c_str());

    printf("Problem:\n");
    problem.print2D();
    CCube goal;
    printf("Goal:\n");
    goal.print2D();

    // solver.Solve_AStar(problem, solution, problem, goal, mask_5th_4());
    // printf("Solution: %s\n", solution.c_str());

    CCube resCube = problem;
    std::vector<bool> masks[] =
        { mask_1st()
        , mask_2nd_1(), mask_2nd_2(), mask_2nd_3(), mask_2nd_4()
        , mask_3rd_1(), mask_3rd_2(), mask_3rd_3(), mask_3rd_4()
        , mask_4th_1(), mask_4th_2(), mask_4th_3(), mask_4th_4()
        , mask_5th_1(), mask_5th_2(), /*mask_5th_3(),*/ mask_5th_4()
        };

    for ( int i = 0; i < 16; i ++ ) {
        problem = resCube;
        std::string tmpSolution = "";
        printf("========= Level %d ========================\n", i+1);
        solver.Solve_AStar(resCube, tmpSolution, problem, goal, masks[i]);
        // solver.Solve_IDAStar(resCube, tmpSolution, problem, goal, masks[i]);
        printf("Solution: %s\n", tmpSolution.c_str());
        solution = solution + tmpSolution;
        printf("Total Solution: %s\n", solution.c_str());
        printf("===========================================\n");
    }
    printf("Final Solution: %s\n", solution.c_str());
    return 0;
}