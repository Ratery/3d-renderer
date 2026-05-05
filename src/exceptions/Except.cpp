#include "Except.h"

#include <exception>
#include <iostream>

namespace renderer {

void react() {
    try {
        throw;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
    }
}

}  // namespace renderer
