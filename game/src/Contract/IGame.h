#pragma once
#include <any>

class IGame
{
public:
	virtual void PreInit(std::any const& config) = 0;
	virtual void BeginPlay() = 0;
	virtual void Tick(double DeltaSeconds) = 0;
	virtual void Render() = 0;
	virtual ~IGame() = default;
protected:
	virtual void EndPlay() = 0;
};
