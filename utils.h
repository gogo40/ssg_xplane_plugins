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

//================================================================================================//
/*UTILS*/
#if APL && __MACH__
int ConvertPath(const char* inPath, char* outPath, int outPathMaxLen);
#endif

#endif //_UTILS_H_

