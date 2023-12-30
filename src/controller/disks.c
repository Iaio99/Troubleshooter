#include <stdio.h>
#include <libudev.h>
#include <stdlib.h>
#include <string.h>
#include <sys/vfs.h>
#include <errno.h>
#include <blkid/blkid.h>

#include "disks.h"
#include "../utils/io.h"

void list_partitions(blkid_partlist partlist, blkid_probe pr)
{
	int nparts;
	int i;
		nparts = blkid_partlist_numof_partitions(partlist);
		if (!nparts)
			goto done;
		
		printf("Number\t   Size UUID\t\t\t\t\t    Name\n");

		for (i = 0; i < nparts; i++) {
			const char *p;
			blkid_partition par = blkid_partlist_get_partition(partlist, i);

			printf("#%d: %10lluM",
				blkid_partition_get_partno(par),
				(unsigned long long) blkid_partition_get_size(par)/1024/2);
			
			p = blkid_partition_get_uuid(par);

			if (p)
				printf(" uuid='%s'", p);
			
			p = blkid_partition_get_name(par);
			
			if (p)
				printf(" name='%s'", p);

			putc('\n', stdout);
		}

		done:
		blkid_free_probe(pr);
	}


void get_disk_info(struct udev_device *device)
{
    	const char *devicePath = udev_device_get_devnode(device);

    	if (!devicePath) {
		print_error("Errore nell'ottenere il percorso del dispositivo\n");
		return;
    	}

    	const char *devType = udev_device_get_devtype(device);
    	
	if (devType && strcmp(devType, "disk") == 0) {
		printf("Disco: %s\n", devicePath);

    		blkid_probe pr;
		blkid_partlist partlist;
		blkid_parttable root_tab;
	
		pr = blkid_new_probe_from_filename(devicePath);

		if (!pr) {
			print_error("%s: failed to create a new libblkid probe\n\n",
					devicePath);
			return;
		}
		/* Binary interface */
		partlist = blkid_probe_get_partitions(pr);
		if (!partlist) {
			print_error("%s: failed to read partitions\n\n", devicePath);
			return;
		} 

		/*
		 * Print info about the primary (root) partition table
		 */
		root_tab = blkid_partlist_get_table(partlist);
		if (!root_tab)
			print_error("%s: does not contains any "
					 "known partition table\n\n", devicePath);

		printf("size: %jdG, sector size: %u, Partition Table Type: %s, id=%s\n---\n",
			(intmax_t)blkid_probe_get_size(pr)/1024/1024/1024,
			blkid_probe_get_sectorsize(pr),
			blkid_parttable_get_type(root_tab),
			blkid_parttable_get_id(root_tab));

		list_partitions(partlist, pr);
		printf("\n");
	}
}

void list_disks()
{
    struct udev *udev = udev_new();

    if (!udev) {
	print_error("Errore nell'inizializzazione di udev\n");
	return;
    }

    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "block");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;

    udev_list_entry_foreach(entry, devices) {
	const char *path = udev_list_entry_get_name(entry);
	struct udev_device *device = udev_device_new_from_syspath(udev, path);
	if (device) {
	    get_disk_info(device);
	    udev_device_unref(device);
	}
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udev);
}
