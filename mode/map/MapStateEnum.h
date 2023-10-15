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


// 地图链表
class MapNode {
public:
    std::pair<int, int> sitePair;

    // 指向下一个节点的指针
    MapNode* next;
  //  MapNode( std::pair<int, int> &sitePair) : value(&sitePair), next(nullptr) {}
};



#endif //CMAKE_DEMO_MAPSTATEENUM_H
