#include <stdio.h>

#define TS_PACKET_SIZE 188
#define SYNC_BYTE 0x47

void extract_pes_from_mpegts(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    unsigned char ts_packet[TS_PACKET_SIZE];
    while (fread(ts_packet, 1, TS_PACKET_SIZE, file) == TS_PACKET_SIZE) {
        if (ts_packet[0] != SYNC_BYTE) {
            printf("Sync byte not found, not a valid TS packet\n");
            continue;
        }

        unsigned char payload_unit_start_indicator = (ts_packet[1] & 0x40) >> 6;
        unsigned short pid = ((ts_packet[1] & 0x1F) << 8) | ts_packet[2];

        if (payload_unit_start_indicator == 1) {
            // This TS packet contains the start of a new PES packet
            printf("Start of a new PES packet, PID: %u\n", pid);
            // TODO: Extract and decode PES packet
        }
    }

    fclose(file);
}

int main() {
    const char* filename = "yourfile.ts"; // replace with your filename
    extract_pes_from_mpegts(filename);
    return 0;
}
