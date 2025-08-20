#include "api/GraphAPI.hpp"
#include <crow.h>

int main() {
    crow::SimpleApp app;

    GraphAPI::registerEndpoints(app);

    app.port(8080).multithreaded().run();

    return 0;
}
