#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define GPIO_MAGIC 'G'

#define GPIO_EXPORT _IOW(GPIO_MAGIC, 1, int)
#define GPIO_SET_DIR _IOW(GPIO_MAGIC, 2, int)
#define GPIO_WRITE _IOW(GPIO_MAGIC, 3, int)
#define GPIO_READ _IOR(GPIO_MAGIC, 4, int)

struct gpio_data {
    int pin;
    int value;
};

int main()
{
    int fd;

    struct gpio_data data;
    struct gpio_data read_back;

    fd = open("/dev/gpioioctl", O_RDWR);

    if (fd < 0) {
        perror("open failed");
        return -1;
    }

    data.pin = 17;
    ioctl(fd, GPIO_EXPORT, &data);

    data.value = 1;
    ioctl(fd, GPIO_SET_DIR, &data);

    data.value = 1;
    ioctl(fd, GPIO_WRITE, &data);

    printf("GPIO set HIGH\n");

    ioctl(fd, GPIO_READ, &read_back);

    printf("GPIO read value = %d\n", read_back.value);

    data.value = 0;
    ioctl(fd, GPIO_WRITE, &data);

    printf("GPIO set LOW\n");

    ioctl(fd, GPIO_READ, &read_back);

    printf("GPIO read value = %d\n", read_back.value);

    close(fd);

    return 0;
}
