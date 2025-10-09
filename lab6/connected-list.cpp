#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string>

// Функция для получения серийного номера устройства
std::string get_serial_number(libusb_device *dev) {
    libusb_device_handle *handle = NULL;
    int r;
    char serial[256] = {0};
    
    // Пытаемся открыть устройство
    r = libusb_open(dev, &handle);
    if (r != 0) {
        return "Не удалось открыть устройство";
    }
    
    // Получаем дескриптор устройства
    struct libusb_device_descriptor desc;
    r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
        libusb_close(handle);
        return "Ошибка получения дескриптора";
    }
    
    // Проверяем наличие серийного номера
    if (desc.iSerialNumber == 0) {
        libusb_close(handle);
        return "Серийный номер отсутствует";
    }
    
    // Получаем серийный номер в ASCII формате
    r = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, 
                                          (unsigned char*)serial, sizeof(serial));
    libusb_close(handle);
    
    if (r < 0) {
        return "Ошибка чтения серийного номера";
    }
    
    return std::string(serial);
}

int main() {
    libusb_device **devs; // указатель на указатель на устройство
    libusb_context *ctx = NULL; // контекст сессии
    int r; // для возвращаемых значений
    ssize_t cnt; // количество найденных устройств
    int i = 0;

    // Инициализация библиотеки libusb
    r = libusb_init(&ctx);
    if (r < 0) {
        printf("Ошибка инициализации libusb: %s\n", libusb_error_name(r));
        return 1;
    }

    // Получение списка устройств
    cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        printf("Ошибка получения списка устройств: %s\n", libusb_error_name(cnt));
        libusb_exit(ctx);
        return 1;
    }

    printf("Найдено устройств: %zd\n\n", cnt);

    // Перебор устройств
    while ((devs[i]) != NULL) {
        struct libusb_device_descriptor desc;
        r = libusb_get_device_descriptor(devs[i], &desc);
        if (r < 0) {
            printf("Ошибка получения дескриптора устройства: %s\n", libusb_error_name(r));
            i++;
            continue;
        }

        printf("Устройство %d:\n", i + 1);
        printf("  Класс: 0x%02x\n", desc.bDeviceClass);
        printf("  Vendor ID: 0x%04x\n", desc.idVendor);
        printf("  Product ID: 0x%04x\n", desc.idProduct);
        
        // Получаем и выводим серийный номер
        std::string serial = get_serial_number(devs[i]);
        printf("  Серийный номер: %s\n", serial.c_str());
        
        // Дополнительная информация о классе устройства
        printf("  Дополнительная информация:\n");
        printf("    - Код класса устройства: %d\n", desc.bDeviceClass);
        printf("    - Код подкласса: %d\n", desc.bDeviceSubClass);
        printf("    - Код протокола: %d\n", desc.bDeviceProtocol);
        printf("    - Версия USB: %d.%d%d\n", 
               (desc.bcdUSB >> 8) & 0xFF, 
               (desc.bcdUSB >> 4) & 0x0F,
               desc.bcdUSB & 0x0F);
        printf("\n");
        i++;
    }

    // Освобождение списка устройств
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
    return 0;
}
