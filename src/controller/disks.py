"""DOC"""
import psutil

def get_disk_info():
    "DOC"
    disk_info = []

    partitions = psutil.disk_partitions()

    for partition in partitions:    
        device = partition.device
        mountpoint = partition.mountpoint
        try:
            partition_usage = psutil.disk_usage(mountpoint)
            total_size = partition_usage.total
            filesystem_type = partition.fstype
            label = psutil.disk_partitions(device)[0].device
        except Exception:
            total_size = "N/A"
            filesystem_type = "N/A"
            label = "N/A"

        disk_info.append({
            "Nome del dispositivo": device,
            "Punto di mount": mountpoint,
            "Filesystem": filesystem_type,
            "Etichetta della partizione": label,
            "Dimensione totale": total_size,
        })

    return disk_info
