//
// Created by 夏雨 on 2023/10/12.
//

#ifndef CMAKE_DEMO_MAPSTATEENUM_H
#define CMAKE_DEMO_MAPSTATEENUM_H

#include <string>

struct MapStateInfo {
    int start_x_point;
    int start_y_point;

    int check_row;
    int check_col;
    float cell_size;

    std::string name;
};

extern const float MAP_CELL_SIZE;

extern const MapStateInfo STANDARD_11_9;


#endif //CMAKE_DEMO_MAPSTATEENUM_H
