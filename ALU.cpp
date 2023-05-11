#include "./include/color.hpp"
#include <iostream>
#include <cmath>

using namespace std;

int binaryToDecimal(int binaryNumber[]) {
    int decimalNumber = 0;
    for (int i = 0; i < 32; i++) {
        decimalNumber += binaryNumber[31 - i] * pow(2, i);
    }
    return decimalNumber;
}

void decimalToBinary(int decimalNumber, int binaryNumber[]) {
    for (int i = 31; i >= 0; i--) {
        binaryNumber[i] = decimalNumber % 2;
        decimalNumber /= 2;
    }
}


void add(int *in1, int *in2, int *out) {
    int carry = 0;
    for (int i = 31; i >= 0; i--) {
        int sum = in1[i] + in2[i] + carry;
        out[i] = sum % 2;
        carry = sum / 2;
    }
    if (carry > 0)
    {
        cout << colors::red << "Result Is Too Big For 32bit\n" << colors::reset;
        throw overflow_error("Overflow error: result too large to fit in 32 bits.");
    }
    
}

void subtract(int *in1, int *in2, int *out) {
    int borrow = 0;
    for (int i = 31; i >= 0; i--) {
        int diff = in1[i] - in2[i] - borrow;
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        out[i] = diff;
    }
    if (borrow > 0)
    {
        cout << colors::red << "Result Is Too Small For 32bit\n" << colors::reset;
        throw underflow_error("Underflow error: result too small to fit in 32 bits.");
    }
    
}

void logical_shift_right(int *in, int *out, int shift) {
    for (int i = 0; i < shift; i++) {
        out[i] = 0;
    }
    for (int i = shift; i < 32; i++) {
        out[i] = in[i - shift];
    }
}

void logical_shift_left(int *in, int *out, int shift) {
    for (int i = 0; i < 32 - shift; i++) {
        out[i] = in[i + shift];
    }
    for (int i = 32 - shift; i < 32; i++) {
        out[i] = 0;
    }
}

void bitwise_and(int *in1, int *in2, int *out) {
    for (int i = 0; i < 32; i++) {
        out[i] = in1[i] & in2[i];
    }
}

void bitwise_or(int *in1, int *in2, int *out) {
    for (int i = 0; i < 32; i++) {
        out[i] = in1[i] | in2[i];
    }
}

void bitwise_xor(int *in1, int *in2, int *out) {
    for (int i = 0; i < 32; i++) {
        out[i] = in1[i] ^ in2[i];
    }
}

void bitwise_nand(int* in1, int* in2, int* out) {
    for (int i = 0; i < 32; i++) {
        out[i] = !(in1[i] & in2[i]); // perform bitwise NAND
    }
}

void increment(int *in, int *out) {
    int carry = 1;
    for (int i = 31; i >= 0; i--) {
        int sum = in[i] + carry;
        out[i] = sum % 2;
        carry = sum / 2;
    }
}

void decrement(int *in, int *out) {
    int borrow = 1;
    for (int i = 31; i >= 0; i--) {
        int diff = in[i] - borrow;
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        out[i] = diff;
    }
}

void menu() {
    cout << "-------------------------------------------\n" << colors::bright_yellow << "[0] Add\n[1] Subtract\n[2] Logical Shift Right\n[3] Logical Shift Left\n[4] Bitwise AND\n[5] Bitwise OR\n[6] Bitwise XOR\n[7] Increment\n[8] Decrement\n[9] Exit\n[10] Menu\n" << colors::reset;
    cout << "-------------------------------------------\n" << colors::bright_cyan <<  "\nthe operation code [0-10]: " << colors::reset;
}

int main() {
    colors::reset;

    int op;
    int in1[32], in2[32], out[32], reg[32];
    int in1_dec, in2_dec, out_dec, reg_dec, shift;
    
    menu();
    cin >> op;

    if (op == 0 || op == 1 || op == 4 || op == 5 || op == 6) {
        cout << colors::bright_cyan <<  "Enter the first input ( Demical ): " << colors::reset;
        cin >> in1_dec;
        decimalToBinary(in1_dec , in1); // in1[32]
                
        cout << colors::bright_cyan <<  "Enter the second input ( Demical ): " << colors::reset;
        cin >> in2_dec;
        decimalToBinary(in2_dec, in2); // in2[32]
    }else if (op == 7 || op == 8) {
        cout << colors::bright_cyan <<  "Enter the input ( Demical ): " << colors::reset;
        cin >> in1_dec;
        decimalToBinary(in1_dec, in1); // in1[32]
    }else if(op == 2 || op == 3){
        cout << colors::bright_cyan <<  "Enter the input ( Demical ): " << colors::reset;
        cin >> in1_dec;
        decimalToBinary(in1_dec, in1); // in1[32]
        cout << colors::bright_cyan <<  "Enter the shift amount ( Demical ): " << colors::reset;
        cin >> shift;
    }

switch (op) {
    case 0:
        add(in1, in2, out);
        cout << "\n-------------------------------------------\n" << colors::green << colors::bold << colors::italic << "Result(Binary): ";
        for (int i = 0; i < 32; i++) {
            cout << out[i];
        }
        binaryToDecimal(out);
        cout << "\nResult(Decimal): " << binaryToDecimal(out) << colors::reset << "\n-------------------------------------------\n";
        cout << endl;
        break;
    case 1:
        subtract(in1, in2, out);
        cout << "\n-------------------------------------------\n" << colors::green << colors::bold << colors::italic << "Result(Binary): ";
        for (int i = 0; i < 32; i++) {
            cout << out[i];
        }
        binaryToDecimal(out);
        cout << "\nResult(Decimal): " << binaryToDecimal(out) << colors::reset << "\n-------------------------------------------\n";
        cout << endl;
        break;
    case 2:
        logical_shift_right(in1, out, shift);
        cout << "\n-------------------------------------------\n" << colors::green << colors::bold << colors::italic << "Result(Binary): ";
        for (int i = 0; i < 32; i++) {
            cout << out[i];
        }
        binaryToDecimal(out);
        cout << "\nResult(Decimal): " << binaryToDecimal(out) << colors::reset << "\n-------------------------------------------\n";
        cout << endl;
        break;
    case 3:
        logical_shift_left(in1, out, shift);
        cout << "\n-------------------------------------------\n" << colors::green << colors::bold << colors::italic << "Result(Binary): ";
        for (int i = 0; i < 32; i++) {
            cout << out[i];
        }
        binaryToDecimal(out);
        cout << "\nResult(Decimal): " << binaryToDecimal(out) << colors::reset << "\n-------------------------------------------\n";
        cout << endl;
        break;
    case 4:
        bitwise_and(in1, in2, out);
        cout << "\n-------------------------------------------\n" << colors::green << colors::bold << colors::italic << "Result(Binary): ";
        for (int i = 0; i < 32; i++) {
            cout << out[i];
        }
        binaryToDecimal(out);
        cout << "\nResult(Decimal): " << binaryToDecimal(out) << colors::reset << "\n-------------------------------------------\n";
        cout << endl;
        break;
    case 5:
        bitwise_or(in1, in2, out);
        cout << "\n-------------------------------------------\n" << colors::green << colors::bold << colors::italic << "Result(Binary): ";
        for (int i = 0; i < 32; i++) {
            cout << out[i];
        }
        binaryToDecimal(out);
        cout << "\nResult(Decimal): " << binaryToDecimal(out) << colors::reset << "\n-------------------------------------------\n";
        cout << endl;
        break;
    case 6:
        bitwise_xor(in1, in2, out);
        cout << "\n-------------------------------------------\n" << colors::green << colors::bold << colors::italic << "Result(Binary): ";
        for (int i = 0; i < 32; i++) {
            cout << out[i];
        }
        binaryToDecimal(out);
        cout << "\nResult(Decimal): " << binaryToDecimal(out) << colors::reset << "\n-------------------------------------------\n";
        cout << endl;
        break;
    case 7:
        increment(in1, out);
        cout << "\n-------------------------------------------\n" << colors::green << colors::bold << colors::italic << "Result(Binary): ";
        for (int i = 0; i < 32; i++) {
            cout << out[i];
        }
        binaryToDecimal(out);
        cout << "\nResult(Decimal): " << binaryToDecimal(out) << colors::reset << "\n-------------------------------------------\n";
        cout << endl;
        break;
    case 8:
        decrement(in1, out);
        cout << "\n-------------------------------------------\n" << colors::green << colors::bold << colors::italic << "Result(Binary): ";
        for (int i = 0; i < 32; i++) {
            cout << out[i];
        }
        binaryToDecimal(out);
        cout << "\nResult(Decimal): " << binaryToDecimal(out) << colors::reset << "\n-------------------------------------------\n";
        cout << endl;
        break;
    case 9:
        cout << colors::bold << "\nExiting..." << colors::reset << endl;
        break;
    case 10:
        main();
        break;
    default:
        cout << colors::on_bright_red << "\nInvalid operation code.\n" << colors::reset << endl;
        main();
        break;
}
return 0;
}