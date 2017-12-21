#ifndef _DEVICE_H
#define _DEVICE_H

#include <stdint.h>
#include "mathlib.h"
#include "primitive.h"
#include "rgb.h"

void device_init(size_t width, size_t height);
void device_exit();
void device_clear();
void device_flip();
void device_draw(struct tri *primitive);
void device_drawframe(struct tri *primitive);


#endif
