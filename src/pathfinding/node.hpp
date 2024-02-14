//
//  nodeStruct.hpp
//  Executable
//
//  Created by tom on 2023/10/30.
//

#ifndef node_hpp
#define node_hpp

#include <stdio.h>
#include "vec2.hpp"

struct Node {
    Vec2i coordinates;
    Vec2i parent;
    float gCost; //dist from start node
    float hCost; //estimated dist from end node
     
    bool operator<(const Node &other) const {
        return hCost+gCost > other.hCost+other.gCost;
    }
    
    Node(Vec2i coordinates, Vec2i parent,float gCost,float hCost): coordinates(coordinates),gCost(gCost),hCost(hCost),parent(parent) {};
    
    
};
#endif /* nodeStruct_hpp */
