#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string>

// Функция для получения описания класса устройства
std::string get_device_class_name(uint8_t device_class) {
    switch(device_class) {
        case 0x00: return "Интерфейс-зависимый";
        case 0x01: return "Аудио";
        case 0x02: return "Сетевой";
        case 0x03: return "HID (Human Interface Device)";
        case 0x07: return "Принтер";
        case 0x08: return "Mass Storage";
        case 0x09: return "USB Hub";
        case 0x0A: return "CDC Data";
        case 0x0B: return "Smart Card";
        case 0x0D: return "Content Security";
        case 0x0E: return "Video";
        case 0x0F: return "Personal Healthcare";
        case 0x10: return "Audio/Video Devices";
        case 0xDC: return "Diagnostic Device";
        case 0xE0: return "Wireless Controller";
        case 0xEF: return "Miscellaneous";
        case 0xFE: return "Application Specific";
        case 0xFF: return "Vendor Specific";
        default: return "Неизвестный класс";
    }
}

// Функция для получения серийного номера устройства
std::string get_serial_number(libusb_device *dev) {
    libusb_device_handle *handle = NULL;
    int r;
    char serial[256] = {0};
    
    r = libusb_open(dev, &handle);
    if (r != 0) {
        return "Не удалось открыть устройство";
    }
    
    struct libusb_device_descriptor desc;
    r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
        libusb_close(handle);
        return "Ошибка получения дескриптора";
    }
    
    if (desc.iSerialNumber == 0) {
        libusb_close(handle);
        return "Серийный номер отсутствует";
    }
    
    r = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, 
                                          (unsigned char*)serial, sizeof(serial));
    libusb_close(handle);
    
    if (r < 0) {
        return "Ошибка чтения серийного номера";
    }
    
    return std::string(serial);
}

int main() {
    libusb_device **devs;
    libusb_context *ctx = NULL;
    int r;
    ssize_t cnt;
    int i = 0;

    r = libusb_init(&ctx);
    if (r < 0) {
        printf("Ошибка инициализации libusb: %s\n", libusb_error_name(r));
        return 1;
    }

    cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        printf("Ошибка получения списка устройств: %s\n", libusb_error_name(cnt));
        libusb_exit(ctx);
        return 1;
    }

    printf("=== ОБНАРУЖЕННЫЕ USB УСТРОЙСТВА ===\n");
    printf("Всего найдено устройств: %zd\n\n", cnt);

    while ((devs[i]) != NULL) {
        struct libusb_device_descriptor desc;
        r = libusb_get_device_descriptor(devs[i], &desc);
        if (r < 0) {
            printf("Ошибка получения дескриптора устройства\n");
            i++;
            continue;
        }

        printf("Устройство %d:\n", i + 1);
        printf("  Класс: 0x%02x (%s)\n", desc.bDeviceClass, get_device_class_name(desc.bDeviceClass).c_str());
        printf("  Vendor ID: 0x%04x\n", desc.idVendor);
        printf("  Product ID: 0x%04x\n", desc.idProduct);
        
        // Получаем информацию о порте
        uint8_t port = libusb_get_port_number(devs[i]);
        uint8_t bus = libusb_get_bus_number(devs[i]);
        printf("  Шина: %d, Порт: %d\n", bus, port);
        
        std::string serial = get_serial_number(devs[i]);
        printf("  Серийный номер: %s\n", serial.c_str());
        
        printf("  Дополнительная информация:\n");
        printf("    - Подкласс: 0x%02x\n", desc.bDeviceSubClass);
        printf("    - Протокол: 0x%02x\n", desc.bDeviceProtocol);
        printf("    - Версия USB: %d.%d%d\n", 
               (desc.bcdUSB >> 8) & 0xFF, 
               (desc.bcdUSB >> 4) & 0x0F,
               desc.bcdUSB & 0x0F);
        printf("\n");
        i++;
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
    return 0;
}