#include "Events.h"
#include "ENBAOToggler.h"

void Events::Register()
{
	cellLoadEventHandler::Register();
}

RE::BSEventNotifyControl cellLoadEventHandler::ProcessEvent(const RE::TESCellFullyLoadedEvent*, RE::BSTEventSource<RE::TESCellFullyLoadedEvent>*)
{
	ENBAOToggler::GetSingleton()->UpdateSettings();
	return RE::BSEventNotifyControl::kContinue;
}
