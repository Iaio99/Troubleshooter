"""DOC"""
import os
import psutil

from psutil._common import bytes2human

def get_disk_info():
    "DOC"
    disk_info = []

    templ = "%-17s %8s %9s %9s %9s"
    partitions = psutil.disk_partitions()

    print(templ % ("Device", "Total", "Type", "Mount", "Label"))

    for part in partitions:
        if os.name == 'nt':
            if 'cdrom' in part.opts or part.fstype == '':
                # skip cd-rom drives with no disk in it; they may raise
                # ENOENT, pop-up a Windows GUI error for a non-ready
                # partition or just hang.
                continue

        device = part.device
        mountpoint = part.mountpoint
        partition_usage = psutil.disk_usage(mountpoint)
        total_size = partition_usage.total
        label = psutil.disk_partitions(device)[0].device

        print(templ % (
            device,
            bytes2human(total_size),
            part.fstype,
            part.mountpoint,
            label))

    return disk_info
