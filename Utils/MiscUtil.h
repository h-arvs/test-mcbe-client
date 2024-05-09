#pragma once
#include <string>
#include <winrt/windows.storage.h>

namespace MiscUtil {
	static std::string GetRoamingState() {
		auto roamingFolder = winrt::Windows::Storage::ApplicationData::Current().RoamingFolder();
		auto path = std::wstring(roamingFolder.Path());
		auto string = std::string(path.begin(), path.end());
		return string;
	}
}