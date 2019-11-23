#include <stdio.h>
#include <stdlib.h>
#include "string.h"

/*
file structure:
    ID3v2/file identifier   "ID3"
    ID3v2 version           $03 00
    ID3v2 flags             %abc00000
    ID3v2 size              4 * %0xxxxxxx

    Frame ID       $xx xx xx xx (four characters)
    Size           $xx xx xx xx
    Flags          $xx xx

    <Frame contents>

    etc...
 */

unsigned int bswap_32(unsigned int num) {
    return ((num>>24)&0xff) | // move byte 3 to byte 0
           ((num<<8)&0xff0000) | // move byte 1 to byte 2
           ((num>>8)&0xff00) | // move byte 2 to byte 1
           ((num<<24)&0xff000000); // byte 0 to byte 3
}

void filecopy(FILE *fp, FILE *ofp) {
    int c;

    while ((c = getc(fp)) != EOF) putc(c, ofp);
}

union frame_header {
    char buffer[10];

    struct {
        unsigned char name[4]; // 4
        unsigned int size; // 4
        unsigned short flags; // 2
    } data;
};

union tag_header {
    char buffer[12];

    struct {
        unsigned short empty;
        unsigned char version[3]; //3 bytes
        unsigned char rev1; // 1
        unsigned char rev2; // 1
        unsigned char flags; // 1
        unsigned int size; // 4
    } data; //total of 10
};

void show(char* media_file_name) {
    FILE* media_file;
    media_file = fopen(media_file_name, "rb");

    fseek(media_file, 0, SEEK_SET);

    union tag_header tag_header;
    fread(tag_header.buffer + 2, sizeof(char), 10, media_file);// read tag header

    unsigned int tag_size = bswap_32(tag_header.data.size); // convert Indians

    printf("%sv%d.%d\n", tag_header.data.version, tag_header.data.rev1, tag_header.data.rev2); // print general info
    //printf("tag size: %d\n", tag_size);

    while (ftell(media_file) < tag_size + 10) {
        union frame_header frame_header;
        fread(frame_header.buffer, sizeof(char), 10, media_file); // read frame header

        printf("%s: ", frame_header.data.name);

        unsigned int frame_size = bswap_32(frame_header.data.size); // convert Indians

        unsigned char* frame_contents = malloc(sizeof(char) * frame_size);
        fread(frame_contents, sizeof(char), frame_size, media_file);// read frame contents

        for (unsigned int i = 0; i < frame_size; i++) { // print frame contents
            printf("%c", frame_contents[i]);
        }
        printf("\n");

        memset(frame_contents, 0, frame_size); //NULL the allocated piece of memory
        free(frame_contents);
    }
    fclose(media_file);
}

void set(char* media_file_name, char new_frame_name[4], char* new_frame_value) {
    FILE* media_file;
    media_file = fopen(media_file_name, "rb");

    union tag_header tag_header;
    fread(tag_header.buffer + 2, sizeof(char), 10, media_file); //read tag header
    unsigned int tag_size = bswap_32(tag_header.data.size);

    long long frame_to_change_pos = 0, frame_to_change_size = 0;

    while (ftell(media_file) < tag_size + 10) { //look for frame
        union frame_header frame_header;
        fread(frame_header.buffer, sizeof(char), 10, media_file);
        long long current_frame_size = bswap_32(frame_header.data.size);

        if (!strcmp(frame_header.data.name, new_frame_name)) {
            frame_to_change_pos = ftell(media_file) - 10;
            frame_to_change_size = current_frame_size;
            break;
        }
        fseek(media_file, current_frame_size, SEEK_CUR); // move to end of frame
    }

    if (frame_to_change_pos == 0) { //if not found, move return position = to end of all tags
        frame_to_change_pos = ftell(media_file);
    }

    unsigned int new_value_size = strlen(new_frame_value); //size of new_frame_value

    unsigned int new_tag_size = tag_size - frame_to_change_size + new_value_size; // new tag size = tag size - prev size + new size

    if (new_value_size == 0) { //if new new_frame_value is empty
        new_tag_size -= 10; //remove frame header from new tag size
    }

    char* media_file_copy_name;
    media_file_copy_name = "_tmpCopy.mp3";

    FILE* media_file_copy; // create a copy of file
    media_file_copy = fopen(media_file_copy_name, "wb");

    fseek(media_file, 0, SEEK_SET);
    fseek(media_file_copy, 0, SEEK_SET);
    filecopy(media_file, media_file_copy);

    fclose(media_file_copy);
    fclose(media_file);

    media_file_copy = fopen(media_file_copy_name, "rb"); // open files for rewriting media file
    media_file = fopen(media_file_name, "wb");

    tag_header.data.size = bswap_32(new_tag_size); // put new tag size into header
    fwrite(tag_header.buffer + 2, sizeof(char), 10, media_file); // write new tag header

    fseek(media_file_copy, 10, SEEK_SET); // move to beginning of tags in copy

    for(unsigned long long i = 0; i < frame_to_change_pos - 10; i++){ // copy everything before the changed frame
        int c;
        c = getc(media_file_copy);
        putc(c, media_file);
    }

    if (new_value_size) { //if new_frame_value to put exists
        union frame_header frame_header;
        frame_header.data.name[0] = new_frame_name[0]; // form header
        frame_header.data.name[1] = new_frame_name[1];
        frame_header.data.name[2] = new_frame_name[2];
        frame_header.data.name[3] = new_frame_name[3];
        frame_header.data.size = bswap_32(new_value_size);
        frame_header.data.flags = 0;
        fwrite(frame_header.buffer, sizeof(char), 10, media_file); // write frame header
    }

    fwrite(new_frame_value, sizeof(char), new_value_size, media_file); // write new frame new_frame_value

    fseek(media_file_copy, frame_to_change_pos + 10 + frame_to_change_size , SEEK_SET); //move to pos after changed tag in copy

    for(unsigned long long i = ftell(media_file); i < new_tag_size; i++) {// copy everything after changed
        unsigned short int c;
        c = getc(media_file_copy);
        putc(c, media_file);
    }

    printf("Frame set: %s -> \"%s\"\n", new_frame_name, new_frame_value);

    filecopy(media_file_copy, media_file); // copy mp3 body
    fclose(media_file);
    fclose(media_file_copy);
    remove(media_file_copy_name);
}

void get(char* media_file_name, char sought_frame_name[4]) {
    FILE* media_file;
    media_file = fopen(media_file_name, "rb");

    union tag_header tag_header;
    fread(tag_header.buffer + 2, sizeof(char), 10, media_file); //read tag header
    unsigned int tag_size = bswap_32(tag_header.data.size); // convert Indians

    while (ftell(media_file) < tag_size + 10) { //look for frame
        union frame_header frame_header;
        fread(frame_header.buffer, sizeof(char), 10, media_file);// read frame header

        long long current_frame_size = bswap_32(frame_header.data.size);

        if (!strcmp(frame_header.data.name, sought_frame_name)) {// if found
            printf("%s: ", frame_header.data.name);

            unsigned int frame_size = bswap_32(frame_header.data.size); // convert Indians

            unsigned char* frame_contents = malloc(sizeof(char) * frame_size);
            fread(frame_contents, sizeof(char), frame_size, media_file); // read frame contents

            for (unsigned int i = 0; i < frame_size; i++) {// print frame value
                printf("%c", frame_contents[i]);
            }
            printf("\n");

            free(frame_contents);
            fclose(media_file);
            return;
        }
        fseek(media_file, current_frame_size, SEEK_CUR); // move to end of frame
    }
    fclose(media_file);
    printf("No value found for %s!\n", sought_frame_name);
}

int main(int argc, char* argv[]) {
    char* filepath;
    filepath = strpbrk(argv[1],"=") + 1;
    for (int i = 2;i < argc; i++){
        if (!strcmp(argv[i], "--show")) {
            show(filepath);
            continue;
        }
        if (argv[i][2]=='g') {
            get(filepath, strpbrk(argv[i],"=") + 1);
            continue;
        }
        if (argv[i][2]=='s') {
            set(filepath, strpbrk(argv[i],"=") + 1, strpbrk(argv[i + 1], "=") + 1);
            continue;
        }
    }

    return 0;
}