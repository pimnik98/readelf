#include "tty.h"
#include "file.h"
#include "stdint.h"
#include "printf.h"
#define EI_NIDENT 16

// Заголовок ELF файла
typedef struct {
    unsigned char e_ident[EI_NIDENT]; // Сигнатура идентификации
    unsigned short e_type;            // Тип объектного файла
    unsigned short e_machine;         // Тип архитектуры
    unsigned int e_version;           // Версия объектного файла
    unsigned int e_entry;             // Начальный адрес исполняемого кода
    unsigned int e_phoff;             // Смещение таблицы программных заголовков
    unsigned int e_shoff;             // Смещение таблицы секций
    unsigned int e_flags;             // Флаги
    unsigned short e_ehsize;          // Размер заголовка
    unsigned short e_phentsize;       // Размер записи таблицы программных заголовков
    unsigned short e_phnum;           // Число записей таблицы программных заголовков
    unsigned short e_shentsize;       // Размер записи таблицы секций
    unsigned short e_shnum;           // Число записей таблицы секций
    unsigned short e_shstrndx;        // Индекс секции со строками
} Elf32_Ehdr;

int main(int argc, char* argv[]) {
    _tty_puts("ReadELF for SayoriOS\n");
    if (argc < 2) {
        printf("Использование: %s <elf-файл>\n", argv[0]);
        return 1;
    }

    printf("Попытка открыть файл %s!\n", argv[1]);

    int fd = fd_open(argv[1], "r");
    if (fd == -1){
        printf("Извините, не удалось открыть файл!\n");
        return 1;
    }
    Elf32_Ehdr header;
    fd_read(fd, sizeof(Elf32_Ehdr), 1, &header);

    fd_close(fd);

    if (
            header.e_ident[0] != 0x7f ||
            header.e_ident[1] != 0x45 ||
            header.e_ident[2] != 0x4c ||
            header.e_ident[3] != 0x46
    ) {
        printf("Получен следующий ответ: %x | %x | %x | %x\n", header.e_ident[0], header.e_ident[1], header.e_ident[2], header.e_ident[3]);
        printf("Извините, но данный файл не является ELF!\n");
        return 1;
    }

    // Выводим информацию из заголовка ELF
    printf("Тип:                     0x%x\n", header.e_type);
    printf("Архитектура:             0x%x\n", header.e_machine);
    printf("Версия ELF:              0x%x\n", header.e_version);
    printf("Точка входа в ELF-файл:  0x%x\n", header.e_entry);
    printf("Флаги:                   0x%x\n", header.e_flags);
    printf("Смещение начала заголовков программ: %u (от начала файла)\n", header.e_phoff);
    printf("Смещение начала заголовков секций: %u (от начала файла)\n", header.e_shoff);
    printf("Размер заголовка ELF-файла:  %u (байтов)\n", header.e_ehsize);
    printf("Размер записи таблицы заголовков программы: %u (байтов)\n", header.e_phentsize);
    printf("Количество записей в таблице заголовков программы: %u\n", header.e_phnum);
    printf("Размер записи таблицы заголовков секций: %u (байтов)\n", header.e_shentsize);
    printf("Количество записей в таблице заголовков секций: %u\n", header.e_shnum);
    printf("Индекс таблицы строк в заголовке секции: %u\n", header.e_shstrndx);
    return 0;
}
