#include <3ds.h>
#include <stdio.h>
#include <string>

#include "hbkb.h"

int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	// Keyboard Class
	HB_Keyboard sHBKB;

	printf("\x1b[0;0HHB_Keyboard Library Demo.");
	printf("\x1b[1;0HPress Start to exit.");

	while (aptMainLoop())
	{
		//Scan Inputs
		hidScanInput();
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) 
			break;

		// Touch Stuff
		touchPosition touch;

		//Read the touch screen coordinates
		hidTouchRead(&touch);

		// Call Keyboard with Touch Position
		u8 KBState = sHBKB.HBKB_CallKeyboard(touch);
		
		// Print Input
		std::string InputHBKB = sHBKB.HBKB_CheckKeyboardInput(); // Check Input
		const char* InputCChar = InputHBKB.c_str();
		printf("\x1b[3;0HInput :");
		printf("\x1b[4;0H%s", InputCChar);

		if (KBState == 1) // User finished Input
		{
			sHBKB.HBKB_Clean(); // Clean Input
			printf("\x1b[2;0HKeyboard Return = Enter Key Pressed");
			break;
		}
		else if (KBState == 2)
			printf("\x1b[2;0HKeyboard Return = Generic Key Pressed");
		else if (KBState == 3)
		{
			sHBKB.HBKB_Clean(); // Clean Input
			printf("\x1b[2;0HKeyboard Return = Cancel Button Pressed");
			break;
		}
		else if (KBState == 4)
			printf("\x1b[2;0HKeyboard Return = No Key Pressed");
		else if (KBState == 0)
			printf("\x1b[2;0HKeyboard Return = UNKNOWN (HBKB Error).");
		else
			printf("\x1b[2;0HKeyboard Return = UNKNOWN (main.cpp Error).");

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	// Exit services
	gfxExit();
	return 0;
}
