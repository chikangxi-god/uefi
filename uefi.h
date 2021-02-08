#include <stdint.h>
#define NULL (0)
typedef uint8_t BOOLEAN;
typedef int64_t INTN;
typedef uint64_t UINTN;
typedef int8_t INT8;
typedef uint8_t UINT8;
typedef int16_t INT16;
typedef uint16_t UINT16;
typedef int32_t INT32;
typedef uint32_t UINT32;
typedef int64_t INT64;
typedef uint64_t UINT64;
typedef uint8_t CHAR8;
typedef uint16_t CHAR16;
typedef void VOID;
typedef struct {
	UINT32 a;
	UINT16 a1;
	UINT16 a2;
	struct {
		UINT8 b;
		UINT8 c;
		UINT8 d;
		UINT8 e;
		UINT8 f;
		UINT8 g;
		UINT8 h;
		UINT8 i;
	}__attribute__((aligned(1))) b;
}__attribute__((aligned(8))) EFI_GUID;
typedef UINTN EFI_STATUS;
#define EFI_SUCCESS 0
#define EFI_LOAD_ERROR ((1<<31)|1u)
#define EFI_INVALID_PARAMETER ((1<<31)|2u)
#define EFI_UNSUPPORTED ((1<<31)|3u)
#define EFI_BAD_BUFFER_SIZE ((1<<31)|4u)
#define EFI_NOT_READY ((1<<31)|6u)
#define EFI_NOT_FOUND ((1<<31)|14u)
typedef VOID* EFI_HANDLE;
typedef VOID* EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;


typedef struct{
	UINT64 Signature;
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
}__attribute__((packed)) EFI_TABLE_HEADER;



typedef EFI_STATUS (*EFI_LOCATE_PROTOCOL)(
		EFI_GUID *Protocol,
		VOID* Registration,
		VOID **Interface
		);
typedef struct{
	UINT32 Type;
	EFI_PHYSICAL_ADDRESS PhysicalStart;
	EFI_VIRTUAL_ADDRESS VirtualStart;
	UINT64 NumberOfPages;
	UINT64 Attribute;
}EFI_MEMORY_DESCRIPTOR;
typedef
EFI_STATUS
(*EFI_GET_MEMORY_MAP)(
		UINTN*,
		EFI_MEMORY_DESCRIPTOR*,
		UINTN*,
		UINTN*,
		UINT32*
		);
typedef
EFI_STATUS
(*EFI_EXIT_BOOT_SERVICES)(
		EFI_HANDLE,
		UINTN
		);

#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

typedef struct{
	EFI_TABLE_HEADER Hdr;

	void(* RaiseTPL)();
	void(* RestoreTPL)();

	void(* AllocatePages)();
	void(* FreePages)();
	EFI_GET_MEMORY_MAP GetMemoryMap;
	void(* AllocatePool)();
	void(* FreePool)();
	
	void(* CreateEvent)();
	void(* SetTimer)();
	void(* WaitForEvent)();
	void(* SignalEvent)();
	void(* CloseEvent)();
	void(* CheckEvent)();

	void(* InstallProtocolInterface)();
	void(* ReinstallProtocolInterface)();
	void(* UninstallProtocolInterface)();
	void(* HandleProtocol)();
	VOID* Reserved;
	void(* RegisterProtocolNotify)();
	void(* LocateHandle)();
	void(* LocateDevicePath)();
	void(* InstallConfigurationTable)();

	void(* LoadImage)();
	void(* StartImage)();
	void(* Exit)();
	void(* UnloadImage)();
	EFI_EXIT_BOOT_SERVICES ExitBootServices;
	
	void(* GetNextmonotonicCount)();
	void(* Stall)();
	void(* SetWatchdogTimer)();

	void(* ConnectController)();
	void(* DisconnectController)();

	void(* OpenProtocol)();
	void(* CloseProtocol)();
	void(* OpenProtocolInformation)();

	void(* ProtocolsPerHandle)();
	void(* LocateHandleBuffer)();
	EFI_LOCATE_PROTOCOL LocateProtocol;
	void* InstallMultipleProtocolInterfaces;
	void* UninstallMultipleProtocolInterfaces;

	void* CalculateCrc32;

	void* CopyMem;
	void* SetMem;
	void(* CreateEventEx)();
} EFI_BOOT_SERVICES;

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
typedef struct EFI_RUNTIME_SERVICES EFI_RUNTIME_SERVICES;

#define EFI_SYSTEM_TABLE_SIGNATURE 0x5453595320494249
#define EFI_2_30_SYSTEM_TABLE_REVISION ((2<<16)|(30))


typedef struct {
	EFI_TABLE_HEADER Hdr;
	CHAR16 *FirmwareVendor;
	UINT32 FirmwareRevision;
	EFI_HANDLE ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
	EFI_HANDLE ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
	EFI_HANDLE StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
	EFI_RUNTIME_SERVICES *RuntimeServices;
	EFI_BOOT_SERVICES *BootServices;
	UINTN NumberOfTableEntries;
} EFI_SYSTEM_TABLE;
typedef
EFI_STATUS
(*EFI_INPUT_RESET)(
		EFI_SIMPLE_TEXT_INPUT_PROTOCOL *,
		BOOLEAN ExtendedVerification
		);
typedef struct{
	UINT16 ScanCode;
	CHAR16 UnicodeChar;
}EFI_INPUT_KEY;
typedef
EFI_STATUS
(*EFI_INPUT_READ_KEY)(
		EFI_SIMPLE_TEXT_INPUT_PROTOCOL *,
		EFI_INPUT_KEY *
		);

struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	EFI_INPUT_RESET Reset;
	EFI_INPUT_READ_KEY ReadKeyStroke;
	EFI_EVENT WaitForKay;
};
struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
	unsigned long long _buf1;
	EFI_STATUS (*OutputString)(
			EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*,
			const CHAR16*);
	unsigned long long _buf[4];
	EFI_STATUS (*ClearScreen)(
			EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*);
};



typedef struct EFI_GRAPHICS_OUTPUT_PROTCOL EFI_GRAPHICS_OUTPUT_PROTOCOL;


typedef struct{
	UINT32 RedMask;
	UINT32 GreenMask;
	UINT32 BlueMask;
	UINT32 ReservedMask;
}EFI_PIXEL_BITMASK;
typedef enum{
	PixelRedGreenBlueReserved8BitPerColor,
	PixelBlueGreenRedReserved8BitPerColor,
	PixelBitMask,
	PixelBltOnly,
	PixelFormatMax
}EFI_GRAPHICS_PIXEL_FORMAT;
typedef struct{
	UINT32 Version;
	UINT32 HorizontalResolution;
	UINT32 VerticalResolution;
	EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
	EFI_PIXEL_BITMASK PixelInformation;
	UINT32 PixelsPerScanLine;
}EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;
typedef struct{
	UINT32 MaxMode;
	UINT32 Mode;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
	UINTN SizeOfInfo;
	EFI_PHYSICAL_ADDRESS FrameBufferBase;
	UINTN FrameBufferSize;
}EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;
typedef
EFI_STATUS
(*EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE)(
		EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
		UINT32 ModeNumber,
		UINTN *SizeOfInfo,
		EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info
		);
typedef
EFI_STATUS
(*EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE)(
		EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
		UINT32 ModeNumber
		);
typedef struct{
	UINT8 Blue;
	UINT8 Green;
	UINT8 Red;
	UINT8 Reserved;
}EFI_GRAPHICS_OUTPUT_BLT_PIXEL;
typedef enum{
	EfiBltVideoFill,
	EfiBltVideoToBltBuffer,
	EfiBltBufferToVideo,
	EfiBltVideoToVideo,
	EfiGraphicsOutputBltOperationMax
}EFI_GRAPHICS_OUTPUT_BLT_OPERATION;
typedef
EFI_STATUS
(*EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT)(
		EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
		EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer,
		EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation,
		UINTN SourceX,
		UINTN SourceY,
		UINTN DestinationX,
		UINTN DestinationY,
		UINTN Width,
		UINTN Height,
		UINTN Delta
		);

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID \
{0x9042a9de,0x23dc,0x4a38,\
	{0x96,0xfb,0x7a,0xde,0xd0,0x80,0x51,0x6a}}
typedef struct EFI_GRAPHICS_OUTPUT_PROTCOL {
	EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE QueryMode;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE SetMode;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT Blt;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
}EFI_GRAPHICS_OUTPUT_PROTOCOL;

