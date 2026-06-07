---

### 2. `driver.c`
This is the core C code we wrote earlier. 

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// This struct perfectly matches the FAT12 boot sector blueprint.
// #pragma pack(push, 1) tells the compiler NOT to add padding between variables,
// ensuring our struct maps perfectly 1-to-1 with the raw disk bytes.
#pragma pack(push, 1)
struct BootSector {
    uint8_t  jump[3];             // Bytes 0-2
    char     oem_name[8];         // Bytes 3-10
    uint16_t bytes_per_sector;    // Bytes 11-12
    uint8_t  sectors_per_cluster; // Byte 13
    uint16_t reserved_sectors;    // Bytes 14-15
    uint8_t  fat_count;           // Byte 16
    uint16_t root_dir_entries;    // Bytes 17-18
    uint16_t total_sectors_short; // Bytes 19-20
    uint8_t  media_descriptor;    // Byte 21
    uint16_t fat_size_sectors;    // Bytes 22-23
    uint16_t sectors_per_track;   // Bytes 24-25
    uint16_t number_of_heads;     // Bytes 26-27
    uint32_t hidden_sectors;      // Bytes 28-31
    uint32_t total_sectors_long;  // Bytes 32-35
    
    // Extended FAT12/16 Boot Record
    uint8_t  drive_number;        // Byte 36
    uint8_t  reserved1;           // Byte 37
    uint8_t  boot_signature;      // Byte 38
    uint32_t volume_id;           // Bytes 39-42
    char     volume_label[11];    // Bytes 43-53
    char     fs_type[8];          // Bytes 54-61
};
#pragma pack(pop)

int main() {
    // Open our raw drive as a binary stream
    FILE *disk = fopen("floppy.img", "rb"); 
    if (!disk) {
        printf("Error: Could not mount disk! Run the disk creation steps first.\n");
        return 1;
    }

    struct BootSector boot;
    
    // Read the first 62 bytes of the file directly into our blueprint struct
    fread(&boot, sizeof(struct BootSector), 1, disk);

    printf("\n=== BARE-METAL DRIVER INITIALIZED ===\n");
    printf("Raw disk bytes successfully mapped to C structures.\n\n");
    
    printf("OEM Name:         %.8s\n", boot.oem_name);
    printf("Volume Label:     %.11s\n", boot.volume_label);
    printf("File System:      %.8s\n", boot.fs_type);
    printf("Bytes per Sector: %d\n", boot.bytes_per_sector);
    printf("Sectors/Cluster:  %d\n", boot.sectors_per_cluster);
    printf("=====================================\n\n");
    
    fclose(disk);
    return 0;
}
