/*
 * utils.h
 *
 * SSG B748 PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include "SSGB748.h"

namespace SSG_B748 {
//================================================================================================//
/*UTILS*/
#if APL && __MACH__
	int ConvertPath(const char* inPath, char* outPath, int outPathMaxLen);
#endif

#if DEBUGMODE
	void debug(const char* message);
#endif


} // namespace SSG_B748

#endif //_UTILS_H_

