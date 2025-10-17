#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cctype>

class USBInfoDatabase {
private:
    std::unordered_map<uint16_t, std::string> vendors;
    std::unordered_map<uint32_t, std::string> products; // key = (vendor_id << 16) | product_id

public:
    bool load_from_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        std::string line;
        uint16_t current_vendor = 0;
        size_t vendor_count = 0;
        size_t product_count = 0;

        while (std::getline(file, line)) {
            // Skip comments and empty lines
            if (line.empty() || line[0] == '#') {
                continue;
            }

            // Check if the line is a vendor (starts with 4 hex digits)
            if (line.length() >= 5 &&
                isxdigit(line[0]) && isxdigit(line[1]) &&
                isxdigit(line[2]) && isxdigit(line[3]) &&
                line[4] == ' ') {

                uint16_t vendor_id = static_cast<uint16_t>(std::stoul(line.substr(0, 4), nullptr, 16));
                std::string vendor_name = line.substr(5);
                vendors[vendor_id] = vendor_name;
                current_vendor = vendor_id;
                vendor_count++;
            }
            // Check if the line is a product (starts with tab + 4 hex digits)
            else if (line.length() >= 6 &&
                     line[0] == '\t' &&
                     isxdigit(line[1]) && isxdigit(line[2]) &&
                     isxdigit(line[3]) && isxdigit(line[4])) {

                uint16_t product_id = static_cast<uint16_t>(std::stoul(line.substr(1, 4), nullptr, 16));
                std::string product_name = line.substr(6);
                uint32_t key = (static_cast<uint32_t>(current_vendor) << 16) | product_id;
                products[key] = product_name;
                product_count++;
            }
        }

        file.close();
        printf("Загружено производителей: %zu, устройств: %zu\n", vendor_count, product_count);
        return true;
    }

    std::string get_vendor_name(uint16_t vendor_id) {
        auto it = vendors.find(vendor_id);
        if (it != vendors.end()) {
            return it->second;
        }
        return "Неизвестный производитель";
    }

    std::string get_product_name(uint16_t vendor_id, uint16_t product_id) {
        uint32_t key = (static_cast<uint32_t>(vendor_id) << 16) | product_id;
        auto it = products.find(key);
        if (it != products.end()) {
            return it->second;
        }
        return "Неизвестное устройство";
    }
};

USBInfoDatabase usb_db;

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

    r = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, (unsigned char*)serial, sizeof(serial));
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

    // Load USB ID database
    printf("Загрузка базы данных USB ID...\n");
    if (!usb_db.load_from_file("/usr/share/misc/usb.ids") &&
        !usb_db.load_from_file("/usr/share/hwdata/usb.ids") &&
        !usb_db.load_from_file("/var/lib/usbutils/usb.ids")) {
        printf("Предупреждение: Не удалось загрузить базу данных usb.ids\n");
        printf("Установите пакет usbutils или скачайте usb.ids вручную\n\n");
    }

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

        std::string vendor_name = usb_db.get_vendor_name(desc.idVendor);
        std::string product_name = usb_db.get_product_name(desc.idVendor, desc.idProduct);

        printf("Устройство %d:\n", i + 1);
        printf("  Класс: 0x%02x (%s)\n", desc.bDeviceClass, get_device_class_name(desc.bDeviceClass).c_str());
        printf("  Vendor ID: 0x%04x (%s)\n", desc.idVendor, vendor_name.c_str());
        printf("  Product ID: 0x%04x (%s)\n", desc.idProduct, product_name.c_str());

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


