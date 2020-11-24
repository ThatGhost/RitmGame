#pragma once
#include "pch.h"
#include "SaveAndLoadManager.h"
#include "dirent.h"
#include <fstream>
#include <sstream>
#include <map>
#include <sys/types.h>

namespace SLUtils {
	std::string SavePath{ "SaveFiles/Save.txt" }; //Do NOT CHANGE
	std::map<std::string, Texture*> textureMap{};
	std::vector<Texture> AllTextures{};

	void WrightToFileInts(std::vector<int>& data, std::string& path){
		std::ofstream DataStream{path};
		for (int i = 0; i < (int)data.size(); i++)
		{
			DataStream << std::to_string(data[i]) << '\n';
		}
		DataStream.close();
	}

	std::vector<int> ReadFileForInt(std::string path){
		std::ifstream DataStream{ path };
		std::vector<int> Data{};
		for (std::string line; getline(DataStream, line); )
		{
			int score{std::stoi(line)};
			Data.push_back(score);
		}
		DataStream.close();
		return Data;
	}

	std::vector<int> ReplaceValue(std::vector<int>& vector, int& value, int place) {
		if (place >= (int)vector.size())return vector;
		if (place < 0)return vector;

		std::vector<int> temp{};
		for (int i = 1; i <= place; i++)
		{
			temp.push_back(vector[i]);
		}
		temp.push_back(value);
		for (int i = place+1; i < (int)vector.size(); i++)
		{
			temp.push_back(vector[i]);
		}
		return temp;
	}
}
using namespace SLUtils;
using namespace utils;
/// <summary>
/// Adds score to scoreboard in right place. 
/// return true if its the new highscore.
/// </summary>
/// <param name="score"></param>
/// <returns></returns>
bool AddScore(int& score) {
	std::vector<int> AllScore{ReadFileForInt(SavePath)};
	bool HighScore{};

	if (score >= AllScore[AllScore.size() - 1]) {
		AllScore = ReplaceValue(AllScore, score, AllScore.size()-1);
		HighScore = true;
	}
	else {
		for (int i{}; i < (int)AllScore.size() - 1; i++)
		{
			if (AllScore[i] <= score && AllScore[i + 1] > score) {
				AllScore = ReplaceValue(AllScore, score, i);
				break;
			}
		}
	}
	WrightToFileInts(AllScore, SavePath);
	return HighScore;
}

void InitializeGameAssets() {
	const std::string assetsPath{"Assets/"};
	struct dirent* entry;
	DIR* dir = opendir(assetsPath.c_str());

	if (dir == NULL) {
		return;
	}
	std::vector<std::string> allNames{};
	std::cout << "Initialised game assets: \n";
	while ((entry = readdir(dir)) != NULL) {
		Texture t{};
		if (TextureFromFile(assetsPath + entry->d_name, t)) {
			std::cout << entry->d_name << '\n';
			AllTextures.push_back(t);
			allNames.push_back(entry->d_name);
		}
	}

	for (int i = 0; i < AllTextures.size(); i++)
	{
		textureMap.insert({ allNames[i], &AllTextures[i]});
	}
	closedir(dir);
}

void DeleteGameAssets() {
	for (size_t i = 0; i < AllTextures.size(); i++)
	{
		DeleteTexture(AllTextures[i]);
	}
}

/// <summary>
/// Get the texture from the name of file
/// </summary>
/// <param name="id"></param>
/// <returns></returns>
Texture* GetTexture(const std::string& id) {
	return textureMap.find(id)->second;
}

