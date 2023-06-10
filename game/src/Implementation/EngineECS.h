#pragma once
#include <chrono>
#include <string>
#include <unordered_map>

#include "Contract/IEngine.h"


#include "Contract/IGame.h"

struct EngineECS_Config
{
	int screenWidth;
	int screenHeight;
	const char* title;
	const char* font_path;
	std::unordered_map<std::string, std::string> images;
	IGame* game;
};

class EngineECS final :
	public IEngine
{
public:
	void PreInit(std::any const& config) override;
	void Init() override;
	void GameLoop() override;
	void RunFrame();
	~EngineECS() override = default;
protected:
	std::chrono::milliseconds lag_ = std::chrono::milliseconds{ 0 };

	IGame* game_ = nullptr;
	void EndPlay() override;
};