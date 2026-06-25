// Needs includes for printing, integers, booleans, strings, and the C standard library.
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// Function to write the png. From https://iquilezles.org/articles/minipng64.
bool write_png_64x64( FILE *fp, const uint32_t pixels[] )
{
    // Nasty hex data. There isn't much of a better way, though...
    static const uint8_t binary[] = {
      0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,0x00,0x00,
      0x00,0x0d,0x49,0x48,0x44,0x52,0x00,0x00,0x00,0x40,
      0x00,0x00,0x00,0x40,0x08,0x06,0x00,0x00,0x00,0xaa,
      0x69,0x71,0xde,0x00,0x00,0x40,0x4b,0x49,0x44,0x41,
      0x54,0x08,0x1d,0x01,0x40,0x40,0xbf,0xbf,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x49,0x45,0x4e,0x44,0xae,0x42,0x60,0x82 };
    
    // Writing the file.
    if( !fwrite(binary,48,1,fp) ) return false;
    for( int i=0; i<64; i++ )
    {
        if( !fwrite(binary + 48,    1,1,fp) ) return false;
        if( !fwrite(pixels + 64*i,256,1,fp) ) return false;
    }
    if( !fwrite(binary+48,20,1,fp) ) return false;
    return true;
}

// Main method. Implemented by me.
int main(int argc, char **argv)
{
    // Pixels.
    uint32_t pixels[64*64];

    // Color.
    uint32_t color = strtol(argv[1], NULL, 16);

    // Set color with a loop.
    for (int i = 0; i < 64*64; i++) {
        pixels[i] = ((color >> 16) & 0xff) | ((color >> 8) & 0xff) << 8 | (color & 0xff) << 16 | 0xff << 24;
	printf("Handled row %d/64\n", (i / 64) % 64); 
    }

    // Open the file.
    
    FILE *file = fopen(argv[2], "wb");
    
    // Basic error checking.
    if (!file)
    {
        fprintf(stderr, "Couldn't open file.\n");
        return 1;
    }

    // Now that we have a successful file, try to write into it.
    if (write_png_64x64(file, pixels))
    {
        printf("Successfully wrote PNG file.\n");
    }
    else
    {
        fprintf(stderr, "Couldn't write PNG file.\n");
        return 1;
    }

    // Be nice and close our file so that we can't actually write it anymore.
    fclose(file);
    return 0;
}

