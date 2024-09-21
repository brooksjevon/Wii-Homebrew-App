#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

static u32 *xfb;
static GXRModeObj *rmode;


void Initialise() {
  
//	VIDEO_Init();
//	PAD_Init();
// 
//	rmode = VIDEO_GetPreferredMode(NULL);
//
//	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
//	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
// 
//	VIDEO_Configure(rmode);
//	VIDEO_SetNextFramebuffer(xfb);
//	VIDEO_SetBlack(FALSE);
//	VIDEO_Flush();
//	VIDEO_WaitVSync();
//	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

    // Initialize video subsystem
    VIDEO_Init();

    // Initialize GameCube controller subsystem
    PAD_Init();

    // Get the preferred video mode for the current display (NTSC, PAL, etc.)
    rmode = VIDEO_GetPreferredMode(NULL);

    // Allocate memory for the framebuffer
    xfb = SYS_AllocateFramebuffer(rmode);
    if (!xfb) {
        // Handle error if memory allocation fails
        printf("Error: Failed to allocate memory for framebuffer\n");
        exit(1); // or handle it gracefully as per your design
    }

    // Initialize the console with the allocated framebuffer
    console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);

    // Configure the video settings based on the preferred mode
    VIDEO_Configure(rmode);

    // Set the allocated framebuffer as the next framebuffer to be displayed
    VIDEO_SetNextFramebuffer(xfb);

    // Turn off the black screen, so the content is visible
    VIDEO_SetBlack(FALSE);

    // Flush any pending video-related operations
    VIDEO_Flush();

    // Wait for the vertical sync to ensure smooth display
    VIDEO_WaitVSync();

    // If the video mode is non-interlaced, wait for an additional VSync
    if (rmode->viTVMode & VI_NON_INTERLACE) {
        VIDEO_WaitVSync();
    }
}


int main() {
 
	Initialise();
 
	printf("Hello World!\n");
	
	while (true) {

		VIDEO_WaitVSync();	
	}

	return 0;
}
