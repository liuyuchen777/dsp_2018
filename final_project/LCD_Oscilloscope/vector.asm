

   .mmregs
   .sect"vectors"
   .ref jump
   .ref start
   .def reset

k_stack_size    .set    200
k_stack         .usect  "stack_section",k_stack_size
system_stack    .set    k_stack+k_stack_size

reset:          bd     start
                stm    #system_stack,sp

nmi:            rete
                nop
				nop
				nop
				;software interrupts
sint17        .space 4*16
sint18        .space 4*16
sint19        .space 4*16
sint20        .space 4*16
sint21        .space 4*16
sint22        .space 4*16
sint23        .space 4*16
sint24        .space 4*16
sint25        .space 4*16
sint26        .space 4*16
sint27        .space 4*16
sint28        .space 4*16
sint29        .space 4*16
sint30        .space 4*16


int0:    b  jump
         nop
		 nop
int1:    rete
         nop
		 nop
		 nop
int2:    rete
         nop
		 nop
		 nop
tint0:   rete
         nop
		 nop
		 nop
brint0:  rete
         nop
		 nop
		 nop
dmac0:   rete
         nop
		 nop
		 nop
dmac1:   rete
         nop
		 nop
		 nop
int3:   rete
         nop
		 nop
		 nop
hpint:   rete
         nop
		 nop
		 nop
dmac2:   rete
         nop
		 nop
		 nop
bxint1:   rete
         nop
		 nop
		 nop
dmac4:   rete
         nop
		 nop
		 nop
dmac5:   rete
         nop
		 nop
		 nop
		.end
