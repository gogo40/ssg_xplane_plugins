/*
 * PluginCallBacks.cpp
 *
 * SSG B748 PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#include "utils.h"
#include "PluginCallBacks.h"
#include "PluginDataRef.h"

//================================================================================================//
/*Plugin callback*/


namespace SSG_B748 {

void	PluginMenuHandlerCallback(
		void* inMenuRef,
		void* inItemRef)
{
	PLUGINDEBUGBEGIN("PluginMenuHandlerCallback");

	/* This is the menu handler.  We will go through each plugin. */
	long n;

	for (n = 0; n < XPLMCountPlugins(); ++n) {
		PLUGINDEBUGDOOPERATION(char	str[128]);
		XPLMPluginID	plugin = XPLMGetNthPlugin(n);
		XPLMPluginID	me = XPLMGetMyID();

		/* Check to see if the plugin is us.  If so, don't
	   * disable ourselves! */
		PLUGINDEBUGDOOPERATION(sprintf(str,"plugin=%d,me=%d\n",plugin, me));
		PLUGINDEBUG(str);

		if (plugin != me) {
			/* Disable based on the item ref for the menu. */
			if (inItemRef == NULL) {
				XPLMDisablePlugin(plugin);
			} else {
				XPLMEnablePlugin(plugin);
			}
		}
	}

	PLUGINDEBUGEND("PluginMenuHandlerCallback");
}

void PluginDataChangedCallback(void* refcon)
{
	PLUGINDEBUGBEGIN("PluginDataChangedCallback");

	if (refcon) {
		PluginDataRef* m_data_ref = reinterpret_cast<PluginDataRef*>(refcon);
		m_data_ref->update();
	}

	PLUGINDEBUGEND("PluginDataChangedCallback");
}

float PluginGetFloat(void* refcon)
{
	PLUGINDEBUGBEGIN("PluginGetFloat");

	float* my_var = static_cast<float*>(refcon);

	PLUGINDEBUGEND("PluginGetFloat");
	return *my_var;
}

void  PluginSetFloat(void* inRefcon, float inValue)
{
	PLUGINDEBUGBEGIN("PluginSetFloat");

	float* my_var = static_cast<float*>(inRefcon);
	*my_var = inValue;

	PLUGINDEBUGEND("PluginSetFloat");
}

} //namespace SSG_B748
