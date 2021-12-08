#pragma once

/*
    This file should not be changed!
/

/ ################################## //
This header file contain all 'exposed'
function declarations.

All the functions are already declared,
this file should not be changed.
// ################################## */

#include <vector>
#include <string>

// Number of registers this implementation support
// Can be used in all files that include this header
// file.
constexpr int REGISTER_SIZE = 8;

// ################################## //
// ###### EXPOSED ASSEMBLER API ##### //
// ################################## //

// General command construction and reading

bool BuildCommandList(std::vector<std::vector<std::string>>& commandList, std::string filepath);
int PeekNextCommandIndex(int registers[]);
int GetAndStepCommandIndex(int registers[]);

// Assignment intructions

void MOV(std::vector<std::string>& command, int registers[]);

// Arithmetic instructions

void ADD(std::vector<std::string>& command, int registers[]);
void SUB(std::vector<std::string>& command, int registers[]);

// Jump instructions

void JEQ(std::vector<std::string>& command, int registers[]);
void JGT(std::vector<std::string>& command, int registers[]);
void JLT(std::vector<std::string>& command, int registers[]);