#include "myUtil.h"
#include <stdlib.h>

float rand(float min, float max) {
	return min + (max - min)*(rand() % 10001) / 10000.0;
}