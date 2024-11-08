#ifndef ACTION_HANDLER_H
#define ACTION_HANDLER_H

#include "../client.h"

class ActionHandler{
    private:
    
    void processDuckEvents();
    Client& client;

    public:

    ActionHandler(Client &client);
    void processEvents();
};
#endif