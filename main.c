/* main.c
Copyright 2021 Carl John Kugler III

Licensed under the Apache License, Version 2.0 (the License); you may not use
this file except in compliance with the License. You may obtain a copy of the
License at

   http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an AS IS BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
*/

#include <stdio.h>
#include <stdint.h>         //ssd1306
#include <string.h>         //ssd1306
//
#include "pico/stdlib.h"
#include "hardware/i2c.h"   //ssd1306
//
#include "hw_config.h"
#include "f_util.h"
#include "ff.h"
//ssd1306
#include "lib/pico-ssd1306/ssd1306.h"
#include "images/LogoMaker128x64.h"
#include "images/TestImage128x64.h"
#include "fonts/acme_5_outlines_font.h"
#include "fonts/bubblesstandard_font.h"
#include "fonts/crackers_font.h"
#include "fonts/BMSPA_font.h"

const uint8_t num_chars_per_disp[]={7,7,7,5};
const uint8_t *fonts[4]= {acme_font, bubblesstandard_font, crackers_font, BMSPA_font};

#define SLEEPTIME       25
#define i2cx            i2c0    //I2C HW Block Selected
#define i2cx_sda_gpio   4
#define i2cx_scl_gpio   5

void setup_gpios(void);
void animation(void);

/**
 * @file main.c
 * @brief Minimal example of writing to a file on SD card
 * @details
 * This program demonstrates the following:
 * - Initialization of the stdio
 * - Mounting and unmounting the SD card
 * - Opening a file and writing to it
 * - Closing a file and unmounting the SD card
 */

int main() {
    // Initialize stdio
    stdio_init_all();

    printf("configuring SSD1306 pins...\n");
    setup_gpios();

    puts("Hello, Secure Digital (SD) world!");

    // See FatFs - Generic FAT Filesystem Module, "Application Interface",
    // http://elm-chan.org/fsw/ff/00index_e.html
    FATFS fs;
    FRESULT fr = f_mount(&fs, "", 1);
    if (FR_OK != fr) {
        panic("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
    }

    // Open a file and write to it
    FIL fil;
    const char* const filename = "filename.txt";
    fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE);
    if (FR_OK != fr && FR_EXIST != fr) {
        panic("f_open(%s) error: %s (%d)\n", filename, FRESULT_str(fr), fr);
    }
    if (f_printf(&fil, __DATE__" "__TIME__" ""Hello, Secure Digital (SD) world!\n") < 0) {
        printf("f_printf failed\n");
    }

    printf("f_size(filename.txt): %llu\n", f_size(&fil));

    // Close the file
    fr = f_close(&fil);
    if (FR_OK != fr) {
        printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
    }

    // Open a image file
    memset(&fil, 0, sizeof(FIL));   // Clear fil structure
    const char imgfilename[] = "LogoFastline128x64.bmp";
    fr = f_open(&fil, imgfilename, FA_OPEN_EXISTING | FA_READ);
    if (FR_OK != fr) {
        panic("f_open(%s) error: %s (%d)\n", imgfilename, FRESULT_str(fr), fr);
    }

    // Print the size of the image file (read test)
    printf("f_size(LogoFastline128x64.bmp): %llu\n", f_size(&fil));

    // Copy contents of image file to image buffer
    char imgbuffer[2048];
    UINT btr = f_size(&fil);    // Bytes to read
    UINT br;                    // Bytes read count
    fr = f_read(&fil, imgbuffer, btr, &br);
    if (br == 0) {
        printf("f_read error or eof: %s (%d)\n", FRESULT_str(fr), fr);
    }

    // Close the image file
    fr = f_close(&fil);
    if (FR_OK != fr) {
        printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
    }

    // Unmount the SD card
    f_unmount("");

    puts("Goodbye, Secure Digital (SD) world!");

    // Initializing Display
    ssd1306_t disp;
    disp.external_vcc=false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2cx);
    ssd1306_clear(&disp);

    // Show the Image on the Display
    ssd1306_bmp_show_image(&disp, imgbuffer, br);
    ssd1306_show(&disp);
    sleep_ms(2000);
  //ssd1306_clear(&disp);

  //printf("jumping to SSD1306 animation...\n");
  //animation();

    for (;;);   //animation() loops forever
}

void setup_gpios(void) {
    i2c_init(i2cx, 400000);
    gpio_set_function(i2cx_sda_gpio, GPIO_FUNC_I2C);
    gpio_set_function(i2cx_scl_gpio, GPIO_FUNC_I2C);
    gpio_pull_up(i2cx_sda_gpio);
    gpio_pull_up(i2cx_scl_gpio);
}

void animation(void) {
    const char *words[]= {"SSD1306", "DISPLAY", "DRIVER"};

    ssd1306_t disp;
    disp.external_vcc=false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2cx);
    ssd1306_clear(&disp);

    printf("ANIMATION!\n");

    char buf[8];

    /*  Test displaying two images continously
        Note: The ssd1306_bmp_show_image() function performs an OR operation
        with the previous image. Essentially, it only calls ssd1306_draw_pixel()
        to turn pixels on, preserving existing data in the framebuffer. To
        prevent this effect, a ssd1306_clear() call is necessary to clear the
        display. However, during debugging, I noticed that when a new image is
        shown, parts of the previous image remain where the new image hasn't
        reached. This is because the old data persists on the display itself,
        awaiting new data. Therefore, a ssd1306_clear() followed by ssd1306_show()
        is required to avoid this issue.
    */
    while(1)
    {
        ssd1306_bmp_show_image(&disp, logo_maker_data, logo_maker_size);
        ssd1306_show(&disp);
        ssd1306_clear(&disp);
      //ssd1306_show(&disp);

        ssd1306_bmp_show_image(&disp, test_image_data, test_image_size);
        ssd1306_show(&disp);
        ssd1306_clear(&disp);
      //ssd1306_show(&disp);
    }

    for(;;) {
        for(int16_t y=0; y<31; ++y) {
            ssd1306_draw_line(&disp, 0, y, 127, y);
            ssd1306_show(&disp);
            sleep_ms(SLEEPTIME);
            ssd1306_clear(&disp);
        }

        ssd1306_bmp_show_image(&disp, logo_maker_data, logo_maker_size);
        ssd1306_show(&disp);
        sleep_ms(2000);

        for(int16_t y=0, i=1; y>=0; y+=i) {
            ssd1306_draw_line(&disp, 0, 31-y, 127, 31+y);
            ssd1306_draw_line(&disp, 0, 31+y, 127, 31-y);
            ssd1306_show(&disp);
            sleep_ms(SLEEPTIME);
            ssd1306_clear(&disp);
            if(y==32) i=-1;
        }

        for(int16_t i=0; i<sizeof(words)/sizeof(char *); ++i) {
            ssd1306_draw_string(&disp, 8, 24, 2, words[i]);
            ssd1306_show(&disp);
            sleep_ms(800);
            ssd1306_clear(&disp);
        }

        for(int16_t y=31; y<63; ++y) {
            ssd1306_draw_line(&disp, 0, y, 127, y);
            ssd1306_show(&disp);
            sleep_ms(SLEEPTIME);
            ssd1306_clear(&disp);
        }

        for(size_t font_i=0; font_i<sizeof(fonts)/sizeof(fonts[0]); ++font_i) {
            uint8_t c=32;
            while(c<=126) {
                uint8_t i=0;
                for(; i<num_chars_per_disp[font_i]; ++i) {
                    if(c>126)
                        break;
                    buf[i]=c++;
                }
                buf[i]=0;

                ssd1306_draw_string_with_font(&disp, 8, 24, 2, fonts[font_i], buf);
                ssd1306_show(&disp);
                sleep_ms(800);
                ssd1306_clear(&disp);
            }
        }

        ssd1306_bmp_show_image(&disp, test_image_data, test_image_size);
        ssd1306_show(&disp);
        sleep_ms(2000);
    }
}
