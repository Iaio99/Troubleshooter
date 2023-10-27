"""DOC"""

import controller.disks

disk_info = controller.disks.get_disk_info()

for info in disk_info:
    print("Informazioni sul disco:")

    for key, value in info.items():
        print(f"{key}: {value}")

    print()
