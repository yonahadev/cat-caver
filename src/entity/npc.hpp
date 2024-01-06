//
//  npc.hpp
//  cat-caver
//
//  Created by tom on 2024/01/06.
//

#ifndef npc_hpp
#define npc_hpp

#include <stdio.h>
#include "sprite.hpp"

class NPC: public Sprite {
public:
    NPC(float offsetX,float offsetY, const int textureIndex);
};

#endif /* npc_hpp */
