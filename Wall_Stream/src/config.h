#pragma once

class Config {
private:
	void createDefaultConfig();
public:
	Config();
	Config(const char* fileName);
	~Config();

};