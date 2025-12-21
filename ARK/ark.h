#ifndef ARK_H
#define ARK_H

#include "pico/stdlib.h"
#include "kernel/loops.h"

class Ark {
public:
    Ark();
    ~Ark();

    void Init();
    void Start();
    void Stop();

private:
    Loops main_loop; // Instance of the class defined in loops.h
};

#endif