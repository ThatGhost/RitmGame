#pragma once
#include "pch.h"
#include "SaveAndLoadManager.h"
#include <fstream>
#include <sstream>

namespace SLUtils {
	std::string SavePath{ "SaveFiles/Save.txt" }; //Do NOT CHANGE

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
		for (size_t i = 1; i <= place; i++)
		{
			temp.push_back(vector[i]);
		}
		temp.push_back(value);
		for (size_t i = place+1; i < (int)vector.size(); i++)
		{
			temp.push_back(vector[i]);
		}
		return temp;
	}
}
using namespace SLUtils;

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
	const std::string AssetsPath{"Assets/"};
}

