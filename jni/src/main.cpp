#include "TouchInput.h"

#ifdef __cplusplus
extern "C" {
#endif

int main() {
    auto touchDevice = android_touch::TouchInput::getNewInstance();

    if (touchDevice == nullptr) {
        std::cout << "no device found" << std::endl;
        return 0;
    }


    touchDevice->down(0, 500, 500, 50);
    touchDevice->commit();
    touchDevice->move(0, 500, 100, 50);
    touchDevice->commit();
    touchDevice->move(0, 500, 800, 50);
    touchDevice->up(0);
    touchDevice->commit();
}

#ifdef __cplusplus
}
#endif