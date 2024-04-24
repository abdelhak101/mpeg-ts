#include <stdio.h>

#define PES_START_CODE 0x000001
#define VIDEO_STREAM_ID 0xE0

void extract_iframes_from_pes(unsigned char* pes_packet, unsigned int pes_packet_size) {
    unsigned int start_code_prefix = (pes_packet[0] << 16) | (pes_packet[1] << 8) | pes_packet[2];
    unsigned char stream_id = pes_packet[3];

    if (start_code_prefix == PES_START_CODE && stream_id == VIDEO_STREAM_ID) {
        // This is a video PES packet
        for (unsigned int i = 0; i < pes_packet_size - 4; ++i) {
            unsigned int code = (pes_packet[i] << 24) | (pes_packet[i+1] << 16) | (pes_packet[i+2] << 8) | pes_packet[i+3];
            if (code == 0x00000100) {
                // This is a picture start code
                unsigned char frame_type = (pes_packet[i+5] & 0x38) >> 3;
                if (frame_type == 1) {
                    printf("Found an I-frame at position %u\n", i);
                    // TODO: Extract the I-frame
                }
            }
        }
    }
}
