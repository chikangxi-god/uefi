BOOTx64.EFI : main.c uefi.h
	x86_64-w64-mingw32-gcc -Wall -Wextra -e efi_main -nostdinc -nostdlib \
		-fno-builtin -Wl,--subsystem,10 -o BOOTx64.EFI main.c -I /usr/share/mingw-w64/include
install : BOOTx64.EFI
	if ls /mnt/efi/EFI/BOOT; \
	then true; \
	else mount /dev/sda1 /mnt/efi; \
	fi
	cp BOOTx64.EFI /mnt/efi/EFI/BOOT/BOOTx64.EFI
	umount /mnt/efi
