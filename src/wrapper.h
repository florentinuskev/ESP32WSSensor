#ifndef WRAPPER_H
#define WRAPPER_H

#include <Arduino.h>

void asyncTimeout(const std::function<void()> &f, int delay);

#endif