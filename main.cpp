#include "all_headers.cpp"
#include <fstream>

int main() {
    int choice;
    while (true) 
    {
        display_menu();
        cin >> choice;

        if (choice == 1) 
        {
            string filename;
            cout << "Enter the instruction file name: ";
            cin >> filename;

            ifstream infile(filename);
            if (!infile.is_open()) 
            {
                cout << "Error: Could not open file " << filename << endl;
                continue;
            }

            mem_1["0"] = "00";
            mem_1["1"] = "00";
            mem_1["2"] = "00";
            mem_1["3"] = "00";
            mem_1["4"] = "00";
            mem_1["5"] = "00";
            mem_1["6"] = "00";
            mem_1["7"] = "00";
            mem_1["8"] = "00";
            mem_1["9"] = "00";
            mem_1["A"] = "00";
            mem_1["B"] = "00";
            mem_1["C"] = "00";
            mem_1["D"] = "00";
            mem_1["E"] = "00";
            mem_1["F"] = "00";

            string instruction_line;
            Instruction inst;
            while (getline(infile, instruction_line)) 
            {
                if (!instruction_line.empty()) 
                { 
                    vec_Instuction.emplace_back(instruction_line);
                }
            }
            for (auto &Current_PC : vec_Instuction) 
            {
                inst.set_OP(Current_PC);
                Machine_Language machine(inst);
                machine.execute_instruction();
            }
            infile.close();
        } 
        else if (choice == 2) 
        {
            display_memory();
        } 
        else if (choice == 3) 
        {
            break;
        } 
        else 
        {
            cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
        }
    };
    cout << "Program ended." << endl;
    return 0;
}
