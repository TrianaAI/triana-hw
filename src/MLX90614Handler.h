#ifndef MLX90614_HANDLER_H
#define MLX90614_HANDLER_H

#include <Adafruit_MLX90614.h>
#include "FirebaseAsyncHandler.h"

class MLX90614Handler {
public:
    MLX90614Handler();
    void begin();
    void update();
    // void updateWithFirebase(FirebaseAsyncHandler &firebaseHandler); // Pass FirebaseAsyncHandler reference

private:
    Adafruit_MLX90614 mlx;
    bool checkingActivation = false;
};

#endif // MLX90614_HANDLER_H