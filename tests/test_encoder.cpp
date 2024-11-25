#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "common/protocol/common/encoder.h"
#include "common/protocol/actions/actions_protocol.h"
#include "common/protocol/events/events_protocol.h"

TEST(Encode, GameCode)
{
    Encoder encoder;
    std::vector<int8_t> buffer(GAME_CODE_SIZE);
    int game_code = 1234;

    encoder.encode_game_code(game_code, buffer.data());

    std::vector<int8_t > expected = {0, 0, 4, -46};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, GameCode)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {0, 0, 4, -46};

    int game_code = encoder.decode_game_code(buffer);

    EXPECT_EQ(game_code, 1234);
}

TEST(Encode, PlayerId)
{
    Encoder encoder;
    std::vector<int8_t> buffer(PLAYER_ID_SIZE);
    int player_id = 1234;

    encoder.encode_player_id(player_id, buffer.data());

    std::vector<int8_t > expected = {4, -46};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, PlayerId)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {4, -46};

    int player_id = encoder.decode_player_id(buffer);

    EXPECT_EQ(player_id, 1234);
}

TEST(Encode, ActionType)
{
    Encoder encoder;
    std::vector<int8_t> buffer(ACTION_TYPE_SIZE);
    ActionType type = CREATE_REQUEST;

    encoder.encode_action_type(type, buffer.data());

    std::vector<int8_t > expected = {0x01};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, ActionType)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {0x01};

    ActionType type = encoder.decode_action_type(buffer);

    EXPECT_EQ(type, CREATE_REQUEST);
}

TEST(Encode, GameMode)
{
    Encoder encoder;
    std::vector<int8_t> buffer(GAME_MODE_SIZE);
    GameMode game_mode = UN_JUGADOR;

    encoder.encode_game_mode(game_mode, buffer.data());

    std::vector<int8_t > expected = {1};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, GameMode)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {1};

    GameMode game_mode = encoder.decode_game_mode(buffer);

    EXPECT_EQ(game_mode, UN_JUGADOR);
}

TEST(Encode, MaxPlayerSize)
{
    Encoder encoder;
    std::vector<int8_t> buffer(MAX_PLAYER_SIZE);
    int max_players = 123;

    encoder.encode_max_players(max_players, buffer.data());

    std::vector<int8_t > expected = {123};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, MaxPlayerSize)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {123};

    int max_players = encoder.decode_max_players(buffer);

    EXPECT_EQ(max_players, 123);
}

TEST(Encode, IsRight)
{
    Encoder encoder;
    std::vector<int8_t> buffer(IS_RIGHT_SIZE);
    bool is_right = true;

    encoder.encode_bool(is_right, buffer.data());

    std::vector<int8_t > expected = {1};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, IsRight)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {1};

    bool is_right = encoder.decode_bool(buffer);

    EXPECT_EQ(is_right, true);
}

TEST(Encode, Bool)
{
    Encoder encoder;
    std::vector<int8_t> buffer(IS_RIGHT_SIZE);
    bool is_connected = true;

    encoder.encode_bool(is_connected, buffer.data());

    std::vector<int8_t > expected = {1};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, Bool)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {1};

    bool is_connected = encoder.decode_bool(buffer);

    EXPECT_EQ(is_connected, true);
}

TEST(Encode, Coordinate)
{
    Encoder encoder;
    std::vector<int8_t> buffer(2);
    int16_t coordinate = 1234;

    encoder.encode_coordinate(coordinate, buffer.data());

    std::vector<int8_t > expected = {4, -46};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, Coordinate)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {4, -46};

    int16_t coordinate = encoder.decode_coordinate(buffer);

    EXPECT_EQ(coordinate, 1234);
}

TEST(Encode, Len)
{
    Encoder encoder;
    std::vector<int8_t> buffer(1);
    uint8_t len = 123;

    encoder.encode_len(len, buffer.data());

    std::vector<int8_t > expected = {123};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, Len)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {123};

    int len = encoder.decode_len(buffer);

    EXPECT_EQ(len, 123);
}

TEST(Encode, PlayerState)
{
    Encoder encoder;
    std::vector<int8_t> buffer(PLAYER_STATE_SIZE);
    State state = PLAYING_DEAD;

    encoder.encode_player_state(state, buffer.data());

    std::vector<int8_t > expected = {4};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, PlayerState)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {4};

    State state = encoder.decode_player_state(buffer);

    EXPECT_EQ(state, PLAYING_DEAD);
}

TEST(Encode, Id)
{
    Encoder encoder;
    std::vector<int8_t> buffer(BULLET_ID_SIZE);
    uint8_t id = 123;

    encoder.encode_id(id, buffer.data());

    std::vector<int8_t > expected = {123};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, Id)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {123};

    uint8_t id = encoder.decode_id(buffer);

    EXPECT_EQ(id, 123);
}

TEST(Encode, TileId)
{
    Encoder encoder;
    std::vector<int8_t> buffer(TILE_ID_SIZE);
    uint8_t tile_id = 123;

    encoder.encode_tile_id(tile_id, buffer.data());

    std::vector<int8_t > expected = {123};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, TileId)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {123};

    uint8_t tile_id = encoder.decode_tile_id(buffer);

    EXPECT_EQ(tile_id, 123);
}

TEST(Encode, BackgroundId)
{
    Encoder encoder;
    std::vector<int8_t> buffer(BACKGROUND_ID_SIZE);
    uint8_t background_id = 123;

    encoder.encode_background_id(background_id, buffer.data());

    std::vector<int8_t > expected = {123};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, BackgroundId)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {123};

    uint8_t background_id = encoder.decode_background_id(buffer);

    EXPECT_EQ(background_id, 123);
}

TEST(Encode, Angle)
{
    Encoder encoder;
    std::vector<int8_t> buffer(ANGLE_SIZE);
    float angle = 10.53;

    encoder.encode_angle(angle, buffer.data());

    std::vector<int8_t > expected = {4,29};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, Angle)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {4, 29};

    float angle = encoder.decode_angle(buffer);

    EXPECT_EQ(std::round(angle*100), 1053);
}

TEST(Encode, ActualPlayers)
{
    Encoder encoder;
    std::vector<int8_t> buffer(ACTUAL_PLAYER_SIZE);
    uint8_t actual_players = 123;

    encoder.encode_actual_players(actual_players, buffer.data());

    std::vector<int8_t > expected = {123};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, ActualPlayers)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {123};

    uint8_t actual_players = encoder.decode_actual_players(buffer);

    EXPECT_EQ(actual_players, 123);
}

TEST(Encode, EventType)
{
    Encoder encoder;
    std::vector<int8_t> buffer(EVENT_TYPE_SIZE);
    EventType type = CREATE_GAME;

    encoder.encode_event_type(type, buffer.data());

    std::vector<int8_t > expected = {0x01};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, EventType)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {0x01};

    EventType type = encoder.decode_event_type(buffer);

    EXPECT_EQ(type, CREATE_GAME);
}

TEST(Encode, Score)
{
    Encoder encoder;
    std::vector<int8_t> buffer(SCORE_SIZE);
    int score = 1234;

    encoder.encode_score(score, buffer.data());

    std::vector<int8_t > expected = {4, -46};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, Score)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {4, -46};

    int score = encoder.decode_score(buffer);

    EXPECT_EQ(score, 1234);
}

TEST(Encode, Strin)
{
    Encoder encoder;
    std::vector<int8_t> buffer(10);
    std::string str = "hola";

    encoder.encode_string(str, buffer.data(), 4);

    std::vector<int8_t > expected = {104, 111, 108, 97, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(buffer, expected);
}

TEST(Decode, String)
{
    Encoder encoder;
    std::vector<int8_t> buffer = {104, 111, 108, 97, 0, 0, 0, 0, 0, 0};

    std::string str = encoder.decode_string(buffer, 4);

    EXPECT_EQ(str, "hola");
}