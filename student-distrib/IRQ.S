#define ASM 1
#include "IRQ.h"

.global IntHandler_0,IntHandler_1,IntHandler_2,IntHandler_3,IntHandler_4,IntHandler_5,IntHandler_6,IntHandler_7
.global IntHandler_8,IntHandler_9,IntHandler_10,IntHandler_11,IntHandler_12,IntHandler_13,IntHandler_14
.global IntHandler_15,IntHandler_16,IntHandler_17,IntHandler_18,IntHandler_19,IntHandler_20,IntHandler_21
.global IntHandler_33,IntHandler_40
.global IntHandler, IntHandler_32 ,IntHandler_128

IntHandler:

    pushal
    cld
    call Interrupt
    popal

    iret

IntHandler_0:

    pushal
    cld
    call Interrupt_0
    popal

    iret

IntHandler_1:

    pushal
    cld
    call Interrupt_1
    popal

    iret

IntHandler_2:

    pushal
    cld
    call Interrupt_2
    popal

    iret

IntHandler_3:

    pushal
    cld
    call Interrupt_3
    popal

    iret

IntHandler_4:

    pushal
    cld
    call Interrupt_4
    popal

    iret

IntHandler_5:

    pushal
    cld
    call Interrupt_5
    popal

    iret

IntHandler_6:

    pushal
    cld
    call Interrupt_6
    popal

    iret

IntHandler_7:

    pushal
    cld
    call Interrupt_7
    popal

    iret

IntHandler_8:

    pushal
    cld
    call Interrupt_8
    popal
    addl $4,%esp
    iret

IntHandler_9:

    pushal
    cld
    call Interrupt_9
    popal

    iret

IntHandler_10:

    pushal
    cld
    call Interrupt_10
    popal
    addl $4,%esp
    iret

IntHandler_11:

    pushal
    cld
    call Interrupt_11
    popal
    addl $4,%esp
    iret

IntHandler_12:

    pushal
    cld
    call Interrupt_12
    popal
    addl $4,%esp
    iret

IntHandler_13:

    pushal
    cld
    call Interrupt_13
    popal
    addl $4, %esp
    iret

IntHandler_14:

    pushal
    cld
    call Interrupt_14
    popal
    addl $4,%esp
    iret

IntHandler_15:

    pushal
    cld
    call Interrupt_15
    popal

    iret

IntHandler_16:

    pushal
    cld
    call Interrupt_16
    popal

    iret

IntHandler_17:
    pushal
    cld

    call Interrupt_17
    popal

    iret

IntHandler_18:

    pushal
    cld
    call Interrupt_18
    popal

    iret

IntHandler_19:

    pushal
    cld
    call Interrupt_19
    popal

    iret

IntHandler_20:

    pushal
    cld
    call Interrupt_20
    popal

    iret

IntHandler_21:

    pushal
    cld
    call Interrupt_21
    popal

    iret

IntHandler_32:
    pushal
    cld
    call Interrupt_32
    popal
    iret

IntHandler_33:

    pushal
    cld
    call Interrupt_33
    popal

    iret

IntHandler_40:

    pushal
    cld
    call Interrupt_40
    popal
    iret

IntHandler_128:
    pushal   #check under control of debugger
    cld
    call Interrupt_128
    popal
    iret
