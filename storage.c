//
// Created by zuma on 14.02.19.
//

#include "storage.h"

/**
 * This example shows the default SPIFFS configuration when SPIFFS is
 * configured in compile-time (SPIFFS_SINGLETON = 1).
 *
 * To configure SPIFFS in run-time uncomment SPIFFS_SINGLETON in the Makefile
 * and replace the commented esp_spiffs_init in the code below.
 *
 */

void example_read_file_posix()
{
    const int buf_size = 0xFF;
    uint8_t buf[buf_size];

    int fd = open("404.html", O_RDONLY);
    if (fd < 0) {
        printf("Error opening file\n");
        return;
    }

    int read_bytes = read(fd, buf, buf_size);
    printf("Read %d bytes\n", read_bytes);

    buf[read_bytes] = '\0';    // zero terminate string
    printf("Data: %s\n", buf);

    close(fd);
}

void example_read_file_spiffs()
{
    const int buf_size = 0xFF;
    uint8_t buf[buf_size];

    spiffs_file fd = SPIFFS_open(&fs, "other.txt", SPIFFS_RDONLY, 0);
    if (fd < 0) {
        printf("Error opening file\n");
        return;
    }

    int read_bytes = SPIFFS_read(&fs, fd, buf, buf_size);
    printf("Read %d bytes\n", read_bytes);

    buf[read_bytes] = '\0';    // zero terminate string
    printf("Data: %s\n", buf);

    SPIFFS_close(&fs, fd);
}

void example_write_file()
{
    uint8_t buf[] = "Example data, written by ESP8266";

    int fd = open("other.txt", O_WRONLY|O_CREAT, 0);
    if (fd < 0) {
        printf("Error opening file\n");
        return;
    }

    int written = write(fd, buf, sizeof(buf));
    printf("Written %d bytes\n", written);

    close(fd);
}

void example_fs_info()
{
    uint32_t total, used;
    SPIFFS_info(&fs, &total, &used);
    printf("Total: %d bytes, used: %d bytes", total, used);
}