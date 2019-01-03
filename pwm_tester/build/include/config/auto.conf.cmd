deps_config := \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/app_trace/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/aws_iot/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/bt/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/driver/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/esp32/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/esp_adc_cal/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/esp_event/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/esp_http_client/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/esp_http_server/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/ethernet/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/fatfs/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/freemodbus/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/freertos/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/heap/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/libsodium/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/log/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/lwip/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/mbedtls/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/mdns/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/mqtt/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/nvs_flash/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/openssl/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/pthread/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/spi_flash/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/spiffs/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/tcpip_adapter/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/unity/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/vfs/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/wear_levelling/Kconfig \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/app_update/Kconfig.projbuild \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/penguin/Documents/Programs/esp32/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/penguin/Documents/Programs/esp32/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_TARGET)" "esp32"
include/config/auto.conf: FORCE
endif
ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
