/*
 *
 * This software is governed by the Broadcom Switch APIs license.
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenMDK/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <shbde.h>
#include <shbde_iproc.h>

/* Hardware abstractions for shared BDE functions */

static unsigned short
linux_pcic16_read(void *pci_dev, unsigned int addr)
{
    /* The PCI configuration read function might need to be implemented */
    /* once the related functions in libbde is hooked */
    fprintf(stdout, "PCI configuration 16-bits read needs to be implemented.\n");

    return 0;
}

static void
linux_pcic16_write(void *pci_dev, unsigned int addr, unsigned short data)
{
    /* The PCI configuration write function might need to be implemented */
    /* once the related functions in libbde is hooked */
    fprintf(stdout, "PCI configuration 16-bits write needs to be implemented.\n");
}

static unsigned int
linux_pcic32_read(void *pci_dev, unsigned int addr)
{
    /* The PCI configuration read function might need to be implemented */
    /* once the related functions in libbde is hooked */
    fprintf(stdout, "PCI configuration 32-bits read needs to be implemented.\n");

    return 0;
}

static void
linux_pcic32_write(void *pci_dev, unsigned int addr, unsigned int data)
{
    /* The PCI configuration write function might need to be implemented */
    /* once the related functions in libbde is hooked */
    fprintf(stdout, "PCI configuration 32-bits write needs to be implemented.\n");
}

static unsigned int
linux_io32_read(void *addr)
{
    /* Juniper SRX300 (Octeon III, little-endian): the PAXB (BAR0) MMIO
     * window maps the CMIC registers in big-endian byte order, so 32-bit
     * accesses must be byte-swapped in software. See linux-user.c. */
    return __builtin_bswap32(*((volatile unsigned int *)addr));
}

static void
linux_io32_write(void *addr, unsigned int data)
{
    /* see linux_io32_read(): software byte swap on the PAXB window */
    *((volatile unsigned int *)addr) = __builtin_bswap32(data);
}

static void
linux_usleep(int usec)
{
    usleep(usec);
}

/*
 * Function:
 *      linux_shbde_hal_init
 * Purpose:
 *      Initialize hardware abstraction module for Linux kernel.
 * Parameters:
 *      shbde - pointer to uninitialized hardware abstraction module
 *      log_func - optional log output function
 * Returns:
 *      Always 0
 */
int
linux_shbde_hal_init(shbde_hal_t *shbde, shbde_log_func_t log_func)
{
    memset(shbde, 0, sizeof(*shbde));

    shbde->log_func = log_func;

    shbde->pcic16_read = linux_pcic16_read;
    shbde->pcic16_write = linux_pcic16_write;
    shbde->pcic32_read = linux_pcic32_read;
    shbde->pcic32_write = linux_pcic32_write;

    shbde->io32_read = linux_io32_read;
    shbde->io32_write = linux_io32_write;

    shbde->usleep = linux_usleep;

    return 0;
}
