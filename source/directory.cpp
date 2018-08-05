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
	consoleDemoInit();
	enableSlot1();
	if (fatInitDefault()) {
	sysSetBusOwners(true, true);
	int type = cardEepromGetType();
	static u8 save[524288];
	FILE *file;
	iprintf("Fat init succeeded.\n");
	iprintf("A: DUMP EEPROM\n");
	iprintf("X: WRITE EEPROM\n");
	iprintf("START: EXIT\n");
	while(1) {
	swiWaitForVBlank();
	scanKeys();
		if(keysDown()&KEY_START) break;
		if(keysDown()&KEY_A) {
				file = fopen("savedata.bin", "wb");
				iprintf("reading EEPROM...\n");
				cardEepromCommand(0x03); 
				cardReadEeprom(0, save, 524288, type);
				iprintf("writing to file... \n");
				fwrite(save, 1, sizeof(save), file);
				iprintf("done.\n");
				fclose(file);
		}

		if(keysDown()&KEY_X) {
					file = fopen("savedata.bin", "rb");
					iprintf("reading savedata.bin...\n");
					if(!file) {
					iprintf("reading savedata.bin failed!\n Please restart the system.\n");
					} else {
					iprintf("savedata.bin found!\n");
					fputc(save[524288], file);
					iprintf("Writing to EEPROM...\n");
					cardWriteEeprom(0, save, 524288, type);
					iprintf("done.\n");
		}
	}
	}
	} else {
		iprintf("fatInitDefault failure: terminating\n");
	}
	return 0;
}
