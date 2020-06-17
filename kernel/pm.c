#include "pm.h"
#include "int.h"
#include "global.h"

void init_gdt_dspt(DESCRIPTOR * dspt,uint32_t base, uint32_t limit, uint16_t attr) {
    dspt->limit_low = limit & 0x0ffff;
    dspt->base_low = base & 0x0ffff;
    dspt->base_mid = (base >> 16) & 0x0ff;
    dspt->attr1 = attr & 0x0ff;
    dspt->limit_high_attr2 = ((limit >> 16) & 0x0f) | (((attr >> 8) & 0x0f) << 4);
    dspt->base_high = (base >> 24) & 0x0ff;
}

void init_idt_dspt(GATE * dspt, int_handler addr, uint16_t selector, uint8_t attr, uint8_t dcount){
    uint32_t offset = (uint32_t *)addr;
    dspt->offset_low = offset & 0x0ffff;
    dspt->selector = selector;
    dspt->dcount = dcount;
    dspt->attr = attr;
    dspt->offset_high = (offset >> 16) & 0x0ffff;
}

uint32_t seg_to_phyaddr(uint16_t seg) {
    DESCRIPTOR *p = &(gdt[seg>>3]);
    return (p->base_high<<24 | p->base_mid << 16 | p->limit_low );
}