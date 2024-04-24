#include <mpeg2dec/mpeg2.h>

void decode_mpeg2(unsigned char *start, unsigned char *end) {
    const mpeg2_info_t *info;
    mpeg2dec_t *decoder;
    decoder = mpeg2_init();
    if (decoder == NULL) {
        fprintf(stderr, "Could not allocate a decoder object.\n");
        exit(1);
    }
    info = mpeg2_info(decoder);
    while (start < end) {
        start = mpeg2_buffer(decoder, start, end);
        while (1) {
            int state = mpeg2_parse(decoder);
            switch (state) {
                case STATE_BUFFER:
                    return;
                case STATE_SEQUENCE:
                    // handle sequence header
                    break;
                case STATE_PICTURE:
                    // handle picture header
                    break;
                case STATE_SLICE:
                    // handle slice data
                    break;
                default:
                    break;
            }
        }
    }
    mpeg2_close(decoder);
}
