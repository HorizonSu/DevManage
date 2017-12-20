#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dev.h"

#define DEV_NUM 8

Dev *DevInit(void)
{
    Dev *current = NULL;
    Dev *dev = (Dev *)malloc(DEV_NUM * sizeof(*dev));
    if (dev == NULL)
        return NULL;

    for (current = dev; current < dev + DEV_NUM; current++) {
        current->dev_no = current - dev;
        current->alloc = NO;
        *(current->process) = '\0';
        current->pos = 0;
    }

    return dev;
}

void DevDestroy(Dev *dev)
{
    free(dev);

    return;
}

int DevAssign(Dev *dev, const char *process, unsigned int pos)
{
    if (dev == NULL)
        return -1;

    dev->alloc = YES;
    strncpy(dev->process, process, 16);
    dev->pos = pos;

    return 0;
}

int DevRecover(Dev *dev, unsigned int len, const char *process)
{
    Dev *p = NULL;
    unsigned int count = 0;

    if (dev == NULL)
        return -1;

    for (p = dev; p < dev + len; p++) {
        if (strcmp(p->process, process) != 0)
            continue;
        p->alloc = NO;
        *(p->process) = '\0';
        p->pos = 0;
        count++;
    }

    return count;
}

int DevDisplay(Dev *dev)
{
    Dev *p = NULL;

    if (dev == NULL)
        return -1;

    fprintf(stdout, "\n输出设备表:\n");
    fprintf(stdout, "绝对号  \t是否分配\t占用进程\t相对号  \n");

    for (p = dev; p < dev + DEV_NUM; p++)
        fprintf(stdout, "%-8u\t%-8s\t%-8s\t%-8u\n", p->dev_no, p->alloc ? "YES" : "NO", p->process, p->pos);

    return 0;
}
