cmake_minimum_required(VERSION 3.10)
project(esp8266_spiffs)


set(CMAKE_CXX_STANDARD 11)

# TODO detect fsdata.c creation
set(HTTPD_DIR ${ESP_OPEN_RTOS_DIR}/extras/httpd)
file(GLOB LIB_httpd_SRC
        ${HTTPD_DIR}/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/fsdata/*.c)

add_custom_target(make_fsdata)
add_custom_command(TARGET make_fsdata
        PRE_BUILD
        COMMENT "make fsdata"
        COMMAND "./makefsdata"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/fsdata)

add_library(httpd STATIC ${LIB_httpd_SRC})
add_dependencies(httpd make_fsdata)

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