#ifndef PM_H
#define PM_H

#include "def.h"
#include "int.h"

//保存GDT IDT相关的数据结构

#define	GDT_SIZE	128
#define	IDT_SIZE	256

//每个任务的局部描述符
#define LDT_SIZE	2

//段描述符
typedef struct descriptor {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t attr1;
    uint8_t limit_high_attr2;
    uint8_t base_high;
}DESCRIPTOR;

typedef struct gate{
	uint16_t	offset_low;		/* Offset Low */
	uint16_t	selector;		/* Selector */
	uint8_t		dcount;			/* 该字段只在调用门描述符中有效。如果在利用
				   				调用门调用子程序时引起特权级的转换和堆栈
				   				的改变，需要将外层堆栈中的参数复制到内层
				   				堆栈。该双字计数字段就是用于说明这种情况
				   				发生时，要复制的双字参数的数量。*/
	uint8_t	    attr;			/* P(1) DPL(2) DT(1) TYPE(4) */
	uint16_t    offset_high;	/* Offset High */
}GATE;

typedef struct s_tss {
	uint32_t	backlink;
	uint32_t	esp0;	/* stack pointer to use during interrupt */
	uint32_t	ss0;	/*   "   segment  "  "    "        "     */
	uint32_t	esp1;
	uint32_t	ss1;
	uint32_t	esp2;
	uint32_t	ss2;
	uint32_t	cr3;
	uint32_t	eip;
	uint32_t	flags;
	uint32_t	eax;
	uint32_t	ecx;
	uint32_t	edx;
	uint32_t	ebx;
	uint32_t	esp;
	uint32_t	ebp;
	uint32_t	esi;
	uint32_t	edi;
	uint32_t	es;
	uint32_t	cs;
	uint32_t	ss;
	uint32_t	ds;
	uint32_t	fs;
	uint32_t	gs;
	uint32_t	ldt;
	uint16_t	trap;
	uint16_t	iobase;	/* I/O位图基址大于或等于TSS段界限，就表示没有I/O许可位图 */
}TSS;


// uint32_t    gdt_pos;//指向表中最后一个描述符

// uint8_t		gdt_ptr[6];	/* 0~15:Limit  16~47:Base */
// DESCRIPTOR	gdt[GDT_SIZE];
// uint8_t		idt_ptr[6];	/* 0~15:Limit  16~47:Base */
// GATE		idt[IDT_SIZE];
// TSS			tss;

#define SEG_32	0x4000	//32 位段
#define SEG_LIMIT_4K	0x8000   //段界限粒度为 4K 字节

#define SEG_DPL0		0x00	//DPL = 0
#define SEG_DPL1    	0x20	//DPL = 1
#define SEG_DPL2   	    0x40	//DPL = 2
#define SEG_DPL3		0x60	 //DPL = 3

#define SEG_DR		    0x90	//存在的只读数据段类型值
#define SEG_DRW			0x92	//存在的可读写数据段属性值
#define SEG_DRWA		0x93	//存在的已访问可读写数据段类型值
#define SEG_C			0x98	//存在的只执行代码段属性值
#define SEG_CR			0x9A	//存在的可执行可读代码段属性值
#define SEG_CCO			0x9C	//存在的只执行一致代码段属性值
#define SEG_CCOR		0x9E	//存在的可执行可读一致代码段属性值

#define SEG_LDT	        0x82	//局部描述符表段类型值
#define SEG_TaskGate    0x85	//任务门类型值
#define SEG_386TSS		0x89    //386 任务状态段类型值
#define SEG_CGate       0x8C	//调用门类型值
#define SEG_IGate		0x8E	//中断门类型值
#define SEG_TGate		0x8F	//陷阱门类型值

//GDT 选择子

#define SelectorCode 	0x08 // 1
#define SelectorData 	0x10 // 2
#define SelectorVideo 	0x18 // 3
#define SelectorTSS		0x20 // 4
#define SelectorLDT		0x28 // 5

#define PL_TASK	1

#define LDT_TI	0x4
#define GDT_TI	0x0;



void init_gdt_dspt(DESCRIPTOR * dspt,uint32_t base, uint32_t limit, uint16_t attr);

void init_idt_dspt(GATE * dspt, int_handler addr, uint16_t selector, uint8_t attr, uint8_t dcount);

uint32_t seg_to_phyaddr(uint16_t seg);

#endif