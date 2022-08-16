#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
//text management
std::vector<std::string> split(std::string text, char delimiter) {
	//split where ',' is found put in vector
	std::vector<std::string> split_text;
	std::stringstream ss(text);
	std::string token;
	while (std::getline(ss, token, delimiter)) {
		split_text.push_back(token);
		}
	return split_text;

}
std::vector<std::string> read(std::string filename) {

	// catch if the file is being used already, try, catch
	std::ifstream file(filename.append(".txt"));
	std::string line;
	std::vector<std::string> data;
	while (std::getline(file, line)) {
		data.push_back(line);
	}
	return data;


}
void write(std::string filename, std::string text) {
    std::fstream file(filename.append(".txt"));
    file << text;
}
//vectors
std::vector<std::string> split_vector(std::vector<std::string> data) {
    std::vector<std::string> info;
    for (int i = 0; i < data.size(); i++) {
        std::string line = data[i];
        info = split(line, ',');
    }
    return data;
}
//birthday
int birthday(std::string date) {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	tm their, todays;
	todays.tm_year = ltm->tm_year;
	todays.tm_mday = ltm->tm_mday;
	todays.tm_mon = ltm->tm_mon;
	todays.tm_hour = 0;
	todays.tm_min = 0;
	their.tm_year = ltm->tm_year;
	their.tm_hour = 0;
	their.tm_min = 0;

	//unpack function split into year, month, day
	if (date.find('-') != std::string::npos) {
		std::vector<std::string> date_info = split(date, '-');
		their.tm_mday = std::stoi(date_info[2]);
		their.tm_mon = std::stoi(date_info[1]) - 1;
	};
	if (date.find('/') != std::string::npos) {
		std::vector<std::string> date_info = split(date, '/');
		their.tm_mday = std::stoi(date_info[0]);
		their.tm_mon = std::stoi(date_info[1]) - 1;
	};
	if (todays.tm_mon > their.tm_mon || difftime(mktime(&their), mktime(&todays)) < 0) {
		their.tm_year += 1;
	};
	return round(difftime(mktime(&their), mktime(&todays)) / (60 * 60 * 24));
}
	
int main() {
    std::vector<std::string> file = read("birthdays");
	std::vector<std::string> e = split_vector(file);
	std::vector<std::pair<std::string,int>> info;
    for (int i = 0; i < e.size(); i++) {
		std::vector<std::string> person = split(e[i], ',');
		info.push_back({person[0],birthday(person[1])});
    }
	//sort info by birthday
	std::sort(info.begin(), info.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
		return a.second < b.second;
	});
	
	//print info
	for (int i = info.size(); i-- > 0; )
	{
		std::cout << info[i].first << ": " << info[i].second << '\n';
	}	
    std::system("pause>0");
	return 0;
}