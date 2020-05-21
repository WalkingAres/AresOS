#ifndef PM_H
#define PM_H

#include "def.h"
//保存GDT IDT相关的数据结构

#define	GDT_SIZE	128
#define	IDT_SIZE	256


typedef struct descriptor {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t attr1;
    uint8_t limit_high_attr2;
    uint8_t base_high;
}DESCRIPTOR;

typedef struct gate{
	uint16_t	offset_low;	/* Offset Low */
	uint16_t	selector;	/* Selector */
	uint8_t	dcount;		/* 该字段只在调用门描述符中有效。如果在利用
				   调用门调用子程序时引起特权级的转换和堆栈
				   的改变，需要将外层堆栈中的参数复制到内层
				   堆栈。该双字计数字段就是用于说明这种情况
				   发生时，要复制的双字参数的数量。*/
	uint8_t	    attr;		/* P(1) DPL(2) DT(1) TYPE(4) */
	uint16_t    offset_high;	/* Offset High */
}GATE;

uint32_t    gdt_pos;//指向表中最后一个描述符

uint8_t		gdt_ptr[6];	/* 0~15:Limit  16~47:Base */
DESCRIPTOR	gdt[GDT_SIZE];
uint8_t		idt_ptr[6];	/* 0~15:Limit  16~47:Base */
GATE		idt[IDT_SIZE];

void init_dspt(DESCRIPTOR * dspt,uint32_t base, uint32_t limit, uint16_t attr) {
    dspt->limit_low = limit & 0x0ffff;
    dspt->base_low = base & 0x0ffff;
    dspt->base_mid = (base >> 16) & 0x0ff;
    dspt->attr1 = attr & 0x0ff;
    dspt->limit_high_attr2 = ((limit >> 16) & 0x0f) | (((attr >> 8) & 0x0f) << 4);
    dspt->base_high = (base >> 24) & 0x0ff;
}

#endif