#include <nds.h>
#include <fat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>


//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------
	
	// Initialise the console, required for printf
	consoleDemoInit();
	enableSlot1();
	if (fatInitDefault()) {
	sysSetBusOwners(true, true);
	int type = cardEepromGetType();
	static u8 save[524288];
	FILE *file;
	file = fopen("savedata.bin", "wb");
	iprintf("Fat init succeeded.\n");
	iprintf("A: DUMP ROM\n");
	iprintf("START: EXIT\n");
	while(1) {
	swiWaitForVBlank();
	scanKeys();
		if(keysDown()&KEY_START) break;
		if(keysDown()&KEY_A) {
				iprintf("reading EEPROM...\n");
				cardEepromCommand(0x03); 
				cardReadEeprom(0, save, 524288, type);
				iprintf("writing to file... \n");
				fwrite(save, 1, sizeof(save), file);
				iprintf("done.. \n");
				fclose(file);
		}	
	}
	} else {
		iprintf("fatInitDefault failure: terminating\n");
	}

	return 0;
}
