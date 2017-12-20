#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dev_type.h"
#include "dev.h"

#define DEV_TYPE_NUM    3

static void DevTypeStore(DevType *tmp, const char *type, int total, Dev *addr)
{
    if (tmp == NULL)
        return;

    tmp->type = strdup(type);
    tmp->total = total;
    tmp->idle = total;
    tmp->addr = addr;

    return;
}

DevType *DevTypeInit(void)
{
    DevType *dev_type = NULL;
    Dev *dev = NULL;

    dev = DevInit();
    if (dev == NULL)
        return NULL;

    dev_type = (DevType *)malloc(DEV_TYPE_NUM * sizeof(*dev_type));
    if (dev_type == NULL) {
        free(dev);
        return NULL;
    }

    DevTypeStore(dev_type, "input", 2, dev);
    DevTypeStore(dev_type + 1, "printer", 3, dev += 2);
    DevTypeStore(dev_type + 2, "tape", 3, dev += 3);

    return dev_type;
}

void DevTypeDestroy(DevType *dev_type)
{
    DevType *p = NULL;

    if (dev_type == NULL)
        return;

    DevDestroy(dev_type->addr);

    for (p = dev_type; p < dev_type + DEV_TYPE_NUM; p++)
        free(p->type);

    free(dev_type);

    return;
}

int DevTypeAssign(DevType *dev_type, const char *process, const char *type, unsigned int pos)
{
    DevType *p = dev_type;
    int index = 0;
    Dev *tmp = NULL;

    if (dev_type == NULL || process == NULL || type == NULL)
        return -1;

    while (p < dev_type + DEV_TYPE_NUM && strcmp(p->type, type) != 0)
        p++;

    if (p == dev_type + DEV_TYPE_NUM)
        return -2;

    if (pos <= 0 || pos > p->total)
        return -3;

    for (tmp = p->addr; tmp < p->addr + p->total; tmp++) {
        if (tmp->pos == pos)
            return -4;
    }

    if (p->idle == 0)
        return 1;

    index = p->total - p->idle;
    p->idle--;
    tmp = p->addr + index;

    DevAssign(tmp, process, pos);

    return 0;
}

int DevTypeRecover(DevType *dev_type, const char *process)
{
    DevType *p = NULL;
    int flag = 1;
    int ret;

    if (dev_type == NULL || process == NULL)
        return -1;

    for (p = dev_type; p < dev_type + DEV_TYPE_NUM; p++) {
        if (p->idle == p->total)
            continue;

        ret = DevRecover(p->addr, p->total, process);
        if (ret > 0) {
            flag = 0;
            p->idle += ret;
        }
    }

    return flag;
}

int DevTypeDisplay(DevType *dev_type)
{
    DevType *p = NULL;

    if (dev_type == NULL)
        return -1;

    fprintf(stdout, "\n输出设备类表:\n");
    fprintf(stdout, "设备类型\t设备总量\t空闲设备\n");

    for (p = dev_type; p < dev_type + DEV_TYPE_NUM; p++)
        fprintf(stdout, "%-8s\t%-8u\t%-8u\n", p->type, p->total, p->idle);

    return DevDisplay(dev_type->addr);
}
