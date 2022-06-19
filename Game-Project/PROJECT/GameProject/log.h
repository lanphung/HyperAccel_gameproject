#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>

#define LOGI(fmt, ...)  {printf(fmt "\n", ##__VA_ARGS__);}
#define LOGE(fmt, ...)  {printf(fmt "\n", ##__VA_ARGS__);}

#endif