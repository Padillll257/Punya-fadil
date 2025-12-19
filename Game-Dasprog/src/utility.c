#include <unistd.h>
#include "../include/utility.h"

void delay(int ms) {
    usleep(ms * 1000);
}
