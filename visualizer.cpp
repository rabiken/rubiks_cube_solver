#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "face.hpp"
#include "cube.hpp"

const sf::Color colors[6] = {
    sf::Color::White,  // Top face
    sf::Color::Yellow, // Bottom face
    sf::Color::Red,    // Right face
    sf::Color::Green,  // Left face
    sf::Color::Blue,   // Front face
    sf::Color::Magenta // Back face
};

// Function to project 3D points to 2D points
sf::Vector2f project3DPoint(float x, float y, float z, float angleX, float angleY) {
    float distance = 3.0f; // Distance from the viewer
    float size = 250.0f; // Scaling factor for visualization

    // Rotate around X-axis
    float yRotatedX = cos(angleX) * y - sin(angleX) * z;
    float zRotatedX = sin(angleX) * y + cos(angleX) * z;

    // Rotate around Y-axis
    float xRotatedY = cos(angleY) * x + sin(angleY) * zRotatedX;
    float zRotatedY = -sin(angleY) * x + cos(angleY) * zRotatedX;

    // Perspective projection
    float projectedX = xRotatedY / (zRotatedY + distance) * size;
    float projectedY = yRotatedX / (zRotatedY + distance) * size;

    return sf::Vector2f(projectedX + 400, projectedY + 300); // Center on screen
}

void drawFace (int faceID, const CFace& faceC, const sf::Vector3f cp[4], float angleX, float angleY, sf::RenderWindow& window) {
    // middle points
    sf::Vector3f mp[12] = { 
        (2.0f*cp[0] + cp[1]) /3.0f,
        (cp[0] + 2.0f*cp[1]) /3.0f,
        (2.0f*cp[1] + cp[2]) /3.0f,
        (cp[1] + 2.0f*cp[2]) /3.0f,
        (2.0f*cp[2] + cp[3]) /3.0f,
        (cp[2] + 2.0f*cp[3]) /3.0f,
        (2.0f*cp[3] + cp[0]) /3.0f,
        (cp[3] + 2.0f*cp[0]) /3.0f,
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };
    mp[8] = (mp[7] + mp[0] - cp[0]);
    mp[9] = (mp[1] + mp[2] - cp[1]);
    mp[10] = (mp[3] + mp[4] - cp[2]);
    mp[11] = (mp[5] + mp[6] - cp[3]);

    const sf::Vector2f p[9][4] = {
        {   project3DPoint(cp[0].x, cp[0].y, cp[0].z, angleX, angleY), 
            project3DPoint(mp[0].x, mp[0].y, mp[0].z, angleX, angleY), 
            project3DPoint(mp[8].x, mp[8].y, mp[8].z, angleX, angleY), 
            project3DPoint(mp[7].x, mp[7].y, mp[7].z, angleX, angleY) 
        },
        {   project3DPoint(mp[0].x, mp[0].y, mp[0].z, angleX, angleY), 
            project3DPoint(mp[1].x, mp[1].y, mp[1].z, angleX, angleY), 
            project3DPoint(mp[9].x, mp[9].y, mp[9].z, angleX, angleY), 
            project3DPoint(mp[8].x, mp[8].y, mp[8].z, angleX, angleY) 
        },
        {   project3DPoint(cp[1].x, cp[1].y, cp[1].z, angleX, angleY), 
            project3DPoint(mp[2].x, mp[2].y, mp[2].z, angleX, angleY), 
            project3DPoint(mp[9].x, mp[9].y, mp[9].z, angleX, angleY), 
            project3DPoint(mp[1].x, mp[1].y, mp[1].z, angleX, angleY) 
        },
        {   project3DPoint(mp[2].x, mp[2].y, mp[2].z, angleX, angleY), 
            project3DPoint(mp[3].x, mp[3].y, mp[3].z, angleX, angleY), 
            project3DPoint(mp[10].x, mp[10].y, mp[10].z, angleX, angleY), 
            project3DPoint(mp[9].x, mp[9].y, mp[9].z, angleX, angleY) 
        },
        {   project3DPoint(cp[2].x, cp[2].y, cp[2].z, angleX, angleY), 
            project3DPoint(mp[4].x, mp[4].y, mp[4].z, angleX, angleY), 
            project3DPoint(mp[10].x, mp[10].y, mp[10].z, angleX, angleY), 
            project3DPoint(mp[3].x, mp[3].y, mp[3].z, angleX, angleY) 
        },
        {   project3DPoint(mp[4].x, mp[4].y, mp[4].z, angleX, angleY), 
            project3DPoint(mp[5].x, mp[5].y, mp[5].z, angleX, angleY), 
            project3DPoint(mp[11].x, mp[11].y, mp[11].z, angleX, angleY), 
            project3DPoint(mp[10].x, mp[10].y, mp[10].z, angleX, angleY) 
        },
        {   project3DPoint(cp[3].x, cp[3].y, cp[3].z, angleX, angleY), 
            project3DPoint(mp[6].x, mp[6].y, mp[6].z, angleX, angleY), 
            project3DPoint(mp[11].x, mp[11].y, mp[11].z, angleX, angleY), 
            project3DPoint(mp[5].x, mp[5].y, mp[5].z, angleX, angleY) 
        },
        {   project3DPoint(mp[6].x, mp[6].y, mp[6].z, angleX, angleY), 
            project3DPoint(mp[7].x, mp[7].y, mp[7].z, angleX, angleY), 
            project3DPoint(mp[8].x, mp[8].y, mp[8].z, angleX, angleY), 
            project3DPoint(mp[11].x, mp[11].y, mp[11].z, angleX, angleY) 
        },
        {   project3DPoint(mp[8].x, mp[8].y, mp[8].z, angleX, angleY), 
            project3DPoint(mp[9].x, mp[9].y, mp[9].z, angleX, angleY), 
            project3DPoint(mp[10].x, mp[10].y, mp[10].z, angleX, angleY), 
            project3DPoint(mp[11].x, mp[11].y, mp[11].z, angleX, angleY) 
        }
    };
    for ( int i = 0; i < 8; i ++ ) {
        sf::ConvexShape polygon(4);
        polygon.setPoint(0, p[i][0]);
        polygon.setPoint(1, p[i][1]);
        polygon.setPoint(2, p[i][2]);
        polygon.setPoint(3, p[i][3]);
        polygon.setFillColor(colors[faceC.GetID(i)/8]);
        window.draw(polygon);
    }
    sf::ConvexShape centerPolygon(4);
    centerPolygon.setPoint(0, p[8][0]);
    centerPolygon.setPoint(1, p[8][1]);
    centerPolygon.setPoint(2, p[8][2]);
    centerPolygon.setPoint(3, p[8][3]);
    centerPolygon.setFillColor(colors[faceID]);
    window.draw(centerPolygon);
}

void popMoveQueue(std::deque<EMove>& moves, CCube& rubiksC) {
    if (moves.size() == 0) {
        printf("No moves in the queue\n");
        return;
    }
    EMove move = moves.front();
    moves.pop_front();
    if (move == EMove::U) {
        rubiksC.Move_U();
    }
    else if (move == EMove::D) {
        rubiksC.Move_D();
    }
    else if (move == EMove::L) {
        rubiksC.Move_L();
    }
    else if (move == EMove::R) {
        rubiksC.Move_R();
    }
    else if (move == EMove::F) {
        rubiksC.Move_F();
    }
    else if (move == EMove::B) {
        rubiksC.Move_B();
    }
    else if (move == EMove::U_Anti) {
        rubiksC.Move_U_Anti();
    }
    else if (move == EMove::D_Anti) {
        rubiksC.Move_D_Anti();
    }
    else if (move == EMove::L_Anti) {
        rubiksC.Move_L_Anti();
    }
    else if (move == EMove::R_Anti) {
        rubiksC.Move_R_Anti();
    }
    else if (move == EMove::F_Anti) {
        rubiksC.Move_F_Anti();
    }
    else if (move == EMove::B_Anti) {
        rubiksC.Move_B_Anti();
    }
}

void manageEvents(sf::RenderWindow& window, float& angleX, float& angleY, 
    CCube& rubiksC, std::deque<EMove>& moves, sf::Clock& clock, bool faceMasks[6]) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
        {
            angleY += 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            angleY -= 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            angleX += 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            angleX -= 0.1f;
        }
        if (event.type != sf::Event::KeyPressed ) 
        {
            continue;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
            faceMasks[0] = !faceMasks[0];
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            faceMasks[1] = !faceMasks[1];
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            faceMasks[2] = !faceMasks[2];
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            faceMasks[3] = !faceMasks[3];
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            faceMasks[4] = !faceMasks[4];
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
            faceMasks[5] = !faceMasks[5];
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
        {   
            // Reset the cube
            rubiksC = CCube();
            // Reset the mask
            for (int i = 0; i < 6; i++) {
                faceMasks[i] = true;
            }
            // Reset the queue
            moves.clear();
        }
        // Terminal Mode
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        {
            std::cout << "Please enque the commands:" << std::endl;
            std::cout << "U: Up, D: Down, L: Left, R: Right, F: Front, B: Back, X': Anti-X" << std::endl;
            std::string input;
            std::cin >> input;
            if (input.size() == 0) {
                continue;
            }
            for ( int i = 0; i < (int)input.size(); i ++ ) {
                char x = input[i];
                x = std::toupper(x);
                if ( x != 'U' && x != 'D' && x != 'L' && x != 'R' && x != 'F' && x != 'B' && x != '\'' ) {
                    std::cout << "Invalid command: " << x << std::endl;
                    continue;
                }
                if ( x == '\'' ) {
                    if (moves.size() == 0) {
                        std::cout << "Invalid command: " << x << std::endl;
                        continue;
                    }
                    EMove prev = moves.back();
                    if ( prev == EMove::U ) {
                        moves.back() = EMove::U_Anti;
                    }
                    else if ( prev == EMove::D ) {
                        moves.back() = EMove::D_Anti;
                    }
                    else if ( prev == EMove::L ) {
                        moves.back() = EMove::L_Anti;
                    }
                    else if ( prev == EMove::R ) {
                        moves.back() = EMove::R_Anti;
                    }
                    else if ( prev == EMove::F ) {
                        moves.back() = EMove::F_Anti;
                    }
                    else if ( prev == EMove::B ) {
                        moves.back() = EMove::B_Anti;
                    }
                }
                else {
                    if ( x == 'U' ) {
                        moves.push_back(EMove::U);
                    }
                    else if ( x == 'D' ) {
                        moves.push_back(EMove::D);
                    }
                    else if ( x == 'L' ) {
                        moves.push_back(EMove::L);
                    }
                    else if ( x == 'R' ) {
                        moves.push_back(EMove::R);
                    }
                    else if ( x == 'F' ) {
                        moves.push_back(EMove::F);
                    }
                    else if ( x == 'B' ) {
                        moves.push_back(EMove::B);
                    }
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            popMoveQueue(moves, rubiksC);
        }
        // Print the current state of the cube in 2D
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) ) 
        {
            printf("Printing the current state of the cube in 2D:\n");
            rubiksC.print2D();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) 
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
                rubiksC.Move_U_Anti();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                rubiksC.Move_D_Anti();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                rubiksC.Move_L_Anti();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                rubiksC.Move_R_Anti();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                rubiksC.Move_F_Anti();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
                rubiksC.Move_B_Anti();
            }
        }
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
                rubiksC.Move_U();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                rubiksC.Move_D();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                rubiksC.Move_L();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                rubiksC.Move_R();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                rubiksC.Move_F();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
                rubiksC.Move_B();
            }
        }
    }
    clock.restart();
}

sf::Vector3f crossProduct(const sf::Vector3f& v1, const sf::Vector3f& v2) {
    sf::Vector3f cross;
    cross.x = v1.y * v2.z - v1.z * v2.y;
    cross.y = v1.z * v2.x - v1.x * v2.z;
    cross.z = v1.x * v2.y - v1.y * v2.x;
    return cross;
}

sf::Vector3f rotate3DPoint(const sf::Vector3f& point, float angleX, float angleY) {
    // Convert angles from degrees to radians
    float radX = angleX * M_PI / 180.0f;
    float radY = angleY * M_PI / 180.0f;

    // Rotate around X-axis
    sf::Vector3f rotated;
    rotated.x = point.x;
    rotated.y = point.y * cos(radX) - point.z * sin(radX);
    rotated.z = point.y * sin(radX) + point.z * cos(radX);

    // Rotate around Y-axis
    sf::Vector3f rotatedFinal;
    rotatedFinal.x = rotated.x * cos(radY) + rotated.z * sin(radY);
    rotatedFinal.y = rotated.y;
    rotatedFinal.z = -rotated.x * sin(radY) + rotated.z * cos(radY);

    return rotatedFinal;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rubik's Cube Visualizer");

    sf::Clock clock;
    float angleX = 0.0f;
    float angleY = 0.0f;

    // Vertices of a Rubik's Cube (3x3x3)
    float size = 1.0f;
    sf::Vector3f vertices[8] = {
        sf::Vector3f(-size, -size, size),
        sf::Vector3f(-size, size, size),
        sf::Vector3f(size, size, size),
        sf::Vector3f(size, -size, size),
        sf::Vector3f(-size, -size, -size),
        sf::Vector3f(-size, size, -size),
        sf::Vector3f(size, size, -size),
        sf::Vector3f(size, -size, -size),
    };

    // Edges of the cube
    const int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Top face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Bottom face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Side edges
    };

    const int faces[6][4] = {
        {0, 1, 2, 3},  // Top face
        {5, 6, 2, 1},  // Right face
        {7, 3, 2, 6},  // Front face
        {5, 1, 0, 4},   // Back face
        {0, 3, 7, 4},  // Left face
        {6, 7, 4, 5}  // Bottom face
    };

    CCube rubiksC;  // Rubik's Cube
    rubiksC.print2D();

    std::deque<EMove> moves;
    
    bool faceMasks[6] = {true, true, true, true, true, true};
    while (window.isOpen()) {
       manageEvents(window, angleX, angleY, rubiksC, moves, clock, faceMasks);

        window.clear(sf::Color::Black);
        // Draw edges
        for (const auto& edge : edges) {
            sf::Vector2f p1 = project3DPoint(vertices[edge[0]].x, vertices[edge[0]].y, vertices[edge[0]].z, angleX, angleY);
            sf::Vector2f p2 = project3DPoint(vertices[edge[1]].x, vertices[edge[1]].y, vertices[edge[1]].z, angleX, angleY);

            sf::Vertex line[] = {
                sf::Vertex(p1, sf::Color::Black),
                sf::Vertex(p2, sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
        }

        // Draw faces 
        for (int i = 5; i >= 0; i--) {
            if ( faceMasks[i] == false ) {
                continue;
            }
            CFace faceC = rubiksC.GetFace(i);
            sf::Vector3f cornersTmp[4];
            for (int j = 0; j < 4; j++) {
                cornersTmp[j] = vertices[faces[i][j]];
            }

        
            // sf::ConvexShape polygon(4);
            drawFace(i, faceC, cornersTmp, angleX, angleY, window);
            // polygon.setFillColor(colors[i]);
            // window.draw(polygon);
        }
        window.display();
    }

    return 0;
}
