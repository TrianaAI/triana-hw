#ifndef MLX90614_HANDLER_H
#define MLX90614_HANDLER_H

#include <Adafruit_MLX90614.h>

class MLX90614Handler {
public:
    MLX90614Handler();
    void begin();
    void update();

private:
    Adafruit_MLX90614 mlx;
};

#endif // MLX90614_HANDLER_H