#include <iostream>
#include <string>
#include "assembler.hpp"
#include <vector>
#include <fstream>

int main()
{
    std::vector<std::string> args;
    std::vector<std::string> command;
    std::string filepath;
    bool running = true;

    while (running && std::cin.good()) {
        std::cin >> filepath;//ifstream?
        std::cin.ignore('\n');


        args.push_back(filepath);


        if (args[0] == "run" && args.size() > 1 && args.size() <= REGISTER_SIZE + 2) {//input kanske kommer till args men inte vidare till command

            int registers[REGISTER_SIZE] = { 0 };


            for (int i = 2; i < int(args.size()); ++i) {
                registers[i - 2] = stoi(args[i]);
            }

            std::vector<std::vector<std::string>> commandList;

            if (!BuildCommandList(commandList, args[1])) {///////VERY BAD INPUT CODE GRADE CHECKMARK
                std::cout << "Error !BuildCommandList" << args[1] << ". Try again. " << std::endl;
            }
            else {
                while (PeekNextCommandIndex(registers) < commandList.size()) {
                    command = commandList[GetAndStepCommandIndex(registers)];

                    if (command[0] == "MOV") {
                        MOV(command, registers);
                    }

                    else if (command[0] == "ADD") {
                        ADD(command, registers);
                    }

                    else if (command[0] == "SUB")
                    {
                        SUB(command, registers);
                    }

                    else if (command[0] == "JEQ") {
                        JEQ(command, registers);
                    }

                    else if (command[0] == "JGT") {
                        JGT(command, registers);
                    }

                    else if (command[0] == "JLT") {
                        JLT(command, registers);
                    }
                }
                std::string reg_line = "";
                for (int i = 0; i < REGISTER_SIZE; i++) {
                    reg_line += std::to_string(registers[i]) + " ";
                    std::cout << reg_line << std::endl;
                }
            }
        }
        if (args[0] == "exit")
        {
            std::cout << "Goodbye" << std::endl;
            running = false;
            return running;
        }
        else {
            std::cout << "Error: Invalid command or number of arguments. Try again." << std::endl;
            std::cout << "---------------------------------------------------" << std::endl;
            std::cout << "Available commands:\n" << std::endl;
            std::cout << "> run program.asm (R0) (R1) ... (R7)" << std::endl;
            std::cout << "\tExecutes a program where 'program.asm' is the name" << std::endl;
            std::cout << "\tof the assembly file and (R0), (R1), ... (R7) is" << std::endl;
            std::cout << "\tthe optional initial values for the registers R0," << std::endl;
            std::cout << "\tR1, ... R7." << std::endl;
            std::cout << "> exit" << std::endl;
            std::cout << "\tCloses the application." << std::endl;
            std::cout << "---------------------------------------------------" << std::endl;
        }
    }
}
