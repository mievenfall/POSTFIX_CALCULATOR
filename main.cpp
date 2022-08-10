#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>

class RPL {
    public:
        // READ USER INPUT
        void read(std::string* input)
        {
            std::cout << "--> ";
            getline(std::cin, *input);
    
        }

        // PRINT OUT THE RESULT
        void print(int* result, int* error_check)
        {
            if (*error_check == 1) std::cout << "ERROR\n";
            else std::cout << *result << std::endl;
        }
};

class E {
    public:
        // EVALUATE THE EXPRESSION
        void evaluate (std::string input)
        {
            long int temp_num = 0;
            int i = 0;
            std::istringstream in (input);
            // GO OVER ELEMENTS SEPARATED FROM SPACE
            for (std::string line; std::getline(in, line, ' '); ) { 
                // IF THE FIRST UNIT OF LINE IS NUMBER
                if (line[i] >= '0' && line[i] <= '9') {
                    for (int j = 0; j < line.size(); j++) {
                        // ERROR IF A UNIT IN LINE IS A NON-NUMBER
                        if (!(line[j] >= '0' && line[j] <= '9')) return;
                        // CONVERT TO INT
                        temp_num += (line[j] - '0') * pow(10, (line.size() - j - 1));
                    }
                    // ADD NUMBER TO STACK
                    nums_stack.push(temp_num);
                    temp_num = 0;                    
                }

                // IF THERE IS A SIGN BEFORE A NUMBER
                else if ((line[i] == '-' || line [i] == '+') && line[i+1] >= '0' && line[i+1] <= '9') {
                    for (int j = 1; j < line.size() ; j++) {
                        // ERROR IF A UNIT IN LINE IS A NON-NUMBER
                        if (!(line[j] >= '0' && line[j] <= '9')) return;
                        //CONVERT TO INT
                        if (line[i] == '-') temp_num -= (line[j] - '0') * pow(10, (line.size() - j - 1));
                        if (line[i] == '+') temp_num += (line[j] - '0') * pow(10, (line.size() - j - 1));
                    }
                    // ADD NUMBER TO STACK
                    nums_stack.push(temp_num);
                    temp_num = 0;
                }
 
                // IF THERE IS AN OPERATOR
                else if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/') {
                    // ERROR IF NON-POSTFIX
                    if (nums_stack.size() == 1) {
                        nums_stack.pop();
                        return;
                    }
                    // ERROR IF PREFIX AND NON-NUMBERS
                    else if (nums_stack.size() == 0) {
                        return;
                    }
                    
                    // EVALUATE THE EXPRESSION
                    /* ALGORITHM
                        push numbers to stack
                        if there is an operator, pop 2 numbers from stack
                        operate the expression
                        push the result back to stack
                        continue
                    */
                    else {
                        // POP 2 NUMBERS AND OPERATE THE EXPRESSION
                        oprt = line[i];
                        num1 = nums_stack.top();
                        nums_stack.pop();
                        num2 = nums_stack.top();
                        nums_stack.pop();

                        switch (oprt)
                        {
                        case '+':
                            nums_stack.push(num2 + num1);
                            break;
                        case '-':
                            nums_stack.push(num2 - num1);
                            break;
                        case '*':
                            nums_stack.push(num2 * num1);
                            break;
                        case '/':
                            if (num1 == 0) break; 
                            else nums_stack.push(num2 / num1);
                            break;
                        
                        }
                    }
                }
                // ERROR IF THE FIRST UNIT IN LINE IS NON-NUMBER NOR SIGN
                else break;
            }
        }
        
        // ERROR CHECK AND SET THE RESULT TO A VARIABLE
        void set_result (int* result, int* error_check) {
            // ERROR IF MORE THAN 1 ELEMENT IN STACK 
            if (nums_stack.size() != 1) {
                while (nums_stack.size() != 0) nums_stack.pop();
                *error_check = 1;
            }

            // SET THE RESULT AND CLEAR THE STACK
            else {
                *error_check = 0;
                *result = nums_stack.top();
                nums_stack.pop();
            }
        }

    private:
        long int num1, num2;
        char oprt;
        std::stack<long int> nums_stack;
};


int main()
{
    // DECLARE VARIABLES
    std::string input;
    int result;
    int error_check = 1;
    E computing;
    RPL calculator;

    do {
        // ASK FOR USER INPUT AND READ IT
        calculator.read(&input);
        // IF THE INPUT IS NOT QUIT THEN CONTINUE THE PROCESS
        if (input != "quit") {
            // EVALUATE AND SET THE RESULT
            computing.evaluate(input);
            computing.set_result(&result, &error_check);
            // PRINT THE RESULT
            calculator.print(&result, &error_check);
        }
    // LOOP IF INPUT IS NOT QUIT
    } while (input != "quit");
}
