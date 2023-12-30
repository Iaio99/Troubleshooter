#pragma once
#include <blkid/blkid.h>
#include <libudev.h>

static void list_partitions(blkid_partlist partlist, blkid_probe pr);
static void get_disk_info(struct udev_device *device);
extern void list_disks();