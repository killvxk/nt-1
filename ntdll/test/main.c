#include <Windows.h>
#include "../ntdll/ntos.h"

NTSTATUS
NTAPI
NtWriteFile(
	_In_ HANDLE FileHandle,
	_In_opt_ HANDLE Event,
	_In_opt_ PIO_APC_ROUTINE ApcRoutine,
	_In_opt_ PVOID ApcContext,
	_Out_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_ PVOID Buffer,
	_In_ ULONG Length,
	_In_opt_ PLARGE_INTEGER ByteOffset,
	_In_opt_ PULONG Key
);

int main( ) {
	// Load custom ntdll
	LoadLibraryA( "C:\\Users\\leet\\Desktop\\ntdll\\x64\\Release\\ntdll.dll", "NtCreateFile");

	HANDLE hFile = CreateFileA( "c:\\users\\leet\\desktop\\test.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ| FILE_SHARE_WRITE,
				 0, CREATE_NEW , 0, FILE_ATTRIBUTE_NORMAL );


	OBJECT_ATTRIBUTES oa;
	HANDLE fileHandle = NULL;
	NTSTATUS status = NULL;
	UNICODE_STRING fileName;
	IO_STATUS_BLOCK osb;

	unsigned char Buffer[ ] = "test";
	NtWriteFile( hFile, NULL, NULL, NULL, &osb, Buffer, strlen( Buffer ), 0, NULL );

	return 0;

}