#include "application/Application.h"
#include "exceptions/Except.h"
#include "render/Frame.h"

int main() {
    using namespace renderer;
    try {
        Application app(Width{800}, Height{600}, "3D Renderer");
        app.run();
    } catch (...) {
        react();
    }
    return 0;
}
