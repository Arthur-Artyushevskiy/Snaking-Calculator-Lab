#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int applyOp(int total, char op, int num) {
    if (op == '+') return total + num;
    if (op == '-') return total - num;
    if (op == '*') return total * num;
    return total;
}

int evaluate(const vector<string>& program, int row, int col, char op, int total) {
    // Base case: end of line
    char savedOp{};
    if (col >= program[row].length()) {
        return total;
    }

    char ch = program[row][col];

    if (isdigit(ch)) {
        int num = ch - '0';
        total = applyOp(total, op, num);
        return evaluate(program, row, col + 1, op, total);
    }
    else if (ch == '+' || ch == '-' || ch == '*') {
        op = ch;
        return evaluate(program, row, col + 1, op, total);
    }
    else if (ch == '^' || ch == 'v') {
        int newRow = (ch == '^') ? row - 1 : row + 1;
        //program.size()
        if (newRow >= 0 && newRow < 2) {
            // (Fixed)the issue with this code is that the next operator is not used, in this example "*" is not used for the second row
            savedOp = op;
            int branchResult = evaluate(program, newRow, col, op, total);
            return evaluate(program, row, col + 1, savedOp, branchResult);
        }
    }

    // Unknown character or out of bounds branch — skip it
    return evaluate(program, row, col + 1, op, total);
}

int evaluate(const vector<string>& program) {
    
    return evaluate(program, 0, 0, '+', 0);
}


int main(){
    // (Fixed) the issue is that the number is  not multiplied by 3 at the end
    vector<string> program = {
        "257*233+6v790-12",
        "61247833212+*9^3"
    };
    cout << evaluate(program) << endl; // Should return 14107
    
    vector<string> program_2 = {
        "2+3v1",
        "   *2"
    };
    cout << evaluate(program_2) << endl;  // Should trace: 2 + 3 = 5 → branch down → *2 = 10 → return → 10 + 1 = 11
    
    return 0;
}
