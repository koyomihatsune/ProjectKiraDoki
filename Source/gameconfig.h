#pragma once
using namespace std;
const int PAUSE_X_START = 39, PAUSE_Y_START = 653, PAUSE_X_END = 39+132, PAUSE_Y_END = 653+41;
const int CONTINUE_X_START = 399, CONTINUE_Y_START = 340, CONTINUE_X_END = 531, CONTINUE_Y_END = 381;
const int EXIT_X_START = 561, EXIT_Y_START = 340, EXIT_X_END = 696, EXIT_Y_END = 382;

string feverchargeimage[3] = { "resources/fever1.png", "resources/fever2.png", "resources/fever3.png" };
int feverchargestart[10] = { 2080, 1000000 };
int feverchargeend[10] = { 3500, 1000000 };
int feverstart[10]= { 3610, 1000000 };

string stagelight[5] = { "resources/bottomlane_1.png", "resources/bottomlane_2.png", "resources/bottomlane_3.png", "resources/bottomlane_4.png", "resources/bottomlane_2.png" };