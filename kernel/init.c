#include "def.h"
#include "stdio.h"
#include "string.h"
#include "pm.h"


void init_gdt() {
    memcpy( gdt,
            ((void *)(*(uint32_t *)(&gdt_ptr[2]))),
            (*(uint16_t *)&gdt_ptr[0]) + 1);

    printf("gdt is loaded!\r\n");
    uint32_t *p = &gdt_ptr[2];
    *p = &gdt;
    return;
}