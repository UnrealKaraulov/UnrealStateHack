typedef void( __stdcall * Callback )( int offset );

Callback Handler = 0;

extern "C" __declspec( dllexport )
void __stdcall InitLocator( Callback handler )
{
	Handler = handler;
}

extern "C" __declspec( dllexport )
void __stdcall DotaStateLocationAt( int * offset)
{
	if ( Handler != 0 )
		Handler( *offset );
}