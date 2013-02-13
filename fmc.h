/*
 * fmc.h
 *
 * SSG B748 PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#ifndef _FMC_H_
#define _FMC_H_

#if APL
#if defined(__MACH__)
#include <Carbon/Carbon.h>
#endif
#endif

#include <cstdio>
#include <cstring>
#include <cmath>

#include <XPLMPlugin.h>
#include <XPLMProcessing.h>
#include <XPLMDataAccess.h>
#include <XPLMUtilities.h>
#include <XPLMMenus.h>

//================================================================================================//
/* PLUGIN ENTRY */

extern "C" PLUGIN_API int XPluginStart(char* outName, char* outSignature, char* outDescription);
extern "C" PLUGIN_API void XPluginStop(void);
extern "C" PLUGIN_API int XPluginEnable(void);
extern "C" PLUGIN_API void XPluginDisable(void);
extern "C" PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, long inMessage, void* inParam);



namespace SSG_B748 {

//================================================================================================//
/*PLUGIN DESCRIPTION */

const char* PluginName = "SSG B748";
const char* PluginNameLog = "SSG_B748_log.txt";
const char* PluginSig = "SSG.B748.fmc";
const char* PluginDesc =
		"SSG B748 by Pericles L. Machado "
		"<pericles.raskolnikoff@gmail.com>\n"
		"(c) 2013 Supercritical Simulation Group";

} // namespace SSG_B748


#endif //_FMC_H_

