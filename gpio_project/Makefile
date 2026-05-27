obj-m += gpio_ioctl_driver.o

KDIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

APP = gpio_user_app

all:
	make -C $(KDIR) M=$(PWD) modules
	gcc gpio_user_app.c -o $(APP)

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -f $(APP)

load:
	sudo insmod gpio_ioctl_driver.ko
	sudo mknod /dev/gpioioctl c $$(grep gpioioctl /proc/devices | awk '{print $$1}') 0
	sudo chmod 666 /dev/gpioioctl

unload:
	sudo rmmod gpio_ioctl_driver
	sudo rm -f /dev/gpioioctl

run:
	./$(APP)
