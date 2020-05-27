#ifndef PM_H
#define PM_H

#include "def.h"
#include "int.h"

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

#define SEG_32	0x4000	//32 λ��
#define SEG_LIMIT_4K	0x8000   //�ν�������Ϊ 4K �ֽ�

#define SEG_DPL0		0x00	//DPL = 0
#define SEG_DPL1    	0x20	//DPL = 1
#define SEG_DPL2   	    0x40	//DPL = 2
#define SEG_DPL3		0x60	 //DPL = 3

#define SEG_DR		    0x90	//���ڵ�ֻ�����ݶ�����ֵ
#define SEG_DRW			0x92	//���ڵĿɶ�д���ݶ�����ֵ
#define SEG_DRWA		0x93	//���ڵ��ѷ��ʿɶ�д���ݶ�����ֵ
#define SEG_C			0x98	//���ڵ�ִֻ�д��������ֵ
#define SEG_CR			0x9A	//���ڵĿ�ִ�пɶ����������ֵ
#define SEG_CCO			0x9C	//���ڵ�ִֻ��һ�´��������ֵ
#define SEG_CCOR		0x9E	//���ڵĿ�ִ�пɶ�һ�´��������ֵ

#define SEG_LDT	        0x82	//�ֲ��������������ֵ
#define SEG_TaskGate    0x85	//����������ֵ
#define SEG_386TSS		0x89    //386 ����״̬������ֵ
#define SEG_CGate       0x8C	//����������ֵ
#define SEG_IGate		0x8E	//�ж�������ֵ
#define SEG_TGate		0x8F	//����������ֵ


//GDT ѡ����

#define SelectorCode 8
#define SelectorData 16
#define SelectorVideo 24

void init_gdt_dspt(DESCRIPTOR * dspt,uint32_t base, uint32_t limit, uint16_t attr);

void init_idt_dspt(GATE * dspt, int_handler addr, uint16_t selector, uint8_t attr, uint8_t dcount);


#endif