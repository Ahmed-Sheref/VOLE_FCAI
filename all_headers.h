#ifndef ALL_HEADERS_H
#define ALL_HEADERS_H

#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

// Global memory maps and instruction vector
extern map<string, string> mem_1;
extern map<string, string> mem_2;
extern vector<string> vec_Instuction;

// ADD_F Class Declaration
class ADD_F 
{
public:
    static double applyFormFloat(const vector<string>& component);
    static string float_to_hex(double number);
    static vector<string> separate(const string& binaryNumber);
    static string hexToBinary(const string& hex);

private:
    static string convertIntegerToBinary(int intPart);
    static string convertFractionToBinary(double fracPart, int precision = 10);
    static string convertDecimalToBinary(double num);
    static double binaryToDecimal(const string& binaryStr);
};

// Instruction Class Declaration
class Instruction {
private:
    static string PC;
    string OP_code;
    string Register;
    string Memory;
    static int lines;

public:
    void set_OP(string instruction);
    bool HALT();
    string get_OP();
    string get_Register();
    string get_Memory();
    string get_PC();
    int get_lines();
    void set_PC(string& new_PC);
};

// MessagePrinter Class Declaration
class MessagePrinter {
public:
    void print_add_floating_point(string reg1, string reg2);
    void print_add_integer(string reg1, string reg2);
    void print_load(string memory_address, string reg_name);
    void print_store(string reg_name, string memory_address);
    void print_move(string reg_from, string reg_to);
    void print_jump(string condition, string target_address);
    void print_halt();
    void print_or(string reg1, string reg2);
    void print_and(string reg1, string reg2);
    void print_xor(string reg1, string reg2);
    void print_rotate(string reg, int steps);
};

// search_in_Memory Class Declaration
class search_in_Memory {
    Instruction inst;
    string memory;
    string Register;

public:
    search_in_Memory(Instruction& inst);
    bool find_and_remove_until_memory(string& memory_part);
};

// Machine_Language Class Declaration
class Machine_Language {
private:
    Instruction inst;
    MessagePrinter printer;

public:
    Machine_Language(Instruction& Instruction_instance);
    void execute_instruction();

private:
    void execute_load(string& memory, string& reg);
    void execute_direct_load(string& memory, string& reg);
    void execute_store(string& reg, string& memory);
    void execute_move(string& memory);
    void execute_add_integer(string& reg, string& memory);
    void execute_add_floating_point(string& reg, string& memory);
    void execute_or(string& reg, string& memory);
    void execute_and(string& reg, string& memory);
    void execute_xor(string& reg, string& memory);
    void execute_rotate(string& reg, int steps);
    void execute_conditional_jump_B(string& reg, string& memory);
    void execute_conditional_jump_D(string& reg, string& memory);
};

// Utility functions
string HX(string& hex1, string& hex2);
void display_menu();
void display_memory();

#endif // ALL_HEADERS_H
