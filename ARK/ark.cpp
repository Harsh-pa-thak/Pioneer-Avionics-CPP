#include "ark.h"

Ark::Ark() {}
Ark::~Ark() {}

void Ark::Init() {
    stdio_init_all();
}

void Ark::Start() {
    main_loop.Run();
}

void Ark::Stop() {
    while (true) {
        tight_loop_contents();
    }
}