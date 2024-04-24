#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t sync_byte:8;
    uint32_t transport_error_indicator:1;
    uint32_t payload_unit_start_indicator:1;
    uint32_t transport_priority:1;
    uint32_t PID:13;
    uint32_t transport_scrambling_control:2;
    uint32_t adaptation_field_control:2;
    uint32_t continuity_counter:4;
} TSHeader;

void parse_header(uint8_t* buffer, TSHeader* header) {
    header->sync_byte = buffer[0];
    header->transport_error_indicator = (buffer[1] & 0x80) >> 7;
    header->payload_unit_start_indicator = (buffer[1] & 0x40) >> 6;
    header->transport_priority = (buffer[1] & 0x20) >> 5;
    header->PID = ((buffer[1] & 0x1F) << 8) | buffer[2];
    header->transport_scrambling_control = (buffer[3] & 0xC0) >> 6;
    header->adaptation_field_control = (buffer[3] & 0x30) >> 4;
    header->continuity_counter = buffer[3] & 0x0F;
}

int main() {
    uint8_t buffer[188];
    TSHeader header;

    // Assume that 'fp' is a file pointer to your MPEG-TS file
    FILE *fp = fopen("yourfile.ts", "rb");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return -1;
    }

    while (fread(buffer, 1, 188, fp) == 188) {
        parse_header(buffer, &header);

        // Now you can access the fields of the header
        printf("PID: %u\n", header.PID);
    }

    fclose(fp);
    return 0;
}
