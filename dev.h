#ifndef __DEV_H__
#define __DEV_H__

typedef enum {
    NO,
    YES
} Whether;

/* 设备表结构 */
typedef struct {
    unsigned int dev_no;
    Whether alloc;
    char process[16];
    unsigned int pos;
} Dev;

extern Dev *DevInit(void);                                                  /* 初始化设备表 */
extern void DevDestroy(Dev *dev);                                           /* 释放设备表 */
extern int DevAssign(Dev *dev, const char *process, unsigned int pos);      /* 设备表分配设备操作 */
extern int DevRecover(Dev *dev, unsigned int len, const char *process);     /* 设备表回收设备操作 */
extern int DevDisplay(Dev *dev);                                            /* 显示设备表 */

#endif
