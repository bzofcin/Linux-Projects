GCC		 	= gcc
CFLAGS	= -std=c99
LFLAGS	= 
PFLAGS	= -g -pthread

IO	= source/io_bound.c
CPU	= source/cpu_bound.c
PAR	= source/par_bound.c
NIC	= source/nic_bound.c

OUTPUT_IO 	= object/io_leib
OUTPUT_CPU	= object/cpu_leib
OUTPUT_PAR	= object/par_leib
OUTPUT_NIC	= object/nic_leib

io: $(IO)
	$(GCC) -o $(OUTPUT_IO) $(CFLAGS) $< $(LFLAGS)

cpu: $(CPU)
	$(GCC) -o $(OUTPUT_CPU) $(CFLAGS) $< $(LFLAGS)

nic: $(CPU)
	$(GCC) -o $(OUTPUT_NIC) $(CFLAGS) $< $(LFLAGS)

par: $(PAR)
	$(GCC) -o $(OUTPUT_PAR) $(CFLAGS) $(PFLAGS) $< $(LFLAGS)

.PHONY: clean
clean:
	-rm -f $(OUTPUT_IO) $(OUTPUT_CPU) $(OUTPUT_PAR)