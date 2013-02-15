/*
 * utils.h
 *
 * SSG PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include "SSGB748.h"


// Disables copy constructor and copy assignment
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);             \
	void operator=(const TypeName&)

//================================================================================================//
/*DEBUG OPERATIONS*/


#if DEBUGMODE
	#define PLUGINDEBUGDOOPERATION(s) \
		s
	#define PLUGINDEBUG(s) \
	SSG_PLUGIN::debug(s); 
	
	#define PLUGINDEBUGPRINTINT(s, i) \
	SSG_PLUGIN::debug(s, i)

	#define PLUGINDEBUGBEGIN(s) \
	PLUGINDEBUG("BEGIN function " \
					s \
					"()\n");

	#define PLUGINDEBUGEND(s) \
	PLUGINDEBUG("END function " \
				s \
				"()\n");
#else
	#define PLUGINDEBUGDOOPERATION(s)
	#define PLUGINDEBUG(s)
	#define PLUGINDEBUGPRINTINT(s, i)
	#define PLUGINDEBUGBEGIN(s)
	#define PLUGINDEBUGEND(s)
#endif


//================================================================================================//
/*UTILS*/

namespace SSG_PLUGIN {
#if APL && __MACH__
	int ConvertPath(const char* inPath, char* outPath, int outPathMaxLen);
#endif

#if DEBUGMODE
	void debug(const char* message);
	void debug(const char* message, int value);
#endif

	void pluginMessage(const char* message);

} // namespace SSG_PLUGIN

#if IBM
#include <windows.h>
#endif

#endif //_UTILS_H_

