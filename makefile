OBJS = $(addsuffix .o,$(patsubst %,bin/%,$(wildcard kernel/*)))
NAME = rxchit
INCLUDES = include/

bin/%.S.o: %.S
	aarch64-none-elf-gcc $(addprefix -I,$(INCLUDES)) -D__ASSEMBLY__ -c -o $@ $^

bin/%.c.o: %.c
	aarch64-none-elf-gcc $(addprefix -I,$(INCLUDES)) -ffreestanding -O2 -Wall -Wextra -c -o $@ $^

bin/%.cpp.o: %.cpp
	aarch64-none-elf-g++ $(addprefix -I,$(INCLUDES)) -ffreestanding -fno-exceptions -fno-rtti -O2 -Wall -Wextra -c -o $@ $^

all: $(OBJS)
	aarch64-none-elf-g++ -T linker.ld -ffreestanding -O2 -nostdlib -lgcc -o bin/$(NAME).elf $^
	aarch64-none-elf-objcopy bin/$(NAME).elf -O binary sysroot/kernel8.img

setup:
	mkdir ./bin
	mkdir ./bin/kernel

	mkdir ./sysroot

clean:
	find bin/* -type f -delete
