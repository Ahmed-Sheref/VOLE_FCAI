#include <bits/stdc++.h>
#include "all_headers.h"

using namespace std;

// Global variables
map<string, string> mem_1;
map<string, string> mem_2;
vector<string> vec_Instuction;

// ADD_F Class Implementations
double ADD_F::applyFormFloat(const vector<string>& component) 
{
    int sign = (component[0] == "1") ? -1 : 1;
    int exponent = binaryToDecimal(component[1]);
    long long power = exponent - 4;
    string new_mantissa;

    if (power < 0) {
        new_mantissa += "0.";
        for (int i = 0; i < abs(power); i++)
            new_mantissa += "0";
        for (int i = 0; i < component[2].size(); i++)
            new_mantissa.push_back(component[2][i]);
    } 
    else 
    {
        for (int i = 0; i < component[2].size(); i++) 
        {
            if (i == power)
                new_mantissa.push_back('.');
            new_mantissa.push_back(component[2][i]);
        }
    }
    return sign * (binaryToDecimal(new_mantissa));
}

string ADD_F::float_to_hex(double number) 
{
    bool sign = (number < 0 ? true : false);
    string Binary_number = convertDecimalToBinary(abs(number));
    if (Binary_number.length() == 2 and Binary_number[0] == '0') return "00";
    vector<char> bits;
    vector<int> positions;
    int decimal_point_index = Binary_number.find('.');
    int pos = decimal_point_index - 1;

    for (int i = 0; i < decimal_point_index; i++) 
    {
        bits.push_back(Binary_number[i]);
        positions.push_back(pos);
        pos--;
    }
    pos = -1;
    for (int i = decimal_point_index + 1; i < Binary_number.length(); i++) 
    {
        bits.push_back(Binary_number[i]);
        positions.push_back(pos);
        pos--;
    }
    int first_one_index = -1;
    for (int i = 0; i < bits.size(); i++) 
    {
        if (bits[i] == '1') 
        {
            first_one_index = i;
            break;
        }
    }

    string Finally_Binary;
    if (first_one_index != -1) 
    {
        int exponent_value = 4 + positions[first_one_index] + 1;
        int exponent_bits = exponent_value;
        if (exponent_bits < 0)
            exponent_bits = 0;
        else if (exponent_bits > 7)
            exponent_bits = 7;
        string exponent_bits_str = convertIntegerToBinary(exponent_bits);
        while (exponent_bits_str.length() < 3)
            exponent_bits_str = "0" + exponent_bits_str;
        if (exponent_bits_str.length() > 3)
            exponent_bits_str = exponent_bits_str.substr(exponent_bits_str.length() - 3);
        string mantissa;
        for (int i = first_one_index; mantissa.length() < 4; i++) {
            if (i < bits.size())
                mantissa += bits[i];
            else
                mantissa += "0";
        }
        Finally_Binary += (sign ? '1' : '0');
        Finally_Binary += exponent_bits_str;
        Finally_Binary += mantissa;
    } 
    else 
    {
        Finally_Binary = (sign ? '1' : '0') + "000";
    }
    string hexResult;
    for (size_t i = 0; i < Finally_Binary.length(); i += 4)
    {
        string binaryChunk = Finally_Binary.substr(i, 4);
        int decimalValue = stoi(binaryChunk, nullptr, 2);
        hexResult += "0123456789ABCDEF"[decimalValue];
    }
    return hexResult;
}

vector<string> ADD_F::separate(const string& binaryNumber) 
{
    vector<string> component(3);
    component[0] = string(1, binaryNumber.front());
    component[1] = binaryNumber.substr(1, 3);
    component[2] = "1" + binaryNumber.substr(5, 7);
    return component;
}

string ADD_F::hexToBinary(const string& hex) 
{
    string binary;
    for (char hexChar : hex) 
    {
        int intValue = stoi(string(1, hexChar), nullptr, 16);
        binary += bitset<4>(intValue).to_string();
    }
    return binary;
}

string ADD_F::convertIntegerToBinary(int intPart) 
{
    string intBinary = "";
    while (intPart > 0) 
    {
        intBinary = to_string(intPart % 2) + intBinary;
        intPart /= 2;
    }
    return intBinary.empty() ? "0" : intBinary;
}

string ADD_F::convertFractionToBinary(double fracPart, int precision) 
{
    string fracBinary = ".";
    int count = 0;
    while (fracPart > 0 && count < precision) 
    {
        fracPart *= 2;
        int bit = static_cast<int>(fracPart);
        fracBinary += to_string(bit);
        fracPart -= bit;
        count++;
    }
    return fracBinary;
}

string ADD_F::convertDecimalToBinary(double num) 
{
    int intPart = static_cast<int>(num);
    double fracPart = num - intPart;
    string intBinary = convertIntegerToBinary(intPart);
    string fracBinary = convertFractionToBinary(fracPart);
    return intBinary + fracBinary;
}

double ADD_F::binaryToDecimal(const string& binaryStr) 
{
    size_t point = binaryStr.find('.');
    string intPart = binaryStr.substr(0, point);
    string fracPart = (point != string::npos) ? binaryStr.substr(point + 1) : "";
    double decimalValue = 0;
    int len = intPart.length();
    for (int i = 0; i < len; i++)
        if (intPart[i] == '1')
            decimalValue += pow(2, len - i - 1);
    len = fracPart.length();
    for (int i = 0; i < len; i++)
        if (fracPart[i] == '1')
            decimalValue += pow(2, -(i + 1));
    return decimalValue;
}

// Instruction Class Implementations
string Instruction::PC = "";
int Instruction::lines = 0;

void Instruction::set_OP(string instruction) 
{
    PC = instruction;
    OP_code = instruction.substr(0, 1);
    Register = instruction.substr(1, 1);
    Memory = instruction.substr(2);
    lines++;
}

bool Instruction::HALT() 
{
    return (OP_code == "C" && (Register == "0" && Memory == "00"));
}

string Instruction::get_OP() { return OP_code; }
string Instruction::get_Register() { return Register; }
string Instruction::get_Memory() { return Memory; }
string Instruction::get_PC() { return PC; }
int Instruction::get_lines() { return lines; }
void Instruction::set_PC(string& new_PC) { PC = new_PC; }

// MessagePrinter Class Implementations
void MessagePrinter::print_add_floating_point(string reg1, string reg2) 
{
    cout << "ADD operation (floating point): Adding values in registers " << reg1 << " and " << reg2 << " as floating-point values" << endl;
}

void MessagePrinter::print_add_integer(string reg1, string reg2) 
{
    cout << "ADD operation: Adding values in registers " << reg1 << " and " << reg2 << endl;
}

void MessagePrinter::print_load(string memory_address, string reg_name) 
{
    cout << "LOAD operation: Loading value from memory address " << memory_address << " to register " << reg_name << endl;
}

void MessagePrinter::print_store(string reg_name, string memory_address) 
{
    cout << "STORE operation: Storing value from register " << reg_name << " to memory address " << memory_address << endl;
}

void MessagePrinter::print_move(string reg_from, string reg_to) {
    cout << "MOVE operation: Moving value from register " << reg_from << " to register " << reg_to << endl;
}

void MessagePrinter::print_jump(string condition, string target_address) {
    cout << "JUMP operation: Jumping to memory address " << target_address << " if condition (" << condition << ") holds." << endl;
}

void MessagePrinter::print_halt() {
    cout << "HALT operation: Stopping program execution." << endl;
}

void MessagePrinter::print_or(string reg1, string reg2) {
    cout << "OR operation: Performing OR on registers " << reg1 << " and " << reg2 << endl;
}

void MessagePrinter::print_and(string reg1, string reg2) {
    cout << "AND operation: Performing AND on registers " << reg1 << " and " << reg2 << endl;
}

void MessagePrinter::print_xor(string reg1, string reg2) {
    cout << "XOR operation: Performing XOR on registers " << reg1 << " and " << reg2 << endl;
}

void MessagePrinter::print_rotate(string reg, int steps) {
    cout << "ROTATE operation: Rotating register " << reg << " right by " << steps << " steps." << endl;
}

// search_in_Memory Class Implementations
search_in_Memory::search_in_Memory(Instruction& inst) : inst(inst) {
    memory = inst.get_Memory();
    Register = inst.get_Register();
}

bool search_in_Memory::find_and_remove_until_memory(string& memory_part) {
    for (int i = inst.get_lines(); i < vec_Instuction.size(); ++i) {
        string instruction_memory = vec_Instuction[i].substr(2);
        if (instruction_memory == memory_part) {
            vec_Instuction.erase(vec_Instuction.begin(), vec_Instuction.begin() + i);
            return true;
        }
    }
    return false;
}

// Machine_Language Class Implementations
Machine_Language::Machine_Language(Instruction& Instruction_instance) : inst(Instruction_instance) {}

void Machine_Language::execute_instruction() {
    string op_code = inst.get_OP();
    string reg = inst.get_Register();
    string mem = inst.get_Memory();

    if (op_code == "1") {
        execute_load(mem, reg);
    } else if (op_code == "2") {
        execute_direct_load(mem, reg);
    } else if (op_code == "3") {
        execute_store(reg, mem);
    } else if (op_code == "4") {
        execute_move(mem);
    } else if (op_code == "5") {
        execute_add_integer(reg, mem);
    } else if (op_code == "6") {
        execute_add_floating_point(reg, mem);
    } else if (op_code == "7") {
        execute_or(reg, mem);
    } else if (op_code == "8") {
        execute_and(reg, mem);
    } else if (op_code == "9") {
        execute_xor(reg, mem);
    } else if (op_code == "A") {
        execute_rotate(reg, stoi(mem, nullptr, 16));
    } else if (op_code == "B") {
        execute_conditional_jump_B(reg, mem);
    } else if (op_code == "D") {
        execute_conditional_jump_D(reg, mem);
    } else if (inst.HALT()) {
        printer.print_halt();
    } else {
        cout << "Unknown opcode: " << op_code << endl;
    }
}

void Machine_Language::execute_load(string& memory, string& reg) {
    printer.print_load(memory, reg);
    if (mem_2.find(memory) == mem_2.end() || mem_2[memory].empty()) {
        mem_1[reg] = "00";
    } else {
        mem_1[reg] = mem_2[memory];
    }
}

void Machine_Language::execute_direct_load(string& memory, string& reg) {
    printer.print_load(memory, reg);
    mem_1[reg] = memory;
}

void Machine_Language::execute_store(string& reg, string& memory) {
    if (memory != "00") {
        printer.print_store(reg, memory);
        mem_2[memory] = mem_1[reg];
    } else {
        if (mem_2["00"].empty()) {
            cout << "address empty\n";
        } else {
            cout << mem_2["00"] << endl;
        }
    }
}

void Machine_Language::execute_move(string& memory) {
    string reg1 = memory.substr(0, 1);
    string reg2 = memory.substr(1);
    printer.print_move(reg1, reg2);
    mem_1[reg2] = mem_1[reg1];
}

void Machine_Language::execute_add_integer(string& reg, string& memory)
{
    string reg1 = reg.substr(0, 1);
    string reg2 = memory.substr(0, 1);
    string reg3 = memory.substr(1, 2);
    printer.print_add_integer(reg1, reg2);
    mem_1[reg1] = HX(mem_1[reg2], mem_1[reg3]);
}

void Machine_Language::execute_add_floating_point(string& reg, string& memory) {
    string reg1 = reg.substr(0, 1);
    string reg2 = memory.substr(0, 1);
    string reg3 = memory.substr(1, 2);
    printer.print_add_floating_point(reg1, reg2);
    string hex1 = mem_1[reg2];
    string hex2 = mem_1[reg3];
    double num1 = ADD_F::applyFormFloat(ADD_F::separate(ADD_F::hexToBinary(hex1)));
    double num2 = ADD_F::applyFormFloat(ADD_F::separate(ADD_F::hexToBinary(hex2)));
    double sum = num1 + num2;
    string resultHex = ADD_F::float_to_hex(sum);
    mem_1[reg1] = resultHex;
}

void Machine_Language::execute_or(string& reg, string& memory) {
    string reg1 = reg.substr(0, 1);
    string reg2 = memory.substr(0, 1);
    printer.print_or(reg1, reg2);

    int result = stoi(mem_1[reg1], nullptr, 16) | stoi(mem_1[reg2], nullptr, 16);
    stringstream ss;
    ss << uppercase << hex << result;
    mem_1[reg1] = ss.str();
}

void Machine_Language::execute_and(string& reg, string& memory) {
    string reg1 = reg.substr(0, 1);
    string reg2 = memory.substr(0, 1);
    printer.print_and(reg1, reg2);

    int result = stoi(mem_1[reg1], nullptr, 16) & stoi(mem_1[reg2], nullptr, 16);
    stringstream ss;
    ss << uppercase << hex << result;
    mem_1[reg1] = ss.str();
}

void Machine_Language::execute_xor(string& reg, string& memory) {
    string reg1 = reg.substr(0, 1);
    string reg2 = memory.substr(0, 1);
    printer.print_xor(reg1, reg2);

    int result = stoi(mem_1[reg1], nullptr, 16) ^ stoi(mem_1[reg2], nullptr, 16);
    stringstream ss;
    ss << uppercase << hex << result;
    mem_1[reg1] = ss.str();
}

void Machine_Language::execute_rotate(string& reg, int steps) {
    printer.print_rotate(reg, steps);

    int val = stoi(mem_1[reg], nullptr, 16);
    int result = (val >> steps) | (val << (8 - steps)) & 0xFF;
    stringstream ss;
    ss << uppercase << hex << result;
    mem_1[reg] = ss.str();
}

void Machine_Language::execute_conditional_jump_B(string& reg, string& memory) {
    printer.print_jump("greater than 0", memory);
    if (stoi(mem_1[reg], nullptr, 16) == stoi(mem_1["0"], nullptr, 16)) {
        search_in_Memory memory_object(inst);
        memory_object.find_and_remove_until_memory(memory);
    }
}

void Machine_Language::execute_conditional_jump_D(string& reg, string& memory) {
    printer.print_jump("greater than 0", memory);
    if (stoi(mem_1[reg], nullptr, 16) > stoi(mem_1["0"], nullptr, 16)) {
        search_in_Memory memory_object(inst);
        memory_object.find_and_remove_until_memory(memory);
    }
}

// Utility function implementations
string HX(string& hex1, string& hex2) 
{
    int num1 = stoi(hex1, nullptr, 16);
    int num2 = stoi(hex2, nullptr, 16);
    int sum = num1 + num2;
    if (sum > 127)
    {
        sum -= 256;
    }
    else if (sum < -127)
    {
        sum += 256;
    }
    stringstream ss;
    ss << uppercase << setfill('0') << setw(2) << hex << sum;
    return ss.str();
}

void display_menu() {
    cout << "Choose an option:" << endl;
    cout << "1. Load Instructions from File" << endl;
    cout << "2. Show Memory Contents" << endl;
    cout << "3. Exit Program" << endl;
    cout << "Enter your choice: ";
}


void display_memory() 
{
    // Display register contents (mem_1)
    cout << "\nRegister Contents (mem_1):" << endl;
    for (const auto& [reg, value] : mem_1) 
    {
        cout << "Register " << reg << ": " << value << endl;
    }

    cout << "\nMemory Contents (mem_2):" << endl;
    cout << "\n    ";  

    for (int col = 0; col < 16; ++col)
        cout << " " << hex << uppercase << col << " ";

    cout << endl;
    cout << "   " << string(49, '-') << endl;  

    for (int row = 0; row < 16; ++row) 
    {
        cout << hex << uppercase << row << " | ";

        for (int col = 0; col < 16; ++col) 
        {
            string address = string(1, "0123456789ABCDEF"[row]) + string(1, "0123456789ABCDEF"[col]);
            cout << setw(2) << setfill('0') << (mem_2.count(address) ? mem_2[address] : "00") << " ";
        }
        cout << endl;
    }
}




