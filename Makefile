# Перед сборкой необходимо скомпилировать сдк
# Путь к SayoriSDK - это единственное что нужно указать.
SDK=../SayoriSDK/libc

INCLUDES=$(SDK)/include

NAMEOUT=readelf.elf

all:
	$(CC) -m32 -ffreestanding -I$(INCLUDES) -mno-red-zone -msse2 -nostdlib -fno-builtin -fno-stack-protector -O0 -c readelf.c -o readelf.o
	$(LD) -mno-pic -mno-pie -T$(SDK)/link.ld readelf.o $(SDK)/libsayori_c.a -m elf_i386 -o $(NAMEOUT)

clean:
	-rm $(NAMEOUT)
	-rm *.o
