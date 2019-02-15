cmake_minimum_required(VERSION 3.10)
project(esp8266_spiffs)


set(CMAKE_CXX_STANDARD 11)

set(SPIFF_DIR ${ESP_OPEN_RTOS_DIR}/extras/spiffs)

file(GLOB LIB_SPIFFS_COMMON_SRC ${SPIFF_DIR}/spiffs/src/*.c)

file(GLOB LIB_SPIFFS_SRC ${SPIFF_DIR}/*.c)

add_library(spiffs STATIC ${LIB_SPIFFS_SRC} ${LIB_SPIFFS_COMMON_SRC})

target_compile_options(spiffs PUBLIC ${COMMON_FLAGS}
    -DSPIFFS_SINGLETON=0
    -DSPIFFS_BASE_ADDR=0x200000
    -DSPIFFS_SIZE=0x10000
    -DSPIFFS_LOG_PAGE_SIZE=0x100
    -DSPIFFS_LOG_BLOCK_SIZE=0x2000
    )



add_custom_target(mkspiffs)
add_custom_command(TARGET mkspiffs
        POST_BUILD
        COMMENT "create mkspiffs"
        COMMAND gcc -I${SPIFF_DIR} -DSPIFFS_SINGLETON=0   -c -o mkspiffs.o ${SPIFF_DIR}/mkspiffs/mkspiffs.c
        COMMAND gcc -I${SPIFF_DIR} -DSPIFFS_SINGLETON=0   -c -o spiffs_hydrogen.o ${SPIFF_DIR}/spiffs/src/spiffs_hydrogen.c
        COMMAND gcc -I${SPIFF_DIR} -DSPIFFS_SINGLETON=0   -c -o spiffs_cache.o ${SPIFF_DIR}/spiffs/src/spiffs_cache.c
        COMMAND gcc -I${SPIFF_DIR} -DSPIFFS_SINGLETON=0   -c -o spiffs_gc.o ${SPIFF_DIR}/spiffs/src/spiffs_gc.c
        COMMAND gcc -I${SPIFF_DIR} -DSPIFFS_SINGLETON=0   -c -o spiffs_check.o ${SPIFF_DIR}/spiffs/src/spiffs_check.c
        COMMAND gcc -I${SPIFF_DIR} -DSPIFFS_SINGLETON=0   -c -o spiffs_nucleus.o ${SPIFF_DIR}/spiffs/src/spiffs_nucleus.c
        COMMAND gcc   mkspiffs.o spiffs_hydrogen.o spiffs_cache.o spiffs_gc.o spiffs_check.o spiffs_nucleus.o   -o mkspiffs
        )

#add_custom_target(make_spiffs_image)
#add_dependencies(make_spiffs_image mkspiffs)
#add_custom_command(TARGET make_spiffs_image
#	POST_BUILD
#	COMMENT "create spiffs image"
#	WORKING_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}"
#	COMMAND  ${CMAKE_CURRENT_BINARY_DIR}/mkspiffs -D ../httpd/fsdata/fs -f ${CMAKE_CURRENT_BINARY_DIR}/spiffs.bin -s 65536 -p 256 -b 8192
#)


target_include_directories(spiffs PUBLIC
            ${ESP_OPEN_RTOS_DIR}/extras/spiffs
            ${ESP_OPEN_RTOS_DIR}/extras/spiffs/spiffs/src
            ${ESP_OPEN_RTOS_DIR}/include
            ${ESP_OPEN_RTOS_DIR}/libc/xtensa-lx106-elf/include
            ${FREE_RTOS}/include
            ${FREE_RTOS}/portable/esp8266
            ${LWIP_DIR}/include
            ${ESP_OPEN_RTOS_DIR}/lwip/include
            ${LWIP_DIR}/include/compat/posix
            ${LWIP_DIR}/include/ipv4
            ${LWIP_DIR}/include/ipv4/lwip
            ${LWIP_DIR}/include/lwip
            ${ESP_OPEN_RTOS_DIR}/core/include
            ${ESP_OPEN_RTOS_DIR}/open_esplibs/include
            )

