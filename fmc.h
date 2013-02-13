/*
 * fmc.h
 *
 * SSG B748 PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
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
/*PLUGIN DESCRIPTION */
static const char* PluginName = "SSG B748";
static const char* PluginSig = "SSG.B748.fmc";
static const char* PluginDesc =
		"SSG B748 by Pericles L. Machado "
		"<pericles.raskolnikoff@gmail.com>\n"
		" to Supercritical Simulation Group";

//================================================================================================//
/*PLUGIN ENTRY */
#ifdef __cplusplus
extern "C" {
#endif

PLUGIN_API int XPluginStart(char* outName, char* outSignature, char* outDescription);
PLUGIN_API void XPluginStop(void);
PLUGIN_API int XPluginEnable(void);
PLUGIN_API void XPluginDisable(void);
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, long inMessage, void* inParam);

#ifdef __cplusplus
}
#endif


#endif //_FMC_H_

