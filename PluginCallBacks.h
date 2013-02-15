/*
 * PluginCallBacks.h
 *
 * SSG PLUGIN
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

namespace SSG_PLUGIN {

void PluginMenuHandlerCallback(void*, void*);
void PluginDataChangedCallback(void*);
float PluginGetFloat(void*);
void  PluginSetFloat(void*, float);

} // namespace SSG_PLUGIN

#endif //_PLUGINCALLBACKS_H_

