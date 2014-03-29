#ifndef FILESYS_PREPROCESSOR_H_INCLUDED
#define FILESYS_PREPROCESSOR_H_INCLUDED




	#ifdef _WIN32
		#include <windows.h>
	 	#define __FSYS__ WINDOWS
		#define	__FSYS__UNSUPPORTED_OS false;
	
	#elif __unix__
		#include <unistd.h>
	 	#include <dirent.h>
		#include <sys/stat.h>
		#include <sys/types.h>
		#define __FSYS__ UNIX_VARIANT
		#define __FSYS__UNSUPPORTED_OS true;
	#endif
	#if !defined(__FSYS__)
		#define __FSYS__UNSUPPORTED_OS true;
		#define __FSYS__ UNKNOWN
		#error Filesys: Unknown or unsupported operating system. Make sure you compile with your operating system specified. Supported OS defines: _WIN32 __unix__	
	#endif




#endif
