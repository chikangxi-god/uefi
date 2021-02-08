#include "uefi.h"

UINT32 mHorizontalResolution;
UINT32 mVerticalResolution;
UINT32 mPixelsPerScanline;
EFI_MEMORY_DESCRIPTOR mMemoryMap[200];

static const CHAR16* toString(UINT64 n)
{
	static CHAR16 buff[17];
	static const CHAR16 map[]={L'0',L'1',L'2',L'3',L'4',L'5',L'6',
		L'7',L'8',L'9',L'a',L'b',L'c',L'd',L'e',L'f'};
	for (int i = 0; i < 16; i++)
	{
		buff[15-i]=map[n%16];
		n/=16;
	}
	buff[16]=L'\0';
	return buff;
}

void efi_main(EFI_HANDLE ImageHandle
		,EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	EFI_SYSTEM_TABLE *ST = SystemTable;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP=NULL;
	EFI_STATUS code = ST->BootServices->LocateProtocol(&gop_guid, NULL,
			(VOID**)&GOP);
	ST->ConOut->OutputString(ST->ConOut,L"\n\rreturn code : ");
	ST->ConOut->OutputString(ST->ConOut,toString(code));
	ST->ConOut->OutputString(ST->ConOut,L"\n\rMaxMode:");
	ST->ConOut->OutputString(ST->ConOut,toString(GOP->Mode->MaxMode));
	ST->ConOut->OutputString(ST->ConOut,L"\n\rMode:");
	ST->ConOut->OutputString(ST->ConOut,toString(GOP->Mode->Mode));

	UINT32 pixelsPerScanLine = GOP->Mode->Info->PixelsPerScanLine;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION info = *GOP->Mode->Info;
	mHorizontalResolution = info.HorizontalResolution;
	mVerticalResolution = info.VerticalResolution;
	mPixelsPerScanline = info.PixelsPerScanLine;
	for (int i=0;i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
		EFI_GRAPHICS_OUTPUT_BLT_PIXEL *p=
			(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)
			(GOP->Mode->FrameBufferBase);
		(p+pixelsPerScanLine*i+j)->Blue=100;
		(p+pixelsPerScanLine*i+j)->Reserved=0;
		}
	}
	UINTN memoryMapSize=sizeof(mMemoryMap);
	UINTN mapKey;
	UINTN descriptorSize;
	UINT32 descriptorVersion;
	code = ST->BootServices->GetMemoryMap(&memoryMapSize,mMemoryMap,&mapKey,&descriptorSize,&descriptorVersion);
	if (code!=EFI_SUCCESS)ST->ConOut->OutputString(ST->ConOut,L"error get memory map");
	code = ST->BootServices->ExitBootServices(ImageHandle,mapKey);
	if (code!=EFI_SUCCESS)ST->ConOut->OutputString(ST->ConOut,L"error exit boot services");
	while (1);
}
