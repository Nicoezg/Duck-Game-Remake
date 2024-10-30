#ifndef CLIENT_H
#define CLIENT_H

class Client{
    private:
    int client_id;

    public:
    Client(int id);

    void moveLeft();
    
    void moveRight();

    void playDead();

    void up();

    void aimUpwards();

    void pickUp();

    void drop();

    void shoot();

    void stopMoving();
};
#endif