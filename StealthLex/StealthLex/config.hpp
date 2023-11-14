#pragma once

#include <iostream>

namespace config
{
	inline bool hasInjected = false;
	inline std::string dbgSym = "*"; //Will print: [dbgSym] Message 
									 //[*] had esex with nicholas1110 :3
}

namespace injectionConfig
{
	inline int injectionBind;
	inline bool beepOnInjection;
	inline int beepFreq;
	inline int beepDur;
}

namespace uninjectConfig
{
	inline int uninjectBind;
	inline bool beepOnUninjection;
	inline int beepFreq;
	inline int beepDur;
}

namespace deleteTracesConfig
{
	inline int deleteTracesBind;
	inline bool beepOnDeleteTraces;
	inline int beepFreq;
	inline int beepDur;
}
