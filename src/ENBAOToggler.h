#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "API/ENBSeriesAPI.h"
#include <shared_mutex>

class ENBAOToggler 
{
public:
	static ENBAOToggler* GetSingleton()
	{
		static ENBAOToggler handler;
		return &handler;
	}

	ENB_API::ENBSDKALT1001* g_ENB = nullptr;
	std::shared_mutex 		mtx;
	json 					JSONSettings;

	bool enabled	= true;
	bool AOEnabled	= true;

	void LoadJSON();
	void SaveJSON();

	void UpdateENBParams();     
	void UpdateSettings();
	void UpdateUI();


private:
	ENBAOToggler() {
	};

	ENBAOToggler(const ENBAOToggler&) = delete;
	ENBAOToggler(ENBAOToggler&&) = delete;

	~ENBAOToggler() = default;

	ENBAOToggler& operator=(const ENBAOToggler&) = delete;
	ENBAOToggler& operator=(ENBAOToggler&&) = delete;
};
