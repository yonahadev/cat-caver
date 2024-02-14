//
//  customQueueClass.hpp
//  Executable
//
//  Created by tom on 2023/10/31.
//

#ifndef customQueue_hpp
#define customQueue_hpp

#include <stdio.h>
#include <queue>
#include "vec2.hpp"
#include "node.hpp"

class CustomQueue {
private:
public:
    std::priority_queue<Node> queue;
    bool findValue(const Vec2i &coordinates) const;
    Node returnValue(const Vec2i &coordinates) const;
    std::priority_queue<Node> removeValue(const Vec2i &coordinates);
    void printValues() const;
    CustomQueue(const std::priority_queue<Node> &queue);
    CustomQueue() = default;
};

#endif /* customQueueClass_hpp */
