#pragma once

namespace SLUtils {
	void WrightToFileInts(std::vector<int>& data, std::string& path);
	std::vector<int> ReadFileForInt(std::string path);
	std::vector<int> ReplaceValue(std::vector<int>& vector, int& value, int place);
}

bool AddScore(int& score);
void InitializeGameAssets();
void DeleteGameAssets();
Texture* GetTexture(const std::string& id);
