/*
 * PluginData.cpp
 *
 * SSG PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#include "utils.h"

#include "PluginData.h"
#include "PluginCallBacks.h"

namespace SSG_PLUGIN {

XPLMDataRef PluginLoadFloat(const char* name, void* refcon, XPLMDataChanged_f callback)
{
	PLUGINDEBUGBEGIN("PluginLoadFloat");

	if (callback == 0) {
		XPLMShareData(name, xplmType_Float, PluginDataChangedCallback, refcon);
	} else {
		XPLMShareData(name, xplmType_Float, callback, refcon);
	}

	PLUGINDEBUGEND("PluginLoadFloat");

	return XPLMFindDataRef(name);
}

void PluginRemoveFloat(const char* name, void* refcon)
{
	PLUGINDEBUGBEGIN("PluginRemoveFloat");

	XPLMUnshareData(name, xplmType_Float, PluginDataChangedCallback, refcon);

	PLUGINDEBUGEND("PluginRemoveFloat");
}

} // namespace SSG_PLUGIN

//*
//gOwnedDataRef = XPLMRegisterDataAccessor(
//								"xplanesdk/examples/sharedata/number",
//								xplmType_Float + xplmType_Double,			/* The types we support */
//								1,											/* Writable */
//								NULL, NULL,									/* No accessors for ints */
//								MyGetDatafCallback, MySetDatafCallback,		/* Accessors for floats */
//								MyGetDatadCallback, MySetDatadCallback,		/* Accessors for doubles */
//								NULL, NULL,									/* No accessors for int arrays */
//								NULL, NULL,									/* No accessors for float arrays */
//								NULL, NULL,									/* No accessors for raw data */
//								NULL, NULL);								/* Refcons not used */
//*/


