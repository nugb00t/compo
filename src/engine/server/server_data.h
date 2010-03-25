#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ServerState {
    static const uint MAX_ENTITIES = 4096;
    static const uint MAX_CLIENTS = 4;

    struct Entity {
        Vector3 position;
        Vector3 positionalVelocity;
        Quaternion rotation;
        Quaternion rotationalVelocity;

        bool active;
    };

    struct Client : Entity {
    };

    Entity entities[MAX_ENTITIES];
    Client clients[MAX_CLIENTS];

    uint time;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ServerRequests {
    struct Entity {
        Vector3 positionalVelocity;
        Quaternion rotationalVelocity;

		bool valid;
    };

    struct Client : Entity {};

    Entity entities[ServerState::MAX_ENTITIES];
    Client clients[ServerState::MAX_CLIENTS];

    uint time;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
