#pragma once

#include <windows.h>
#include "resource.h"

void playNoise() {
	// res: IDR_WAVE1
	PlaySound((LPSTR)IDR_WAVE1, NULL, SND_ASYNC | SND_RESOURCE | SND_LOOP);
}