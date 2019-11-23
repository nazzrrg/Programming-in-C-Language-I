#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* .arch structure:
 * <header> - 16 bytes:
 *     file_type
 *     file size
 *     compression type
 *
 * <file header part>
 *     header size
 *     compressed file size
 *     file size
 *
 *   *file name with type*
 *
 *   *file contents*
 * etc....
 */

unsigned int bswap_32(unsigned int num) {
    return ((num>>24)&0xff) | // move byte 3 to byte 0
           ((num<<8)&0xff0000) | // move byte 1 to byte 2
           ((num>>8)&0xff00) | // move byte 2 to byte 1
           ((num<<24)&0xff000000); // byte 0 to byte 3
}

union arch_header {
    char buffer[12];

    struct {
        char archive_type[4];
        unsigned int archive_size;
        unsigned int compression_type;
    } data;
};

union file_header_part {
    char buffer[12];

    struct {
        unsigned int header_size;
        unsigned int file_size;
        unsigned int compressed_file_size;
    } data;
};

long long get_file_size(char* file) {
    FILE* f;
    f = fopen(file, "rb");
    if (f == NULL) perror("Error opening file for getting its size");

    fseek(f, 0, SEEK_END);

    long long result = ftell(f);

    fclose(f);
    return result;
}

void copy_file(FILE *from, FILE *to) {
    int c;
    while ((c = getc(from)) != EOF) putc(c, to);
}

void extract (char* input_file_name) {
    FILE* input_file;
    input_file = fopen(input_file_name, "rb");
    if (input_file == NULL) perror("Error reading archive");

    union arch_header arch_header; // read archive header
    if (!fread(arch_header.buffer, sizeof(char), 12, input_file)) perror("Error reading file");

    while (ftell(input_file) < arch_header.data.archive_size) {
        union file_header_part file_header_part; // read file header
        if (!fread(file_header_part.buffer, sizeof(char), 12, input_file)) perror("Error reading file");

        char *file_name = malloc(sizeof(char) * (file_header_part.data.header_size - 12)); // read file name
        if (!
        fread(file_name, sizeof(char), file_header_part.data.header_size - 12, input_file)) perror("Error reading file");

        FILE* output_file;
        output_file = fopen(file_name, "wb");
        if (output_file == NULL) perror("Error opening file for output");

        for (unsigned int i = 0; i < file_header_part.data.file_size; i++) {
            int c;
            c = getc(input_file);
            putc(c, output_file);
        }

        fclose(output_file);
    }
    fclose(input_file);
}

void create (char* file_name, int argc, char* argv[]) {
    FILE* output_file;
    output_file = fopen(file_name, "wb");
    if (output_file == NULL) perror("Error opening file");

    union arch_header arch_header; // form and write archive header
    arch_header.data.archive_type[0] = 'A';
    arch_header.data.archive_type[1] = 'R';
    arch_header.data.archive_type[2] = 'C';
    arch_header.data.archive_type[3] = 'H';
    arch_header.data.archive_size = 12;
    arch_header.data.compression_type = 0;
    for (int i = 3; i < argc; i++) {
        arch_header.data.archive_size += get_file_size(argv[i]) + 12 + strlen(argv[i]);
    }
    if (!fwrite(arch_header.buffer, sizeof(char), 12, output_file)) perror("Error writing to archive");

    for (int i = 3; i < argc; i++) {
        union file_header_part file_header_part; // form and write file header
        file_header_part.data.file_size = get_file_size(argv[i]);
        file_header_part.data.compressed_file_size = file_header_part.data.file_size;
        file_header_part.data.header_size = 12 + strlen(argv[i]);
        if (!fwrite(file_header_part.buffer, sizeof(char), 12, output_file)) perror("Error writing to archive");
        if (!fwrite(argv[i], sizeof(char), strlen(argv[i]), output_file)) perror("Error writing to archive");

        FILE* file;
        file = fopen(argv[i], "rb");
        if (file == NULL) perror("Error opening file for output");

        copy_file(file, output_file); // copy file into archive

        fclose(file);
    }
    fclose(output_file);
}

void list (char* input_file_name) {
    FILE* input_file;
    input_file = fopen(input_file_name, "rb");
    if (input_file == NULL) perror("Error opening file");

    union arch_header arch_header; // read archive header
    if (!fread(arch_header.buffer, sizeof(char), 12, input_file)) perror("Error reading file");

    while (ftell(input_file) < arch_header.data.archive_size) {
        union file_header_part file_header_part; // read file header
        if(!fread(file_header_part.buffer, sizeof(char), 12, input_file)) perror("Error reading file");

        char *file_name = malloc(sizeof(char) * (file_header_part.data.header_size - 12)); // read file name
        if(!fread(file_name, sizeof(char), file_header_part.data.header_size - 12, input_file)) perror("Error reading file");

        printf("%s\n", file_name);

        if(fseek(input_file, file_header_part.data.file_size, SEEK_CUR)) perror("Error reading file"); // skip file contents
    }
    fclose(input_file);
}

int main(int argc, char* argv[]) {
    //--filename=archive.arch --create sample1.txt sample2.txt sample3.bmp
    //--filename=archive.arch --extract
    //--filename=archive.arch --list

    char* file_name;//0 - exec file
    if (argc > 1) {
        file_name = strpbrk(argv[1], "=") + 1; //1 - file name

        switch (argv[2][2]) { //2 - command
            case 'e': { //extract - only 3 args possible
                if (argc != 3) {
                    printf("Error: too many arguments");
                    exit(EXIT_FAILURE);
                }
                extract(file_name);
                break;
            }
            case 'c': {
                create(file_name, argc, argv); //pass archive name and args for file names
                break;
            }
            case 'l': { //list - only 3 args possible
                printf("listing:\n");
                if (argc != 3) {
                    printf("Error: too many arguments");
                    exit(EXIT_FAILURE);
                }
                list(file_name);
                extract(file_name);
                break;
            }

        }
    } else {
        printf("Error: no file name found");
        exit(EXIT_FAILURE);
    }

    return 0;
}