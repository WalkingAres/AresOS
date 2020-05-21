#ifndef PM_H
#define PM_H

#include "def.h"
//����GDT IDT��ص����ݽṹ

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
	uint8_t	dcount;		/* ���ֶ�ֻ�ڵ���������������Ч�����������
				   �����ŵ����ӳ���ʱ������Ȩ����ת���Ͷ�ջ
				   �ĸı䣬��Ҫ������ջ�еĲ������Ƶ��ڲ�
				   ��ջ����˫�ּ����ֶξ�������˵���������
				   ����ʱ��Ҫ���Ƶ�˫�ֲ�����������*/
	uint8_t	    attr;		/* P(1) DPL(2) DT(1) TYPE(4) */
	uint16_t    offset_high;	/* Offset High */
}GATE;

uint32_t    gdt_pos;//ָ��������һ��������

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