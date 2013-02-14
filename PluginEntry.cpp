/*
 * fmc.cpp
 *
 * SSG B748 PLUGIN
 *
 * Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
 *					  -- Supercritical Simulation Group
 */

#include "utils.h"
#include "PluginEntry.h"
#include "PluginCallBacks.h"
#include "PluginDataRef.h"

namespace SSG_B748 {

//================================================================================================//
/*PLUGIN DATA*/
/* File to write data to. */
FILE* g_output_file = 0;
//================================================================================================//
/* Data refs we will record. */
PluginDataRef* g_data_ref = 0;

} // namespace SSG_B748

//================================================================================================//
/*PLUGIN ENTRY*/
PLUGIN_API int XPluginStart(
	char* outName,
	char* outSig,
	char* outDesc)
{
	PLUGINDEBUGBEGIN("XPluginStart");

	::strcpy(outName, PluginName);
	::strcpy(outSig, PluginSig);
	::strcpy(outDesc, PluginDesc);

	PLUGINDEBUGEND("XPluginStart");
	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
	PLUGINDEBUGBEGIN("XPluginStop");

	/* Unregister data */
	if (SSG_B748::g_data_ref) {
		delete SSG_B748::g_data_ref;
		SSG_B748::g_data_ref = 0;
	}

	/* Close the file */
	if (SSG_B748::g_output_file) {
		fclose(SSG_B748::g_output_file);
		SSG_B748::g_output_file = 0;
	}

	PLUGINDEBUGEND("XPluginStop");
}

PLUGIN_API void XPluginDisable(void)
{
	PLUGINDEBUGBEGIN("XPluginDisable");

	if (SSG_B748::g_output_file) {
		fflush(SSG_B748::g_output_file);
	}

	PLUGINDEBUGEND("XPluginDisable");
}

PLUGIN_API int XPluginEnable(void)
{
	PLUGINDEBUGBEGIN("XPluginEnable");

	PluginInit();

	PLUGINDEBUGEND("XPluginEnable");

	return 1;
}

static void PluginInit()
{
	PLUGINDEBUGBEGIN("PluginInit");

	PLUGINDEBUG("Loading plugin...(PluginInit())\n");

	PLUGINDEBUG("\tCreating and loading data refs...(PluginInit())\n");

	/* Find the data refs we want to record. */
	if (!SSG_B748::g_data_ref) {
		SSG_B748::g_data_ref = new SSG_B748::PluginDataRef;
	}

	SSG_B748::g_data_ref->StartProcessTime(1);
	SSG_B748::g_data_ref->create();
	SSG_B748::g_data_ref->get();

	PLUGINDEBUG("\tCreating and loading data refs...(PluginInit())[OK]\n");

	char	 outputPath[255];

	#if APL && __MACH__
	char outputPath2[255];
	int Result = 0;
	#endif

	/* Open a file to write to.  We locate the X-System directory
	 * and then concatenate our file name.  This makes us save in
	 * the X-System directory.  Open the file.
	 */
	XPLMGetSystemPath(outputPath);
	strcat(outputPath, PluginNameLog);

	PLUGINDEBUG("\tEnabling plugin...(PluginInit())\n");
	//XPLMEnablePlugin(XPLMGetMyID());
	PLUGINDEBUG("\tEnabling plugin...(PluginInit())[OK]\n");

	#if APL && __MACH__
	Result = SSG_B748::ConvertPath(outputPath, outputPath2, sizeof(outputPath));
	if (Result == 0) {
		strcpy(outputPath, outputPath2);
	} else {
		#if DEBUGMODE
		PLUGINDEBUG("Unable to convert path(PluginInit())\n");
		#endif
	}
	#endif


	#if DEBUGMODE
	PLUGINDEBUG("\tOpenning plugin output file...(PluginInit())\n");
	if (!SSG_B748::g_output_file) {
		SSG_B748::g_output_file = fopen(outputPath, "w");
	}
	PLUGINDEBUG("\tOpenning plugin output file...(PluginInit())[OK]\n");
	#endif


	PLUGINDEBUG("\tCreating Menu item...(PluginInit())\n");
	//XPLMMenuID	myMenu;
	int			mySubMenuItem;



	mySubMenuItem = XPLMAppendMenuItem(
						XPLMFindPluginsMenu(),	/* Put in plugins menu */
						PluginName,				/* Item Title */
						0,						/* Item Ref */
						1);						/* Force English */

	//myMenu =
			XPLMCreateMenu(
						PluginName,
						XPLMFindPluginsMenu(),
						mySubMenuItem,							/* Menu Item to attach to. */
						SSG_B748::PluginMenuHandlerCallback,	/* The handler */
						0);										/* Handler Ref */

	PLUGINDEBUG("\tCreating Menu item...(PluginInit())[OK]\n");

	PLUGINDEBUG("Loading plugin...(PluginInit())[OK]\n");

	PLUGINDEBUGEND("PluginInit");
}

PLUGIN_API void XPluginReceiveMessage(
	XPLMPluginID	inFromWho,
	long	 inMessage,
	void* inParam)
{
	PLUGINDEBUGBEGIN("XPluginReceiveMessage");

	if (inFromWho == XPLM_PLUGIN_XPLANE) {
		switch (inMessage) {
			case XPLM_MSG_PLANE_LOADED:
				PLUGINDEBUG("Message XPML_MSG_PLANE_LOADED received"
							"...(XPluginReceiveMessage())\n");
				PLUGINDEBUG("Call PluginInit()...(XPluginReceiveMessage())\n");

				PluginInit();

				PLUGINDEBUG("Call PluginInit()...(XPluginReceiveMessage())[OK]\n");
			break;
		}
	}

	PLUGINDEBUGEND("XPluginReceiveMessage");
}

