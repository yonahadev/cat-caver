//
//  customQueueClass.cpp
//  Executable
//
//  Created by tom on 2023/10/31.
//

#include "customQueue.hpp"
#include <iostream>
#include <vector>

CustomQueue::CustomQueue(const std::priority_queue<Node> &queue):queue(queue) {};

bool CustomQueue::findValue(const Vec2i &coordinates) const {
    std::priority_queue<Node> tempQueue = queue;
    while (tempQueue.empty() == false) {
        if (tempQueue.top().coordinates == coordinates) {
            return true;
        }
        tempQueue.pop();
    }
    return false;
}

Node CustomQueue::returnValue(const Vec2i &coordinates) const {
    std::priority_queue<Node> tempQueue = queue;
    while (tempQueue.empty() == false) {
        if (tempQueue.top().coordinates == coordinates) {
            return tempQueue.top();
        }
        tempQueue.pop();
    }
    Node null (coordinates,coordinates,0,0);
    return null;
}

void CustomQueue::printValues() const {
    std::priority_queue<Node> tempQueue = queue;
    while (tempQueue.empty() == false) {
        std::cout << tempQueue.top().coordinates.x << "," << tempQueue.top().coordinates.y << "\n";
        tempQueue.pop();
    }
}


std::priority_queue<Node> CustomQueue::removeValue(const Vec2i &coordinates) {
    std::priority_queue<Node> tempQueue = {};
    while (queue.empty() == false) {
        if (queue.top().coordinates != coordinates) {
            tempQueue.push(queue.top());
        }
        queue.pop();
    }
    return tempQueue;
}
