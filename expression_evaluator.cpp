#include <iostream>
#include <stack>
#include <cassert>

using namespace std;

void evaluate(stack<int>& operands, stack<char>& operators) {

    int a = operands.top();
    operands.pop();
    int b = operands.top();
    operands.pop();

    switch (operators.top()) {

    case '+':
        operands.push(b + a);
        break;
    case '-':
        operands.push(b - a);
        break;
    case '*':
        operands.push(b * a);
        break;
    case '/':
        operands.push(b / a);
        break;

        // handle default case;

    }

}

int precedence(char o) {
    if (o == '+' || o == '-') return 0;
    else if (o == '*' || o == '/') return 1;
    // case: functions as the pow or ^
    // else throw an error
}

int eval(const string& exp) {

    stack<int> operands;
    stack<char> operators;

    for (int i = 0; i < exp.length(); i++) {

        // case: operand
        if (exp[i] >= '0' && exp[i] <= '9') {
            // enhancement: get the float operand
            int x = 0;
            do {
                x = 10 * x + (exp[i] - '0');
                i++;
                if (i == exp.length()) break;
            } while (exp[i] >= '0' && exp[i] <= '9');

            operands.push(x);
            // to reset to the current place after incrementation
            i--;
        }

        // case: operator
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {

            if (operators.empty() || operators.top() == '(') operators.push(exp[i]);
            else if (precedence(exp[i]) > precedence(operators.top())) operators.push(exp[i]);
            else {

                do {

                    evaluate(operands, operators);
                    operators.pop();

                } while (!operators.empty() && !(operators.top() == '('));

                operators.push(exp[i]);
            }

        }

        // case: open parentheses
        else if (exp[i] == '(') operators.push('(');

        // case: close parantheses
        else if (exp[i] == ')') {

            do {

                evaluate(operands, operators);
                operators.pop();

            } while (operators.top() != '(');
            operators.pop();

        }

        // case: else throw an error

    }


    // final calculations
    if (!operators.empty()) {

        do {

            evaluate(operands, operators);
            operators.pop();

        } while (!operators.empty());

    }

    return operands.top();
}

int main()
{
    assert(eval("14/5*(6-88)") == (14 / 5 * (6 - 88)));
    assert(eval("656-757*(9+9)") == (656 - 757 * (9 + 9)));
    assert(eval("589") == 589);
    cout << "All tests have been passed successfully";
    return 0;
}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.