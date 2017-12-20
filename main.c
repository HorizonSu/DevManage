#include <stdio.h>
#include "dev_type.h"

#define STR_LEN 16

/* 读取字符串 */
static int GetStr(char *str, unsigned int len)
{
    char *p = NULL;

    if (str== NULL)
        return -1;

    if (fgets(str, len, stdin) == NULL)
        return -1;

    for (p = str; *p != '\0'; p++) {
        if (*p == '\n') {
            *p = '\0';
            break;
        }
    }

    return p - str;
}

/* 读取整数 */
static int GetInt(unsigned int *value)
{
    if (value == NULL)
        return -1;

    while (fscanf(stdin, "%u", value) != 1)
        while (getchar() != '\n');

    while (getchar() != '\n');

    return 0;
}

/* 分配函数 */
static int Assign(DevType *dev_type)
{
    char process[STR_LEN];
    char type[STR_LEN];
    unsigned int pos;
    int ret;

    if (dev_type == NULL)
        return -1;

    fprintf(stdout, "\n请输入进程名、所需设备类和设备相对号:\n");

    fprintf(stdout, "进程名:");
    GetStr(process, STR_LEN);
    fprintf(stdout, "设备类:");
    GetStr(type, STR_LEN);
    fprintf(stdout, "相对号:");
    GetInt(&pos);
    fprintf(stdout, "\n");

    ret = DevTypeAssign(dev_type, process, type, pos);

    switch (ret) {
    case -1:
        fprintf(stdout, "参数错误!\n");
        break;
    case -2:
        fprintf(stdout, "没有该设备类型!\n");
        break;
    case -3:
        fprintf(stdout, "设备相对号错误!\n");
        break;
    case -4:
        fprintf(stdout, "该相对设备号已被占用!\n");
        break;
    case 1:
        fprintf(stdout, "没有多余的空闲设备!\n");
        break;
    default:
        fprintf(stdout, "设备分配成功!\n");
        break;
    }

    return ret;
}

/* 回收函数 */
static int Recover(DevType *dev_type)
{
    char process[STR_LEN];
    int ret;

    if (dev_type == NULL)
        return -1;

    fprintf(stdout, "\n请输入进程名:");
    GetStr(process, STR_LEN);
    fprintf(stdout, "\n");

    ret = DevTypeRecover(dev_type, process);
    if (ret == -1)
        fprintf(stdout, "参数错误!\n");
    else if (ret == 1)
        fprintf(stdout, "没有该进程!\n");
    else
        fprintf(stdout, "设备回收成功!\n");

    return ret;
}

/* 显示函数 */
static inline int Display(DevType *dev_type)
{
    return DevTypeDisplay(dev_type);
}

/* 功能执行 */
static inline void Process(DevType *dev_type, int option)
{
    switch (option) {
    case 1:
        Assign(dev_type);
        break;
    case 2:
        Recover(dev_type);
        break;
    case 3:
        Display(dev_type);
        break;
    default:
        break;
    }

    return;
}

/* 选择执行设备操作 */
static void SelectFun(DevType *dev_type)
{
    int option = 0;

    do {
        fprintf(stdout, "\n\n\n======================================================\n");
        fprintf(stdout, "1-分配  2-回收  3-显示  0-退出\n");
        fprintf(stdout, "请选择功能项<0-3>: ");

        if (fscanf(stdin, "%d", &option) != 1 || option < 0 || option > 3) {
            fprintf(stdout, "输入错误!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (option == 0)
            break;

        Process(dev_type, option);
    } while (1);

    return;
}

int main(void)
{
    DevType *dev_type = DevTypeInit();      /* 初始化设备类表 */

    if (dev_type == NULL)                   /* 初始化失败 */
        return -1;                          /* 退出程序 */   

    SelectFun(dev_type);                    /* 选择设备操作并执行 */

    DevTypeDestroy(dev_type);               /* 释放设备类表 */

    return 0;
}
