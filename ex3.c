#include <stdio.h>
#include <stdlib.h>
#include <mpeg2dec/mpeg2.h>
#include <SDL.h>

int main(int argc, char *argv[]) {
    FILE *file;
    uint8_t buffer[4096];
    size_t bytes_read;
    mpeg2dec_t *decoder;
    const mpeg2_info_t *info;
    mpeg2_state_t state;

    // Open the MPEG-2 video file
    file = fopen(argv[1], "rb");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", argv[1]);
        return 1;
    }

    // Initialize the MPEG-2 decoder
    decoder = mpeg2_init();
    if (!decoder) {
        fprintf(stderr, "Could not initialize MPEG-2 decoder\n");
        return 1;
    }

    // Get the decoder information
    info = mpeg2_info(decoder);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("Video Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, info->sequence->width, info->sequence->height, SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // Create an SDL renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    // Main decoding loop
    while (1) {
        // Read data from the file into the buffer
        bytes_read = fread(buffer, 1, sizeof(buffer), file);
        if (bytes_read <= 0)
            break;

        // Decode the data
        mpeg2_buffer(decoder, buffer, buffer + bytes_read);
        state = mpeg2_parse(decoder);

        // Handle the different decoding states
        switch (state) {
            case STATE_SEQUENCE:
                // A new sequence has started
                break;
            case STATE_PICTURE:
                // A new picture is ready to be decoded
                break;
            case STATE_SLICE:
                // A new slice of the picture is ready
                // Display the decoded frame
                if (info->display_fbuf) {
                    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, info->sequence->width, info->sequence->height);
                    SDL_UpdateTexture(texture, NULL, info->display_fbuf->buf[0], info->sequence->width * 3);
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    SDL_DestroyTexture(texture);
                }
                break;
            default:
                break;
        }
    }

    // Clean up
    mpeg2_close(decoder);
    fclose(file);

    return 0;
}
