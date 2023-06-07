#pragma once

class IModuleManager
{
public:
	virtual void startUp() = 0;
	virtual void shutDown() = 0;
};
