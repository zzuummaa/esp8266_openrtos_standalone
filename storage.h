//
// Created by zuma on 14.02.19.
//

#ifndef ESP8266_SPIFFS_STORAGE_H
#define ESP8266_SPIFFS_STORAGE_H

#include "fcntl.h"
#include "unistd.h"

#include "spiffs.h"
#include "esp_spiffs.h"

void example_read_file_posix();

void example_read_file_spiffs();

void example_write_file();

void example_fs_info();

#endif //ESP8266_SPIFFS_STORAGE_H
