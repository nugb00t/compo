#ifndef SERVER_VIEW
#define SERVER_VIEW

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ServerView {
    static const unsigned MAX_ENTITIES = 4096;
    static const unsigned MAX_CLIENTS = 4;

    struct Entity {
        Vector3 position;
        Vector3 positionalVelocity;
        Quaternion direction;
        Quaternion directionalVelocity;

        bool active;
    };

    struct Client : Entity {
    };

    Entity entities[MAX_ENTITIES];
    Client clients[MAX_CLIENTS];

    unsigned time;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
