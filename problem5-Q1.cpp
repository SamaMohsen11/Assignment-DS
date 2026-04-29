#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

class Calculator {
private:
    stack<int> st;
    int result;
    int sign;

    bool lastWasOperator;
    bool lastWasDigit;

public:
    Calculator() {
        result = 0;
        sign = 1;
        lastWasOperator = true;
        lastWasDigit = false;
    }

    int calculate(string s) {

        for (int i = 0; i < s.length(); i++) {

            if (s[i] == ' ') continue;

            if (isdigit(s[i])) {

                if (lastWasDigit) {
                    cout << "Invalid";
                    exit(0);
                }

                int num = 0;
                while (i < s.length() && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }

                result += sign * num;
                i--;

                lastWasDigit = true;
                lastWasOperator = false;
            }

            else if (s[i] == '+' || s[i] == '-') {

                if (lastWasOperator && !st.empty()) {
                    cout << "Invalid";
                    exit(0);
                }

                if (s[i] == '+' && lastWasOperator) {
                    cout << "Invalid";
                    exit(0);
                }

                if (s[i] == '+') sign = 1;
                else sign = -1;

                lastWasOperator = true;
                lastWasDigit = false;
            }

            else if (s[i] == '(') {
                st.push(result);
                st.push(sign);
                result = 0;
                sign = 1;

                lastWasOperator = true;
                lastWasDigit = false;
            }

            else if (s[i] == ')') {
                int prevSign = st.top(); st.pop();
                int prevResult = st.top(); st.pop();

                result = prevResult + prevSign * result;

                lastWasOperator = false;
                lastWasDigit = true;
            }

            else {
                cout << "Invalid" << endl;
                exit(0);
            }
        }

        return result;
    }
};

int main() {
    string s;

    cout << "Enter expression: ";
    getline(cin, s);

    Calculator calc;
    cout << "Result = " << calc.calculate(s) << endl;

    return 0;
}
