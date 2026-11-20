cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lab0_http)

target_sources(app PRIVATE src/main.c)

# Each HTTP_SERVICE_DEFINE needs a matching iterable ROM section, named after
# the service, or its resource list fails to link.
zephyr_linker_sources(SECTIONS sections-rom.ld)
zephyr_linker_section(NAME http_resource_desc_iot_service
  KVMA RAM_REGION GROUP RODATA_REGION
)
