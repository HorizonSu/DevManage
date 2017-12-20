#ifndef __DEV_TYPE_H__
#define __DEV_TYPE_H__

#include "dev.h"

/* 设备类表结构 */
typedef struct {
    char *type;
    unsigned int total;
    unsigned int idle;
    Dev *addr;
} DevType;

extern DevType *DevTypeInit(void);                                                                      /* 设备类表初始化 */
extern void DevTypeDestroy(DevType *dev_type);                                                          /* 设备类表释放 */
extern int DevTypeAssign(DevType *dev_type, const char *process, const char *type, unsigned int pos);   /* 设备类表分配设备操作 */
extern int DevTypeRecover(DevType *dev_type, const char *process);                                      /* 设备类表回收设备操作 */
extern int DevTypeDisplay(DevType *dev_type);                                                           /* 显示设备类表 */

#endif
