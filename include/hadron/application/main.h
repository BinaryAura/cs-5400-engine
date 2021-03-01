#ifndef MAIN_H
#define MAIN_H

#include "hadron/application/application.h"

extern Application* create(const int32_t, const char**);

int32_t main(const int32_t argc, const char** argv);

#endif // MAIN_H
