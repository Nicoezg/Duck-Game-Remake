//
// Created by fran on 21/10/24.
//

#ifndef TALLER_TP_EVENT_TYPE_H
#define TALLER_TP_EVENT_TYPE_H

enum EventType {
    CREATE_GAME = 0x01,
    JOIN_GAME = 0x02,
    BROADCAST = 0x03,
    NEW_PLAYER = 0x04,
    REFRESH_GAMES = 0x05,
    START_GAME = 0x06,
    SCORE = 0x07,
    GAME_OVER = 0x08,
    MAP_LOAD = 0x09,
};

#endif // TALLER_TP_EVENT_TYPE_H