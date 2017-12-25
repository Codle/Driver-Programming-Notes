obj-m :=char_dev.o
chardevmodule-objs :=module
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
		rm -rf *.o .cmd *.ko *.mod.c .tmp_versions *.order *.symvers .*