#ifndef HITBOX_H
#define HITBOX_H

struct hitBox {
    int x, y;          
    int width, height;  
    
    hitBox(int x = 0, int y = 0, int width = 0, int height = 0)
        : x(x), y(y), width(width), height(height) {}
    
    static bool isColliding(const hitBox &box1, const hitBox &box2) {
        return (box1.x < box2.x + box2.width &&
                box1.x + box1.width > box2.x &&
                box1.y < box2.y + box2.height &&
                box1.y + box1.height > box2.y);
    }
};

#endif // HITBOX_H
