#pragma once
extern "C" _declspec(dllexport) int execmd(const char* cmd, char* result);
extern "C" _declspec(dllexport) int execmd_hide(char* CommandLine, char* result);

