#define _WIN32_WINNT 0x0501 
#define WINVER 0x0501 
#define NTDDI_VERSION 0x05010000
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>

#pragma region GiveCallback
//#include <commctrl.h>
//
//// C RunTime Header Files
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>
//
//
//#include <psapi.h>
//#pragma comment( lib, "psapi.lib" )
//using std::string;
//
//
////-----------------------------------------------------------------------------
//
//HMODULE WINAPI GetRemoteModuleHandle( HANDLE hProcess , LPCSTR lpModuleName )
//{
//	HMODULE* ModuleArray = NULL;
//	DWORD ModuleArraySize = 100;
//	DWORD NumModules = 0;
//	CHAR lpModuleNameCopy[ MAX_PATH ] = { 0 };
//	CHAR ModuleNameBuffer[ MAX_PATH ] = { 0 };
//
//	/* Make sure we didn't get a NULL pointer for the module name */
//	if ( lpModuleName == NULL )
//		goto GRMH_FAIL_JMP;
//
//	/* Convert lpModuleName to all lowercase so the comparison isn't case sensitive */
//	for ( size_t i = 0; lpModuleName[ i ] != '\0'; ++i )
//	{
//		if ( lpModuleName[ i ] >= 'A' && lpModuleName[ i ] <= 'Z' )
//			lpModuleNameCopy[ i ] = lpModuleName[ i ] + 0x20; // 0x20 is the difference between uppercase and lowercase
//		else
//			lpModuleNameCopy[ i ] = lpModuleName[ i ];
//
//		lpModuleNameCopy[ i + 1 ] = '\0';
//	}
//
//	/* Allocate memory to hold the module handles */
//	ModuleArray = new HMODULE[ ModuleArraySize ];
//
//	/* Check if the allocation failed */
//	if ( ModuleArray == NULL )
//		goto GRMH_FAIL_JMP;
//
//	/* Get handles to all the modules in the target process */
//	if ( !::EnumProcessModulesEx( hProcess , ModuleArray ,
//		ModuleArraySize * sizeof( HMODULE ) , &NumModules , LIST_MODULES_ALL ) )
//		goto GRMH_FAIL_JMP;
//
//	/* We want the number of modules not the number of bytes */
//	NumModules /= sizeof( HMODULE );
//
//	/* Did we allocate enough memory for all the module handles? */
//	if ( NumModules > ModuleArraySize )
//	{
//		delete[ ] ModuleArray; // Deallocate so we can try again
//		ModuleArray = NULL; // Set it to NULL se we can be sure if the next try fails
//		ModuleArray = new HMODULE[ NumModules ]; // Allocate the right amount of memory
//
//		/* Check if the allocation failed */
//		if ( ModuleArray == NULL )
//			goto GRMH_FAIL_JMP;
//
//		ModuleArraySize = NumModules; // Update the size of the array
//
//		/* Get handles to all the modules in the target process */
//		if ( !::EnumProcessModulesEx( hProcess , ModuleArray ,
//			ModuleArraySize * sizeof( HMODULE ) , &NumModules , LIST_MODULES_ALL ) )
//			goto GRMH_FAIL_JMP;
//
//		/* We want the number of modules not the number of bytes */
//		NumModules /= sizeof( HMODULE );
//	}
//
//	/* Iterate through all the modules and see if the names match the one we are looking for */
//	for ( DWORD i = 0; i <= NumModules; ++i )
//	{
//		/* Get the module's name */
//		::GetModuleBaseName( hProcess , ModuleArray[ i ] ,
//							 ModuleNameBuffer , sizeof( ModuleNameBuffer ) );
//
//		/* Convert ModuleNameBuffer to all lowercase so the comparison isn't case sensitive */
//		for ( size_t j = 0; ModuleNameBuffer[ j ] != '\0'; ++i )
//		{
//			if ( ModuleNameBuffer[ j ] >= 'A' && ModuleNameBuffer[ j ] <= 'Z' )
//				ModuleNameBuffer[ j ] += 0x20; // 0x20 is the difference between uppercase and lowercase
//		}
//
//		/* Does the name match? */
//		if ( strstr( ModuleNameBuffer , lpModuleNameCopy ) != NULL )
//		{
//			/* Make a temporary variable to hold return value*/
//			HMODULE TempReturn = ModuleArray[ i ];
//
//			/* Give back that memory */
//			delete[ ] ModuleArray;
//
//			/* Success */
//			return TempReturn;
//		}
//
//		/* Wrong module let's try the next... */
//	}
//
//	/* Uh Oh... */
//GRMH_FAIL_JMP:
//
//	/* If we got to the point where we allocated memory we need to give it back */
//	if ( ModuleArray != NULL )
//		delete[ ] ModuleArray;
//
//	/* Failure... */
//	return NULL;
//}
//
//
////-----------------------------------------------------------------------------
//
//FARPROC WINAPI GetRemoteProcAddress( HANDLE hProcess , HMODULE hModule , LPCSTR lpProcName , UINT Ordinal , BOOL UseOrdinal )
//{
//	BOOL Is64Bit = FALSE;
//	MODULEINFO RemoteModuleInfo = { 0 };
//	UINT_PTR RemoteModuleBaseVA = 0;
//	IMAGE_DOS_HEADER DosHeader = { 0 };
//	DWORD Signature = 0;
//	IMAGE_FILE_HEADER FileHeader = { 0 };
//	IMAGE_OPTIONAL_HEADER64 OptHeader64 = { 0 };
//	IMAGE_OPTIONAL_HEADER32 OptHeader32 = { 0 };
//	IMAGE_DATA_DIRECTORY ExportDirectory = { 0 };
//	IMAGE_EXPORT_DIRECTORY ExportTable = { 0 };
//	UINT_PTR ExportFunctionTableVA = 0;
//	UINT_PTR ExportNameTableVA = 0;
//	UINT_PTR ExportOrdinalTableVA = 0;
//	DWORD* ExportFunctionTable = NULL;
//	DWORD* ExportNameTable = NULL;
//	WORD* ExportOrdinalTable = NULL;
//
//	/* Temporary variables not used until much later but easier
//	/* to define here than in all the the places they are used */
//	CHAR TempChar;
//	BOOL Done = FALSE;
//
//	/* Check to make sure we didn't get a NULL pointer for the name unless we are searching by ordinal */
//	if ( lpProcName == NULL && !UseOrdinal )
//		goto GRPA_FAIL_JMP;
//
//	/* Get the base address of the remote module along with some other info we don't need */
//	if ( !::GetModuleInformation( hProcess , hModule , &RemoteModuleInfo , sizeof( RemoteModuleInfo ) ) )
//		goto GRPA_FAIL_JMP;
//	RemoteModuleBaseVA = ( UINT_PTR ) RemoteModuleInfo.lpBaseOfDll;
//
//	/* Read the DOS header and check it's magic number */
//	if ( !::ReadProcessMemory( hProcess , ( LPCVOID ) RemoteModuleBaseVA , &DosHeader ,
//		sizeof( DosHeader ) , NULL ) || DosHeader.e_magic != IMAGE_DOS_SIGNATURE )
//		goto GRPA_FAIL_JMP;
//
//	/* Read and check the NT signature */
//	if ( !::ReadProcessMemory( hProcess , ( LPCVOID ) ( RemoteModuleBaseVA + DosHeader.e_lfanew ) ,
//		&Signature , sizeof( Signature ) , NULL ) || Signature != IMAGE_NT_SIGNATURE )
//		goto GRPA_FAIL_JMP;
//
//	/* Read the main header */
//	if ( !::ReadProcessMemory( hProcess ,
//		( LPCVOID ) ( RemoteModuleBaseVA + DosHeader.e_lfanew + sizeof( Signature ) ) ,
//		&FileHeader , sizeof( FileHeader ) , NULL ) )
//		goto GRPA_FAIL_JMP;
//
//	/* Which type of optional header is the right size? */
//	if ( FileHeader.SizeOfOptionalHeader == sizeof( OptHeader64 ) )
//		Is64Bit = TRUE;
//	else if ( FileHeader.SizeOfOptionalHeader == sizeof( OptHeader32 ) )
//		Is64Bit = FALSE;
//	else
//		goto GRPA_FAIL_JMP;
//
//	if ( Is64Bit )
//	{
//		/* Read the optional header and check it's magic number */
//		if ( !::ReadProcessMemory( hProcess ,
//			( LPCVOID ) ( RemoteModuleBaseVA + DosHeader.e_lfanew + sizeof( Signature ) +sizeof( FileHeader ) ) ,
//			&OptHeader64 , FileHeader.SizeOfOptionalHeader , NULL )
//			|| OptHeader64.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC )
//			goto GRPA_FAIL_JMP;
//	}
//	else
//	{
//		/* Read the optional header and check it's magic number */
//		if ( !::ReadProcessMemory( hProcess ,
//			( LPCVOID ) ( RemoteModuleBaseVA + DosHeader.e_lfanew + sizeof( Signature ) +sizeof( FileHeader ) ) ,
//			&OptHeader32 , FileHeader.SizeOfOptionalHeader , NULL )
//			|| OptHeader32.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC )
//			goto GRPA_FAIL_JMP;
//	}
//
//	/* Make sure the remote module has an export directory and if it does save it's relative address and size */
//	if ( Is64Bit && OptHeader64.NumberOfRvaAndSizes >= IMAGE_DIRECTORY_ENTRY_EXPORT + 1 )
//	{
//		ExportDirectory.VirtualAddress = ( OptHeader64.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ] ).VirtualAddress;
//		ExportDirectory.Size = ( OptHeader64.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ] ).Size;
//	}
//	else if ( OptHeader32.NumberOfRvaAndSizes >= IMAGE_DIRECTORY_ENTRY_EXPORT + 1 )
//	{
//		ExportDirectory.VirtualAddress = ( OptHeader32.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ] ).VirtualAddress;
//		ExportDirectory.Size = ( OptHeader32.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ] ).Size;
//	}
//	else
//		goto GRPA_FAIL_JMP;
//
//	/* Read the main export table */
//	if ( !::ReadProcessMemory( hProcess , ( LPCVOID ) ( RemoteModuleBaseVA + ExportDirectory.VirtualAddress ) ,
//		&ExportTable , sizeof( ExportTable ) , NULL ) )
//		goto GRPA_FAIL_JMP;
//
//	/* Save the absolute address of the tables so we don't need to keep adding the base address */
//	ExportFunctionTableVA = RemoteModuleBaseVA + ExportTable.AddressOfFunctions;
//	ExportNameTableVA = RemoteModuleBaseVA + ExportTable.AddressOfNames;
//	ExportOrdinalTableVA = RemoteModuleBaseVA + ExportTable.AddressOfNameOrdinals;
//
//	/* Allocate memory for our copy of the tables */
//	ExportFunctionTable = new DWORD[ ExportTable.NumberOfFunctions ];
//	ExportNameTable = new DWORD[ ExportTable.NumberOfNames ];
//	ExportOrdinalTable = new WORD[ ExportTable.NumberOfNames ];
//
//	/* Check if the allocation failed */
//	if ( ExportFunctionTable == NULL || ExportNameTable == NULL || ExportOrdinalTable == NULL )
//		goto GRPA_FAIL_JMP;
//
//	/* Get a copy of the function table */
//	if ( !::ReadProcessMemory( hProcess , ( LPCVOID ) ExportFunctionTableVA ,
//		ExportFunctionTable , ExportTable.NumberOfFunctions * sizeof( DWORD ) , NULL ) )
//		goto GRPA_FAIL_JMP;
//
//	/* Get a copy of the name table */
//	if ( !::ReadProcessMemory( hProcess , ( LPCVOID ) ExportNameTableVA ,
//		ExportNameTable , ExportTable.NumberOfNames * sizeof( DWORD ) , NULL ) )
//		goto GRPA_FAIL_JMP;
//
//	/* Get a copy of the ordinal table */
//	if ( !::ReadProcessMemory( hProcess , ( LPCVOID ) ExportOrdinalTableVA ,
//		ExportOrdinalTable , ExportTable.NumberOfNames * sizeof( WORD ) , NULL ) )
//		goto GRPA_FAIL_JMP;
//
//	/* If we are searching for an ordinal we do that now */
//	if ( UseOrdinal )
//	{
//		/* NOTE:
//		/* Microsoft's PE/COFF specification does NOT say we need to subtract the ordinal base
//		/* from our ordinal but it seems to always give the wrong function if we don't */
//
//		/* Make sure the ordinal is valid */
//		if ( Ordinal < ExportTable.Base || ( Ordinal - ExportTable.Base ) >= ExportTable.NumberOfFunctions )
//			goto GRPA_FAIL_JMP;
//
//		UINT FunctionTableIndex = Ordinal - ExportTable.Base;
//
//		/* Check if the function is forwarded and if so get the real address*/
//		if ( ExportFunctionTable[ FunctionTableIndex ] >= ExportDirectory.VirtualAddress &&
//			 ExportFunctionTable[ FunctionTableIndex ] <= ExportDirectory.VirtualAddress + ExportDirectory.Size )
//		{
//			Done = FALSE;
//			string TempForwardString;
//			TempForwardString.clear( ); // Empty the string so we can fill it with a new name
//
//			/* Get the forwarder string one character at a time because we don't know how long it is */
//			for ( UINT_PTR i = 0; !Done; ++i )
//			{
//				/* Get next character */
//				if ( !::ReadProcessMemory( hProcess ,
//					( LPCVOID ) ( RemoteModuleBaseVA + ExportFunctionTable[ FunctionTableIndex ] + i ) ,
//					&TempChar , sizeof( TempChar ) , NULL ) )
//					goto GRPA_FAIL_JMP;
//
//				TempForwardString.push_back( TempChar ); // Add it to the string
//
//				/* If it's NUL we are done */
//				if ( TempChar == ( CHAR )'\0' )
//					Done = TRUE;
//			}
//
//			/* Find the dot that seperates the module name and the function name/ordinal */
//			size_t Dot = TempForwardString.find( '.' );
//			if ( Dot == string::npos )
//				goto GRPA_FAIL_JMP;
//
//			/* Temporary variables that hold parts of the forwarder string */
//			string RealModuleName , RealFunctionId;
//			RealModuleName = TempForwardString.substr( 0 , Dot - 1 );
//			RealFunctionId = TempForwardString.substr( Dot + 1 , string::npos );
//
//			HMODULE RealModule = GetRemoteModuleHandle( hProcess , RealModuleName.c_str( ) );
//			FARPROC TempReturn;// Make a temporary variable to hold return value 
//
//
//			/* Figure out if the function was exported by name or by ordinal */
//			if ( RealFunctionId.at( 0 ) == '#' ) // Exported by ordinal
//			{
//				UINT RealOrdinal = 0;
//				RealFunctionId.erase( 0 , 1 ); // Remove '#' from string
//
//				/* My version of atoi() because I was too lazy to use the real one... */
//				for ( size_t i = 0; i < RealFunctionId.size( ); ++i )
//				{
//					if ( RealFunctionId[ i ] >= '0' && RealFunctionId[ i ] <= '9' )
//					{
//						RealOrdinal *= 10;
//						RealOrdinal += RealFunctionId[ i ] - '0';
//					}
//					else
//						break;
//				}
//
//				/* Recursively call this function to get return value */
//				TempReturn = GetRemoteProcAddress( hProcess , RealModule , NULL , RealOrdinal , TRUE );
//			}
//			else // Exported by name
//			{
//				/* Recursively call this function to get return value */
//				TempReturn = GetRemoteProcAddress( hProcess , RealModule , RealFunctionId.c_str( ) , 0 , FALSE );
//			}
//
//			/* Give back that memory */
//			delete[ ] ExportFunctionTable;
//			delete[ ] ExportNameTable;
//			delete[ ] ExportOrdinalTable;
//
//			/* Success!!! */
//			return TempReturn;
//		}
//		else // Not Forwarded
//		{
//
//			/* Make a temporary variable to hold return value*/
//			FARPROC TempReturn = ( FARPROC ) ( RemoteModuleBaseVA + ExportFunctionTable[ FunctionTableIndex ] );
//
//			/* Give back that memory */
//			delete[ ] ExportFunctionTable;
//			delete[ ] ExportNameTable;
//			delete[ ] ExportOrdinalTable;
//
//			/* Success!!! */
//			return TempReturn;
//		}
//	}
//
//
//	/* Iterate through all the names and see if they match the one we are looking for */
//	for ( DWORD i = 0; i < ExportTable.NumberOfNames; ++i )
//	{
//		string TempFunctionName;
//
//		Done = FALSE;// Reset for next name
//		TempFunctionName.clear( ); // Empty the string so we can fill it with a new name
//
//		/* Get the function name one character at a time because we don't know how long it is */
//		for ( UINT_PTR j = 0; !Done; ++j )
//		{
//			/* Get next character */
//			if ( !::ReadProcessMemory( hProcess , ( LPCVOID ) ( RemoteModuleBaseVA + ExportNameTable[ i ] + j ) ,
//				&TempChar , sizeof( TempChar ) , NULL ) )
//				goto GRPA_FAIL_JMP;
//
//			TempFunctionName.push_back( TempChar ); // Add it to the string
//
//			/* If it's NUL we are done */
//			if ( TempChar == ( CHAR )'\0' )
//				Done = TRUE;
//		}
//
//		/* Does the name match? */
//		if ( TempFunctionName.find( lpProcName ) != string::npos )
//		{
//			/* NOTE:
//			/* Microsoft's PE/COFF specification says we need to subtract the ordinal base
//			/*from the value in the ordinal table but that seems to always give the wrong function */
//
//			/* Check if the function is forwarded and if so get the real address*/
//			if ( ExportFunctionTable[ ExportOrdinalTable[ i ] ] >= ExportDirectory.VirtualAddress &&
//				 ExportFunctionTable[ ExportOrdinalTable[ i ] ] <= ExportDirectory.VirtualAddress + ExportDirectory.Size )
//			{
//				Done = FALSE;
//				string TempForwardString;
//				TempForwardString.clear( ); // Empty the string so we can fill it with a new name
//
//				/* Get the forwarder string one character at a time because we don't know how long it is */
//				for ( UINT_PTR j = 0; !Done; ++j )
//				{
//					/* Get next character */
//					if ( !::ReadProcessMemory( hProcess ,
//						( LPCVOID ) ( RemoteModuleBaseVA + ExportFunctionTable[ i ] + j ) ,
//						&TempChar , sizeof( TempChar ) , NULL ) )
//						goto GRPA_FAIL_JMP;
//
//					TempForwardString.push_back( TempChar ); // Add it to the string
//
//					/* If it's NUL we are done */
//					if ( TempChar == ( CHAR )'\0' )
//						Done = TRUE;
//				}
//
//				/* Find the dot that seperates the module name and the function name/ordinal */
//				size_t Dot = TempForwardString.find( '.' );
//				if ( Dot == string::npos )
//					goto GRPA_FAIL_JMP;
//
//				/* Temporary variables that hold parts of the forwarder string */
//				string RealModuleName , RealFunctionId;
//				RealModuleName = TempForwardString.substr( 0 , Dot );
//				RealFunctionId = TempForwardString.substr( Dot + 1 , string::npos );
//
//				HMODULE RealModule = GetRemoteModuleHandle( hProcess , RealModuleName.c_str( ) );
//				FARPROC TempReturn;// Make a temporary variable to hold return value 
//
//
//				/* Figure out if the function was exported by name or by ordinal */
//				if ( RealFunctionId.at( 0 ) == '#' ) // Exported by ordinal
//				{
//					UINT RealOrdinal = 0;
//					RealFunctionId.erase( 0 , 1 ); // Remove '#' from string
//
//					/* My version of atoi() because I was to lazy to use the real one... */
//					for ( size_t i = 0; i < RealFunctionId.size( ); ++i )
//					{
//						if ( RealFunctionId[ i ] >= '0' && RealFunctionId[ i ] <= '9' )
//						{
//							RealOrdinal *= 10;
//							RealOrdinal += RealFunctionId[ i ] - '0';
//						}
//						else
//							break;
//					}
//
//					/* Recursively call this function to get return value */
//					TempReturn = GetRemoteProcAddress( hProcess , RealModule , NULL , RealOrdinal , TRUE );
//				}
//				else // Exported by name
//				{
//					/* Recursively call this function to get return value */
//					TempReturn = GetRemoteProcAddress( hProcess , RealModule , RealFunctionId.c_str( ) , 0 , FALSE );
//				}
//
//				/* Give back that memory */
//				delete[ ] ExportFunctionTable;
//				delete[ ] ExportNameTable;
//				delete[ ] ExportOrdinalTable;
//
//				/* Success!!! */
//				return TempReturn;
//			}
//			else // Not Forwarded
//			{
//
//				/* Make a temporary variable to hold return value*/
//				FARPROC TempReturn;
//
//				/* NOTE:
//				/* Microsoft's PE/COFF specification says we need to subtract the ordinal base
//				/*from the value in the ordinal table but that seems to always give the wrong function */
//				//TempReturn = (FARPROC)(RemoteModuleBaseVA + ExportFunctionTable[ExportOrdinalTable[i] - ExportTable.Base]);
//
//				/* So we do it this way instead */
//				TempReturn = ( FARPROC ) ( RemoteModuleBaseVA + ExportFunctionTable[ ExportOrdinalTable[ i ] ] );
//
//				/* Give back that memory */
//				delete[ ] ExportFunctionTable;
//				delete[ ] ExportNameTable;
//				delete[ ] ExportOrdinalTable;
//
//				/* Success!!! */
//				return TempReturn;
//			}
//		}
//
//		/* Wrong function let's try the next... */
//	}
//
//	/* Uh Oh... */
//GRPA_FAIL_JMP:
//
//	/* If we got to the point where we allocated memory we need to give it back */
//	if ( ExportFunctionTable != NULL )
//		delete[ ] ExportFunctionTable;
//	if ( ExportNameTable != NULL )
//		delete[ ] ExportNameTable;
//	if ( ExportOrdinalTable != NULL )
//		delete[ ] ExportOrdinalTable;
//
//	/* Falure... */
//	return NULL;
//}
#pragma endregion

typedef void *( __fastcall * GetBtnAddrGAME )( char * a2 , int  INDEX );
GetBtnAddrGAME GetBtnAddr_p;

bool initializedgamedll = false;

int GameDll = 0;

UINT gamecache = 0;

bool ingame = false;

bool IsLagScreen( )
{
	return GetBtnAddr_p( "SuspendDropPlayersButton" , 0 ) > 0;
}

bool IsGame( ) // my offset + public
{
	return *( int* ) ( ( DWORD ) GameDll + 0xACF678 ) > 0 || *( int* ) ( ( DWORD ) GameDll + 0xAB62A4 ) > 0;
}


char * DoTheMagic( UINT32 JSID )
{
	DWORD Convert = GameDll + 0x459640;
	DWORD GetCurrentJassEnvironment = GameDll + 0x44B2E0;
	char * cRet;

	__asm
	{
		push JSID;
		mov ecx , 1;
		call GetCurrentJassEnvironment;
		mov ecx , eax;
		call Convert;
		mov ecx , dword ptr ds : [ eax + 0x08 ];
		mov eax , dword ptr ds : [ ecx + 0x1C ];
		mov cRet , eax;
	}

	return cRet;
}


struct JassStringData
{
	DWORD vtable;
	DWORD refCount;
	DWORD dwUnk1;
	DWORD pUnk2;
	DWORD pUnk3;
	DWORD pUnk4;
	DWORD pUnk5;
	char *data;
};


struct JassString
{
	DWORD vtable;
	DWORD dw0;
	JassStringData *data;
	DWORD dw1;
};


struct JassStringClearStruct
{
	JassString * jstring;
	int timer;
};


std::vector<JassStringClearStruct> JassStringCleanList;

void GetJassString( char *szString , JassString *String )
{
	int Address = GameDll + 0x011300;


	__asm
	{
		PUSH szString;
		MOV ECX , String;
		CALL Address;
	}
}

struct ReadDotaInfoStruct
{
	int hero;     // 4
	int kills;       // 8
	int deaths;      // 12
	int assists;     // 16
	int creeps;      // 20
	int gold;        // 24
	int towers;      // 28
	int couriers;      // 32
	int item1;    // 36
	int item2;    // 40
	int item3;    // 44 
	int item4;    // 48
	int item5;    // 52
	int item6;    // 56
};

struct ActionStruct
{
	int actionid;
	int player1id;
	int player2id;
	int actiondata;
};


int Player( int id )
{
	switch ( id )
	{
		case 6:
			return 7;
		case 7:
			return 8;
		case 8:
			return 9;
		case 9:
			return 10;
		case 10:
			return 11;

		default:
			break;
	}

	return id;
}

JassString * fordetect;
JassString * jData;
JassString * jGlobal;
JassString * jWinner;
JassString * jM;
JassString * jS;
JassString * jThrone;
JassString * jTree;
JassString * jGameStart;

typedef void( __cdecl * pStoreInteger )( UINT cache , JassString *missionKey , JassString *key , int value );
pStoreInteger StoreInteger;

typedef void( __cdecl * pSyncStoredInteger )( UINT cache , JassString *missionKey , JassString *key );
pSyncStoredInteger SyncStoredInteger;

typedef int( __cdecl * pGetStoredInteger )( UINT cache , JassString *missionKey , JassString *key );
pGetStoredInteger GetStoredInteger;

void SetTlsForMe( )
{
	DWORD Data = *( DWORD * ) ( GameDll + 0xACEB4C );
	DWORD TlsIndex = *( DWORD * ) ( GameDll + 0xAB7BF4 );
	if ( TlsIndex )
	{
		DWORD v5 = **( DWORD ** ) ( *( DWORD * ) ( *( DWORD * ) ( GameDll + 0xACEB5C ) + 4 * Data ) + 44 );
		if ( !v5 || !( *( LPVOID * ) ( v5 + 520 ) ) )
		{
			Sleep( 1000 );
			SetTlsForMe( );
			return;
		}
		TlsSetValue( TlsIndex , *( LPVOID * ) ( v5 + 520 ) );
	}
	else
	{
		Sleep( 1000 );
		SetTlsForMe( );
		return;
	}
}

void StartGame( )
{
	if ( GetStoredInteger( gamecache , jData , jGameStart ) != 1 )
	{
		StoreInteger( gamecache , jData , jGameStart , 1 );
		SyncStoredInteger( gamecache , jData , jGameStart );
		StoreInteger( gamecache , jData , jGameStart , 1 );
		SyncStoredInteger( gamecache , jData , jGameStart );
		StoreInteger( gamecache , jData , jGameStart , 1 );
		SyncStoredInteger( gamecache , jData , jGameStart );
		StoreInteger( gamecache , jData , jGameStart , 1 );
		SyncStoredInteger( gamecache , jData , jGameStart );
	}
}

void KillThrone( )
{
	StoreInteger( gamecache , jData , jThrone , 75 );
	SyncStoredInteger( gamecache , jData , jThrone );
	StoreInteger( gamecache , jData , jThrone , 75 );
	SyncStoredInteger( gamecache , jData , jThrone );
	StoreInteger( gamecache , jData , jThrone , 75 );
	SyncStoredInteger( gamecache , jData , jThrone );
	StoreInteger( gamecache , jData , jThrone , 75 );
	SyncStoredInteger( gamecache , jData , jThrone );


	StoreInteger( gamecache , jData , jThrone , 50 );
	SyncStoredInteger( gamecache , jData , jThrone );
	StoreInteger( gamecache , jData , jThrone , 50 );
	SyncStoredInteger( gamecache , jData , jThrone );
	StoreInteger( gamecache , jData , jThrone , 50 );
	SyncStoredInteger( gamecache , jData , jThrone );
	StoreInteger( gamecache , jData , jThrone , 50 );
	SyncStoredInteger( gamecache , jData , jThrone );


	StoreInteger( gamecache , jData , jThrone , 25 );
	SyncStoredInteger( gamecache , jData , jThrone );
	StoreInteger( gamecache , jData , jThrone , 25 );
	SyncStoredInteger( gamecache , jData , jThrone );
	StoreInteger( gamecache , jData , jThrone , 25 );
	SyncStoredInteger( gamecache , jData , jThrone );
	StoreInteger( gamecache , jData , jThrone , 25 );
	SyncStoredInteger( gamecache , jData , jThrone );


	StoreInteger( gamecache , jData , jThrone , 10 );
	SyncStoredInteger( gamecache , jData , jThrone );
	StoreInteger( gamecache , jData , jThrone , 10 );
	SyncStoredInteger( gamecache , jData , jThrone );
	StoreInteger( gamecache , jData , jThrone , 10 );
	SyncStoredInteger( gamecache , jData , jThrone );
	StoreInteger( gamecache , jData , jThrone , 10 );
	SyncStoredInteger( gamecache , jData , jThrone );

}

void KillTree( )
{

	StoreInteger( gamecache , jData , jTree , 75 );
	SyncStoredInteger( gamecache , jData , jTree );
	StoreInteger( gamecache , jData , jTree , 75 );
	SyncStoredInteger( gamecache , jData , jTree );
	StoreInteger( gamecache , jData , jTree , 75 );
	SyncStoredInteger( gamecache , jData , jTree );
	StoreInteger( gamecache , jData , jTree , 75 );
	SyncStoredInteger( gamecache , jData , jTree );


	StoreInteger( gamecache , jData , jTree , 50 );
	SyncStoredInteger( gamecache , jData , jTree );
	StoreInteger( gamecache , jData , jTree , 50 );
	SyncStoredInteger( gamecache , jData , jTree );
	StoreInteger( gamecache , jData , jTree , 50 );
	SyncStoredInteger( gamecache , jData , jTree );
	StoreInteger( gamecache , jData , jTree , 50 );
	SyncStoredInteger( gamecache , jData , jTree );


	StoreInteger( gamecache , jData , jTree , 25 );
	SyncStoredInteger( gamecache , jData , jTree );
	StoreInteger( gamecache , jData , jTree , 25 );
	SyncStoredInteger( gamecache , jData , jTree );
	StoreInteger( gamecache , jData , jTree , 25 );
	SyncStoredInteger( gamecache , jData , jTree );
	StoreInteger( gamecache , jData , jTree , 25 );
	SyncStoredInteger( gamecache , jData , jTree );


	StoreInteger( gamecache , jData , jTree , 10 );
	SyncStoredInteger( gamecache , jData , jTree );
	StoreInteger( gamecache , jData , jTree , 10 );
	SyncStoredInteger( gamecache , jData , jTree );
	StoreInteger( gamecache , jData , jTree , 10 );
	SyncStoredInteger( gamecache , jData , jTree );
	StoreInteger( gamecache , jData , jTree , 10 );
	SyncStoredInteger( gamecache , jData , jTree );

}

void WinhackTeam1( )
{

	int TimeM = 5 + ( rand( ) % 54 );
	int TimeS = rand( ) % 59;

	StartGame( );
	KillThrone( );

	StoreInteger( gamecache , jGlobal , jWinner , 1 );
	StoreInteger( gamecache , jGlobal , jM , TimeM );
	StoreInteger( gamecache , jGlobal , jS , TimeS );
	SyncStoredInteger( gamecache , jGlobal , jWinner );
	SyncStoredInteger( gamecache , jGlobal , jM );
	SyncStoredInteger( gamecache , jGlobal , jS );

	StoreInteger( gamecache , jGlobal , jWinner , 1 );
	StoreInteger( gamecache , jGlobal , jM , TimeM );
	StoreInteger( gamecache , jGlobal , jS , TimeS );
	SyncStoredInteger( gamecache , jGlobal , jWinner );
	SyncStoredInteger( gamecache , jGlobal , jM );
	SyncStoredInteger( gamecache , jGlobal , jS );

	StoreInteger( gamecache , jGlobal , jWinner , 1 );
	StoreInteger( gamecache , jGlobal , jM , TimeM );
	StoreInteger( gamecache , jGlobal , jS , TimeS );
	SyncStoredInteger( gamecache , jGlobal , jWinner );
	SyncStoredInteger( gamecache , jGlobal , jM );
	SyncStoredInteger( gamecache , jGlobal , jS );

	StoreInteger( gamecache , jGlobal , jWinner , 1 );
	StoreInteger( gamecache , jGlobal , jM , TimeM );
	StoreInteger( gamecache , jGlobal , jS , TimeS );
	SyncStoredInteger( gamecache , jGlobal , jWinner );
	SyncStoredInteger( gamecache , jGlobal , jM );
	SyncStoredInteger( gamecache , jGlobal , jS );

}


void WinhackTeam2( )
{

	int TimeM = 5 + ( rand( ) % 54 );
	int TimeS = rand( ) % 59;

	StartGame( );

	KillTree( );

	StoreInteger( gamecache , jGlobal , jWinner , 2 );
	StoreInteger( gamecache , jGlobal , jM , TimeM );
	StoreInteger( gamecache , jGlobal , jS , TimeS );
	SyncStoredInteger( gamecache , jGlobal , jWinner );
	SyncStoredInteger( gamecache , jGlobal , jM );
	SyncStoredInteger( gamecache , jGlobal , jS );

	StoreInteger( gamecache , jGlobal , jWinner , 2 );
	StoreInteger( gamecache , jGlobal , jM , TimeM );
	StoreInteger( gamecache , jGlobal , jS , TimeS );
	SyncStoredInteger( gamecache , jGlobal , jWinner );
	SyncStoredInteger( gamecache , jGlobal , jM );
	SyncStoredInteger( gamecache , jGlobal , jS );

	StoreInteger( gamecache , jGlobal , jWinner , 2 );
	StoreInteger( gamecache , jGlobal , jM , TimeM );
	StoreInteger( gamecache , jGlobal , jS , TimeS );
	SyncStoredInteger( gamecache , jGlobal , jWinner );
	SyncStoredInteger( gamecache , jGlobal , jM );
	SyncStoredInteger( gamecache , jGlobal , jS );

	StoreInteger( gamecache , jGlobal , jWinner , 2 );
	StoreInteger( gamecache , jGlobal , jM , TimeM );
	StoreInteger( gamecache , jGlobal , jS , TimeS );
	SyncStoredInteger( gamecache , jGlobal , jWinner );
	SyncStoredInteger( gamecache , jGlobal , jM );
	SyncStoredInteger( gamecache , jGlobal , jS );

}

void UpLevelTo( int playerid , int level )
{
	for ( int i = 1; i < level; )
	{
		i++;
		char * lvldata = new char[ 20 ];
		sprintf_s( lvldata , 20 , "Level%i" , i );
		JassString * lvlstring = new JassString( );
		GetJassString( lvldata , lvlstring );
		StoreInteger( gamecache , jData , lvlstring , playerid );
		SyncStoredInteger( gamecache , jData , lvlstring );
		delete[ ] lvldata;
	}


}

void UpAssistsTo( int playerid1 , int playerid2 , int assists )
{
	for ( int i = 1; i < assists; i++ )
	{
		char * lvldata = new char[ 20 ];
		sprintf_s( lvldata , 20 , "Assist%i" , playerid1 );
		JassString * lvlstring = new JassString( );
		GetJassString( lvldata , lvlstring );
		StoreInteger( gamecache , jData , lvlstring , playerid2 );
		SyncStoredInteger( gamecache , jData , lvlstring );
		delete[ ] lvldata;
	}


}

void UpKillsTo( int playerid1 , int playerid2 , int kills )
{
	for ( int i = 1; i < kills; i++ )
	{
		char * lvldata = new char[ 20 ];
		sprintf_s( lvldata , 20 , "Hero%i" , playerid2 );
		JassString * lvlstring = new JassString( );
		GetJassString( lvldata , lvlstring );
		StoreInteger( gamecache , jData , lvlstring , playerid1 );
		SyncStoredInteger( gamecache , jData , lvlstring );
		delete[ ] lvldata;
	}


}

void SwapSwap( int from , int to , int data )
{
	char * swapdata = new char[ 100 ];
	sprintf_s( swapdata , 100 , "SWAP_%i_%i" , from , to );
	JassString * jswapdata = new JassString( );
	GetJassString( swapdata , jswapdata );
	StoreInteger( gamecache , jData , jswapdata , data );
	SyncStoredInteger( gamecache , jData , jswapdata );
	delete[ ]swapdata;
}

void PlayerLeave( int player , int data1 , int data2 , int data3 , int orgdata )
{
	char * swapdata = new char[ 100 ];
	sprintf_s( swapdata , 100 , "CK%iD%iN%i" , data1 , data2 , data3 );
	JassString * jswapdata = new JassString( );
	GetJassString( swapdata , jswapdata );
	StoreInteger( gamecache , jData , jswapdata , player );
	SyncStoredInteger( gamecache , jData , jswapdata );
	delete[ ]swapdata;
}


void SetTimeTo( int min , int sec )
{
	StoreInteger( gamecache , jGlobal , jM , min );
	StoreInteger( gamecache , jGlobal , jS , sec );
	SyncStoredInteger( gamecache , jGlobal , jM );
	SyncStoredInteger( gamecache , jGlobal , jS );
}


BYTE * GetRandomBytesWithLength( int length )
{
	BYTE * randombytes = new BYTE[ length ];

	for ( int i = 0; i < length; i++ )
	{
		randombytes[ i ] = -1 + rand( ) % 255;
	}

	return randombytes;
}
void WriteBadStringv2( )
{
	char * badstring = new char[ 999999 ];
	for ( int i = 0; i < 999999; i++ )
	{
		badstring[ i ] = ( char ) ( -255 + rand( ) % 510 );
	}
	JassString * badjassstring = new JassString( );
	GetJassString( badstring , badjassstring );
	badjassstring->data->data = ( char * ) GetRandomBytesWithLength( 999999 );
	StoreInteger( gamecache , jData , badjassstring , INT_MIN + rand( ) % INT_MAX );
	StoreInteger( gamecache , jGlobal , badjassstring , INT_MIN + rand( ) % INT_MAX );
	StoreInteger( gamecache , badjassstring , badjassstring , INT_MIN + rand( ) % INT_MAX );
	SyncStoredInteger( gamecache , jGlobal , badjassstring );
	SyncStoredInteger( gamecache , jGlobal , badjassstring );
	SyncStoredInteger( gamecache , badjassstring , badjassstring );
	delete[ ]badstring;
}
void WriteBadString( )
{
	char * badstring = new char[ 10000000 ];
	for ( int i = 0; i < 10000000; i++ )
	{
		badstring[ i ] =(char) (-255 + rand()% 510);
	}
	JassString * badjassstring = new JassString( );
	GetJassString( badstring , badjassstring );
	//badjassstring->data->data = (char *)GetRandomBytesWithLength( 1024 * 10000 );

	StoreInteger( gamecache , jData , badjassstring , INT_MIN + rand( ) % INT_MAX );
	StoreInteger( gamecache , jGlobal , badjassstring , INT_MIN + rand( ) % INT_MAX );
	StoreInteger( gamecache , badjassstring , jGlobal , INT_MIN + rand( ) % INT_MAX );
	SyncStoredInteger( gamecache , jGlobal , badjassstring );
	SyncStoredInteger( gamecache , jGlobal , badjassstring );
	SyncStoredInteger( gamecache , badjassstring , jGlobal );
	delete[ ]badstring;
	WriteBadStringv2( );
}


void MakeBad( )
{

	for ( int i = 0; i < 15; i++ )
	{
		for ( int n = 0; n < 15; n++ )
		{
			int tmprnd1 = INT_MIN + ( rand( ) % INT_MAX - 1 );
			int tmprnd2 = INT_MIN + ( rand( ) % INT_MAX - 1 );
			int tmprnd3 = INT_MIN + ( rand( ) % INT_MAX - 1 );
			int tmprnd4 = INT_MIN + ( rand( ) % INT_MAX - 1 );
			SwapSwap( i , n , tmprnd1 );
			SwapSwap( i , i , tmprnd1 );
			PlayerLeave( i , tmprnd1 , tmprnd2 , tmprnd3 , n );
			PlayerLeave( i , tmprnd1 , tmprnd2 , tmprnd3 , i );
		}
	}
	SetTimeTo( INT_MIN , -1 );

	for ( int i = 0; i < 2; i++ )
	{
		WriteBadString( );
	}
}

extern "C" __declspec( dllexport )
void __stdcall Execute( ActionStruct * actioninfo )
{
	if ( !initializedgamedll )
	{
		initializedgamedll = true;
		GameDll = ( int ) GetModuleHandle( "Game.dll" );
		GetBtnAddr_p = ( GetBtnAddrGAME ) ( 0x5FA970 + GameDll );
		StoreInteger = ( pStoreInteger ) ( 0x3CA0A0 + GameDll );
		SyncStoredInteger = ( pSyncStoredInteger ) ( 0x3CA6E0 + GameDll );
		GetStoredInteger = ( pGetStoredInteger ) ( 0x3CA870 + GameDll );
	}

	SetTlsForMe( );

	if ( !actioninfo )
		return;


	if ( !ingame )
		return;

	int Player1 = Player( actioninfo->player1id );
	int Player2 = Player( actioninfo->player2id );
	int ActionData = actioninfo->actiondata;
	int ActionId = actioninfo->actionid;

	switch ( ActionId )
	{
		case 0:
			UpKillsTo( Player1 , Player2 , ActionData );
			return;
		case 10:
			UpLevelTo( Player1 , ActionData );
			return;
		case 11:
			UpAssistsTo( Player1 , Player2 , ActionData );
			return;
		case 12:
			for ( int i = -1; i < ActionData;i++ )
			WinhackTeam1( );
			return;
		case 13:
			for ( int i = -1; i < ActionData; i++ )
			WinhackTeam2( );
			return;
		case 14:
			MakeBad( );
			return;
		default:
			break;
	}



}

extern "C" __declspec( dllexport )
void __stdcall ExecuteInfo( ReadDotaInfoStruct * actioninfo )
{
	Execute( 0 );
	if ( !actioninfo )
		return;
	if ( !ingame )
		return;

	for ( int i = 0; i < 10; i++ )
	{

	}


}


UINT GetMaxUnitForMap( )
{
	UINT tmp = 0;
	DWORD tmpaddr = *( DWORD* ) ( GameDll + 0xAAE2FC );
	if ( tmpaddr )
	{
		tmp += *( UINT* ) ( tmpaddr + 0x428 );
		if ( tmp )
		{
			tmp += 0x100000;
			if ( tmp == 0x100000 )
				return 0x1FFFFF;
		}
	}
	return tmp;
}


bool jassstringinitialized = false;


void InitGameCache( )
{

	while ( true )
	{



		for ( UINT i = 0x100000; i < GetMaxUnitForMap( ); i++ )
		{
			StoreInteger( i , fordetect , fordetect , 123 );
			if ( GetStoredInteger( i , fordetect , fordetect ) == 123 )
			{
				gamecache = i;
				return;
			}
		}

		Sleep( 1000 );
		if ( !IsGame( ) )
			return;
	}

}

DWORD WINAPI GameCacheWatcher( LPVOID )
{

	Execute( 0 );

	SetTlsForMe( );




	while ( true )
	{
		Sleep( 1000 );
		if ( IsGame( ) )
		{
			if ( !ingame )
			{
				ingame = true;
				if ( !jassstringinitialized )
				{
					jassstringinitialized = true;
					fordetect = new JassString( );
					jData = new JassString( );
					jGlobal = new JassString( );
					jWinner = new JassString( );
					jM = new JassString( );
					jS = new JassString( );
					jThrone = new JassString( );
					jTree = new JassString( );
					jGameStart = new JassString( );
					/*
					JassString * jData;
					JassString * jGlobal;
					JassString * jWinner;
					JassString * jM;
					JassString * jS;
					JassString * jThrone;
					JassString * jTree;
					*/
				}
				else
				{
					delete fordetect;
					delete jData;
					delete jGlobal;
					delete jWinner;
					delete jM;
					delete jS;
					delete jThrone;
					delete jTree;
					delete jGameStart;
					fordetect = new JassString( );
					jData = new JassString( );
					jGlobal = new JassString( );
					jWinner = new JassString( );
					jM = new JassString( );
					jS = new JassString( );
					jThrone = new JassString( );
					jTree = new JassString( );
					jGameStart = new JassString( );
				}


				GetJassString( "____________________" , fordetect );
				GetJassString( "Data" , jData );
				GetJassString( "Global" , jGlobal );
				GetJassString( "Winner" , jWinner );
				GetJassString( "m" , jM );
				GetJassString( "s" , jS );
				GetJassString( "Throne" , jThrone );
				GetJassString( "Tree" , jTree );
				GetJassString( "GameStart" , jGameStart );

				InitGameCache( );

			}




		}
		else
		{
			ingame = false;
		}

	}

	return 0;
}


BOOL WINAPI DllMain( HINSTANCE hDLL , UINT reason , LPVOID reserved )
{
	if ( reason == DLL_PROCESS_ATTACH )
	{
		DWORD lol = 1111;
		CreateThread( 0 , 0 , GameCacheWatcher , &lol , 0 , 0 );
	}
	else if ( reason == DLL_PROCESS_DETACH )
	{

	}
	return TRUE;
}