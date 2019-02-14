cmake_minimum_required(VERSION 3.10)
project(esp8266_spiffs)


set(CMAKE_CXX_STANDARD 11)

set(HTTPD_DIR ${ESP_OPEN_RTOS_DIR}/extras/httpd)
file(GLOB LIB_httpd_SRC ${HTTPD_DIR}/*.c fsdata.c)

add_library(httpd STATIC ${LIB_httpd_SRC})

target_compile_options(httpd PUBLIC ${COMMON_FLAGS}
            -DLWIP_HTTPD_CGI
            -DLWIP_HTTPD_SSI
            )

target_include_directories(httpd PUBLIC
            ./
            ${ESP_OPEN_RTOS_DIR}/extras
            ${ESP_OPEN_RTOS_DIR}/extras/httpd
            ${ESP_OPEN_RTOS_DIR}/extras/httpd/include
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
# mbedtls includes
target_include_directories(httpd PUBLIC
        ${ESP_OPEN_RTOS_DIR}/extras
        ${ESP_OPEN_RTOS_DIR}/extras/mbedtls/mbedtls/include
        ${ESP_OPEN_RTOS_DIR}/extras/mbedtls/include
#        ${ESP_OPEN_RTOS_DIR}/include
#        ${ESP_OPEN_RTOS_DIR}/libc/xtensa-lx106-elf/include
#        ${FREE_RTOS}/include
#        ${FREE_RTOS}/portable/esp8266
#        ${LWIP_DIR}/include
#        ${ESP_OPEN_RTOS_DIR}/lwip/include
#        ${LWIP_DIR}/include/compat/posix
#        ${LWIP_DIR}/include/ipv4
#        ${LWIP_DIR}/include/ipv4/lwip
#        ${LWIP_DIR}/include/lwip
#        ${ESP_OPEN_RTOS_DIR}/core/include
#        ${ESP_OPEN_RTOS_DIR}/open_esplibs/include
        )