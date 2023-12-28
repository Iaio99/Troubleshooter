#pragma once

void get_disk_info(const char *path);

void list_partitions(blkid_partlist partlist, blkid_probe pr);
void get_disk_info(struct udev_device *device);
void list_disks();