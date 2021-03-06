#pragma once
#include "pch.h"
//#include <vld.h>
#ifdef BL_PLATFORM_WINDOWS
//#define _CRTDBG_MAP_ALLOC
#include <iostream>

extern Balbino::Application* Balbino::CreateApplication();
//#undef main

void StartHeapControl();
void DumpMemoryLeaks();

int main( int arc, char* argv[] )
{
	(void) arc;
	(void) argv;

	StartHeapControl();
#ifdef _DEBUG
	_CrtMemState s1{}, s2{}, s3{};
	_CrtMemCheckpoint( &s1 );
#endif // _DEBUG
	auto pApp = Balbino::CreateApplication();
	try
	{
		pApp->Initialize();
		pApp->Run();
	}
	catch ( const std::exception& e )
	{
		std::cout << e.what();
	}
	delete pApp;
#ifdef _DEBUG
	if ( _CrtMemDifference( &s3, &s1, &s2 ) )
		_CrtMemDumpStatistics( &s3 );
#endif // _DEBUG

	DumpMemoryLeaks();

	return 0;
}

inline void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	//HeapSetInformation( NULL, HeapEnableTerminationOnCorruption, NULL, 0 );

	// Report detected leaks when the program exits
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 3957 );
#endif
}

inline void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
}
#endif // BL_PLATFORM_WINDOWS