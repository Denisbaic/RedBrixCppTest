#pragma once
#include <any>

class IEngine
{
public:
	virtual void PreInit(std::any const & config) = 0;
	virtual void Init() = 0;
	virtual void GameLoop() = 0;
	virtual ~IEngine() = default;
protected:
	virtual void EndPlay() = 0;

};