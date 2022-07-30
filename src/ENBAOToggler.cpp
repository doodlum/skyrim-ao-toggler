#include "ENBAOToggler.h"

void ENBAOToggler::LoadJSON()
{
	mtx.lock();
	std::ifstream i(L"Data\\SKSE\\Plugins\\ENBAOToggler.json");
	i >> JSONSettings;
	enabled = JSONSettings["Enabled"];
	mtx.unlock();
}

void ENBAOToggler::SaveJSON()
{
	mtx.lock();
	std::ofstream o(L"Data\\SKSE\\Plugins\\ENBAOToggler.json");
	JSONSettings["Enabled"] = enabled;
	o << JSONSettings.dump(1);
	mtx.unlock();
}


void ENBAOToggler::UpdateENBParams()
{
	if (enabled){
		ENB_SDK::ENBParameter param;

		param.Type = ENB_SDK::ENBParameterType::ENBParam_BOOL;
		param.Size = ENBParameterTypeToSize(param.Type);

		memcpy(param.Data, &AOEnabled, param.Size);
		g_ENB->SetParameter("enbseries.ini", "EFFECT", "EnableAmbientOcclusion", &param);
	}
}

void ENBAOToggler::UpdateSettings()
{
	auto player = RE::PlayerCharacter::GetSingleton();
	if (auto cell = player->GetParentCell()) {
		if (cell->IsInteriorCell()) {
			mtx.lock();
			std::set<std::string> interiorExclusionList = JSONSettings["Interior"]["Exclusions"];	
			AOEnabled =!interiorExclusionList.contains(cell->GetFormEditorID());
			mtx.unlock();
		} else if (auto worldspace = player->GetWorldspace()) {
			mtx.lock();
			std::set<std::string> exteriorExclusionList = JSONSettings["Worldspace"]["Exclusions"];
			AOEnabled = !exteriorExclusionList.contains(worldspace->GetFormEditorID());
			mtx.unlock();
		} else {
			AOEnabled = true;
		}
	}
}

void ENBAOToggler::UpdateUI()
{
	auto bar = g_ENB->TwGetBarByEnum(ENB_API::ENBWindowType::GeneralWindow);
	g_ENB->TwAddVarRW(bar, "Enabled", ETwType::TW_TYPE_BOOLCPP, &enabled, "group=MOD:ENBAOToggler");
}
