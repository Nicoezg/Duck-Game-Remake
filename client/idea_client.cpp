#include "idea_client.h"
#include <iostream>
#include <ostream>

Client::Client(int id): client_id(id){
}

void Client::moveLeft(){
    std::cout << "Moving left" << std::endl;

}

void Client::moveRight(){
    std::cout << "Moving right" << std::endl;

}

void Client::playDead(){
    std::cout << "Playing dead" << std::endl;

}

void Client::up(){
    std::cout << "Jumping" << std::endl;

}

void Client::aimUpwards(){
    std::cout << "Aiming upwards" << std::endl;

}

void Client::pickUp(){
    std::cout << "Picking up" << std::endl;

}

void Client::drop(){
    std::cout << "Dropping" << std::endl;

}

void Client::shoot(){
    std::cout << "Shooting" << std::endl;

}

void Client::stopMoving(){
    std::cout << "Stopping" << std::endl;

}