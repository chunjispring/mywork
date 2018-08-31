#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include "bas/bas_global.h"
#include "bas/bas_genathcd.h"

//中文测试

BAS_EXPORT int iGenAthcd(void)
{
    time_t tTime;
    int iVal;

    time(&tTime);
    srandom(tTime);
    //while ((iVal = random()%999999) < 9999);
    iVal = random() % 999999;
    return iVal;
}
