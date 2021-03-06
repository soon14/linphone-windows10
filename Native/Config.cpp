/*
Config.cpp
Copyright (C) 2015  Belledonne Communications, Grenoble, France
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "ApiLock.h"
#include "Config.h"

bool BelledonneCommunications::Linphone::Native::Config::GetBool(Platform::String^ section, Platform::String^ key, bool defaultValue)
{
	return (GetInt(section, key, defaultValue) == TRUE);
}

void BelledonneCommunications::Linphone::Native::Config::SetBool(Platform::String^ section, Platform::String^ key, bool value)
{
	SetInt(section, key, (int)value);
}

int BelledonneCommunications::Linphone::Native::Config::GetInt(Platform::String^ section, Platform::String^ key, int defaultValue)
{
	API_LOCK;
	const char *ccSection = Utils::pstoccs(section);
	const char *ccKey = Utils::pstoccs(key);
	int value = lp_config_get_int(this->config, ccSection, ccKey, defaultValue);
	delete(ccKey);
	delete(ccSection);
	return value;
}

void BelledonneCommunications::Linphone::Native::Config::SetInt(Platform::String^ section, Platform::String^ key, int value)
{
	API_LOCK;
	const char *ccSection = Utils::pstoccs(section);
	const char *ccKey = Utils::pstoccs(key);
	lp_config_set_int(this->config, ccSection, ccKey, value);
	delete(ccKey);
	delete(ccSection);
}

int64 BelledonneCommunications::Linphone::Native::Config::GetInt64(Platform::String^ section, Platform::String^ key, int64 defaultValue)
{
	API_LOCK;
	const char *ccSection = Utils::pstoccs(section);
	const char *ccKey = Utils::pstoccs(key);
	int64 value = lp_config_get_int64(this->config, ccSection, ccKey, defaultValue);
	delete(ccKey);
	delete(ccSection);
	return value;
}

void BelledonneCommunications::Linphone::Native::Config::SetInt64(Platform::String^ section, Platform::String^ key, int64 value)
{
	API_LOCK;
	const char *ccSection = Utils::pstoccs(section);
	const char *ccKey = Utils::pstoccs(key);
	lp_config_set_int64(this->config, ccSection, ccKey, value);
	delete(ccKey);
	delete(ccSection);
}

float BelledonneCommunications::Linphone::Native::Config::GetFloat(Platform::String^ section, Platform::String^ key, float defaultValue)
{
	API_LOCK;
	const char *ccSection = Utils::pstoccs(section);
	const char *ccKey = Utils::pstoccs(key);
	float value = lp_config_get_float(this->config, ccSection, ccKey, defaultValue);
	delete(ccKey);
	delete(ccSection);
	return value;
}

void BelledonneCommunications::Linphone::Native::Config::SetFloat(Platform::String^ section, Platform::String^ key, float value)
{
	API_LOCK;
	const char *ccSection = Utils::pstoccs(section);
	const char *ccKey = Utils::pstoccs(key);
	lp_config_set_float(this->config, ccSection, ccKey, value);
	delete(ccKey);
	delete(ccSection);
}

Platform::String^ BelledonneCommunications::Linphone::Native::Config::GetString(Platform::String^ section, Platform::String^ key, Platform::String^ defaultValue)
{
	API_LOCK;
	const char *ccSection = Utils::pstoccs(section);
	const char *ccKey = Utils::pstoccs(key);
	const char *ccDefaultValue = Utils::pstoccs(defaultValue);
	const char *ccvalue = lp_config_get_string(this->config, ccSection, ccKey, ccDefaultValue);
	Platform::String^ value = Utils::cctops(ccvalue);
	delete(ccDefaultValue);
	delete(ccKey);
	delete(ccSection);
	return value;
}

void BelledonneCommunications::Linphone::Native::Config::SetString(Platform::String^ section, Platform::String^ key, Platform::String^ value)
{
	API_LOCK;
	const char *ccSection = Utils::pstoccs(section);
	const char *ccKey = Utils::pstoccs(key);
	const char *ccValue = Utils::pstoccs(value);
	lp_config_set_string(this->config, ccSection, ccKey, ccValue);
	delete(ccValue);
	delete(ccKey);
	delete(ccSection);
}

Platform::Array<int>^ BelledonneCommunications::Linphone::Native::Config::GetRange(Platform::String^ section, Platform::String^ key, const Platform::Array<int>^ defaultValue)
{
	API_LOCK;
	Platform::Array<int>^ range = ref new Platform::Array<int>(2);
	const char *ccSection = Utils::pstoccs(section);
	const char *ccKey = Utils::pstoccs(key);
	lp_config_get_range(this->config, ccSection, ccKey, &range[0], &range[1], defaultValue[0], defaultValue[1]);
	delete(ccKey);
	delete(ccSection);
	return range;
}

void BelledonneCommunications::Linphone::Native::Config::SetRange(Platform::String^ section, Platform::String^ key, const Platform::Array<int>^ value)
{
	API_LOCK;
	const char *ccSection = Utils::pstoccs(section);
	const char *ccKey = Utils::pstoccs(key);
	lp_config_set_range(this->config, ccSection, ccKey, value[0], value[1]);
	delete(ccKey);
	delete(ccSection);
}

BelledonneCommunications::Linphone::Native::Config::Config(::LinphoneConfig *config) :
	config(config)
{
	lp_config_ref(config);
}

BelledonneCommunications::Linphone::Native::Config::Config(Platform::String^ configPath, Platform::String^ factoryConfigPath)
{
	API_LOCK;
	const char *ccConfigPath = Utils::pstoccs(configPath);
	const char *ccFactoryConfigPath = Utils::pstoccs(factoryConfigPath);
	this->config = lp_config_new_with_factory(ccConfigPath, ccFactoryConfigPath);
	delete(ccFactoryConfigPath);
	delete(ccConfigPath);
}

BelledonneCommunications::Linphone::Native::Config::~Config()
{
	if (this->config != nullptr) {
		lp_config_unref(this->config);
	}
}