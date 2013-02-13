/*
 * PluginCallBacks.h
 *
 * SSG B748 PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#ifndef _PLUGINCALLBACKS_H_
#define _PLUGINCALLBACKS_H_


#include <cstdio>
#include <cstring>
#include <cmath>

#include <XPLMPlugin.h>
#include <XPLMProcessing.h>
#include <XPLMDataAccess.h>
#include <XPLMUtilities.h>
#include <XPLMMenus.h>

//================================================================================================//
/*PLUGIN CALLBACKS */
void PluginDataChangedCallback(void*);
float PluginFlightLoopCallback(float, float, int, void*);
float PluginGetFloat(void*);
void  PluginSetFloat(void*, float);

#endif //_PLUGINCALLBACKS_H_

