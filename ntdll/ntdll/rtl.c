#include <Windows.h>
#include "ntos.h"

#define EXPORT_C __declspec(dllexport)

EXPORT_C BOOLEAN RtlIsCurrentProcess( HANDLE hProcess ) {
	return hProcess == -1 || ( INT )NtCompareObjects( ) >= 0;
}

EXPORT_C BOOLEAN RtlIsCurrentThread( HANDLE hThread ) {
	return hThread == -2 || ( INT )NtCompareObjects( ) >= 0;
}

EXPORT_C UINT* RtlGetCurrentServiceSessionId( ) {
	return *(UINT*)NtCurrentPeb( )->SharedData;
}

EXPORT_C PWSTR RtlGetNtSystemRoot( ) {
	if( RtlGetCurrentServiceSessionId( ) )
		return ( PWSTR )NtCurrentPeb( )->SharedData + 3;
	return 0;
}

EXPORT_C DWORD64 RtlGetNtVersionNumbers(
	PULONG NtMajorVersion,
	PULONG NtMinorVersion,
	PULONG NtBuildNumber
) {
	struct _PEB* CurrentPeb = NtCurrentPeb( );
	ULONG ulValue = 0;

	if( NtMajorVersion )
	{
		ulValue = CurrentPeb->OSMajorVersion;
		*NtMajorVersion = ulValue;
	}
	if( NtMinorVersion )
	{
		ulValue = CurrentPeb->OSMinorVersion;
		*NtMinorVersion = ulValue;
	}
	if( NtBuildNumber )
	{
		ulValue = CurrentPeb->OSBuildNumber | 0xF0000000;
		*NtBuildNumber = ulValue;
	}
	return ulValue;
}


NTSTATUS __fastcall RtlpNtCreateKey(
	PHANDLE KeyHandle,
	ACCESS_MASK DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes,
	PULONG Disposition
) {

	if( ObjectAttributes )
		*( DWORD* )( ObjectAttributes->SecurityDescriptor ) &= 0xFFFFFFCF;
	return NtCreateKey( KeyHandle, DesiredAccess, ObjectAttributes, NULL, NULL, NULL, Disposition );
}

NTSTATUS __fastcall RtlpNtOpenKey(
	PHANDLE pKeyHandle,
	ACCESS_MASK DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes
) {
	if( ObjectAttributes )
		*( DWORD* )( ObjectAttributes->SecurityDescriptor ) &= 0xFFFFFFCF;
	return NtOpenKey( pKeyHandle, DesiredAccess, ObjectAttributes );
}

NTSTATUS __fastcall RtlpNtSetValueKey(
	HANDLE KeyHandle,
	ULONG Type,
	PVOID Data,
	ULONG DataSize
) {

	UNICODE_STRING Value = { 0 };

	return NtSetValueKey(
		KeyHandle,
		&Value,
		NULL,
		Type,
		Data,
		DataSize );
}