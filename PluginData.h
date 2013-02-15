/*
 * PluginData.h
 *
 * SSG PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#ifndef _PLUGINDATA_H_
#define _PLUGINDATA_H_

#include <XPLMDataAccess.h>

namespace SSG_PLUGIN {

XPLMDataRef PluginLoadFloat(const char* name, void* refcon = 0,
							XPLMDataChanged_f callback = 0);
void PluginRemoveFloat(const char* name, void* refcon = 0);

} // namespace SSG_PLUGIN

#endif // _PLUGINCALLBACKS_H_
