#include "core/Application.h"
#include "core/Logger.h"
#include <iostream>

int main() {
    try {
        VE::Application app;
        app.Run();
    }
    catch (const std::exception& e) {
        std::cerr << "HATA: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
