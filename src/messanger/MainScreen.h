#pragma once
#include "Chat.h"
#include <fstream>
#include <memory>
#include <string>

class MainScreen {
public:
  MainScreen();
  void startApp();

private:
  std::string m_name = "";
  std::string m_scndUserAddress = "";
  short m_readPort = 0;
  short m_destinationPort = 0;
  void showOptions();
  void clearScreen();
  void configFromFile();
  void configFromInput();
  void readFile(std::ifstream &file);
  short inputValidator(const std::string &errMess);
  void configToFile();
  void openChat();
  void writeToFile(std::ofstream &file);
  void showStatusInfo(const std::string &statusType,
                      const std::string &statusMessage);
};
