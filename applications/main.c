/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/

#include <rtthread.h>
#define APP_RO_BASE     0x80000000
#define APP_SIZE        (1*1024*1024)

int jump_rtthread0(void);
int jump_rtthread1(void);

int main(int argc, char **argv)
{
    rt_kprintf("Hello, I am preloader.\n");

    jump_rtthread0();

    return 0;
}

static void demo_load_jump(const char *devName)
{
    struct rt_device_blk_geometry geo;
    rt_device_t device = RT_NULL;
    void (*fw_func)(void);
    fw_func = (void(*)(void))APP_RO_BASE;

    int blk_num;

    if ((device = rt_device_find(devName)) == RT_NULL)
    {
        rt_kprintf("Failed to find %s.\n", devName);
        goto exit_demo_read;
    }

    if (rt_device_open(device, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("Open device %s failed!\n", devName);
        goto exit_demo_read;
    }

    rt_memset(&geo, 0, sizeof(geo));
    if (rt_device_control(device, RT_DEVICE_CTRL_BLK_GETGEOME, &geo) != RT_EOK)
    {
        rt_kprintf("%s CTRL_BLK_GETGEOME failed!\n", devName);
        goto exit_demo_read;
    }
    else if (geo.block_size == 0)
    {
        rt_kprintf("Invalid block size!\n", devName);
        goto exit_demo_read;
    }

    blk_num = APP_SIZE / geo.block_size;
    rt_kprintf("geo.block_size: %d\n", geo.block_size);
    rt_kprintf("load blk_num: %d\n", blk_num);
    rt_size_t size = rt_device_read(device,
                                    0,
                                    (void *)APP_RO_BASE,
                                    blk_num);
    if (size != blk_num)
    {
        rt_kprintf("Failed to read %d");
        goto exit_demo_read;
    }

    rt_kprintf("Loading done, will jump\n");
    if (device)
        rt_device_close(device);
    device = RT_NULL;

    /* Enter interrupt */
    rt_interrupt_enter();

    /* Jump to APP_RO_BASE */
    fw_func();

    /* won't go here*/
    /* Leave interrupt */
    rt_interrupt_leave();

exit_demo_read:

    if (device)
        rt_device_close(device);
}

int jump_rtthread0(void)
{
    demo_load_jump("rtthread0");
    return 0;
}
MSH_CMD_EXPORT(jump_rtthread0, Demo to load and jump);

int jump_rtthread1(void)
{
    demo_load_jump("rtthread0");
    return 0;
}
MSH_CMD_EXPORT(jump_rtthread1, Demo to load and jump);
