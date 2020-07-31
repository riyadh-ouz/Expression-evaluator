#include <iostream>
#include <stack>
#include <string>
#include <exception>
#include <cassert>

using namespace std;

class Error : public exception
{
public:
    Error(string const& desc = "Unknown Error") throw()
        :m_desc(desc)
    {}
    virtual const char* what() const throw()
    {
        return m_desc.c_str();
    }

    virtual ~Error() throw()
    {}

private:
    string m_desc;
};

template <typename T>
void evaluate(stack<T>& operands, stack<char>& operators) {

    T a = operands.top();
    operands.pop();
    T b = operands.top();
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
        if (a == 0) throw Error("ZeroDivision");
        operands.push(b / a);
        break;
    default:
        throw Error("Invalid Operator");
        break;

    }

}

int precedence(char o) {
    if (o == '+' || o == '-') return 0;
    else if (o == '*' || o == '/') return 1;
    // case: math functions as the pow or ^
    else throw Error("Invalid Operator");
}

template <typename T>
T eval(string const& exp) {

    stack<T> operands;
    stack<char> operators;

    for (unsigned i = 0; i < exp.length(); i++) {
        // case: operand
        if (exp[i] >= '0' && exp[i] <= '9') {

            T x = 0;
            unsigned unit;
            do {
                unit = exp[i] - '0';
                x = 10 * x + unit;
                i++;
                if (i == exp.length()) break;
            } while (exp[i] >= '0' && exp[i] <= '9');

            if (exp[i] == '.') {
                i++;
                unsigned puiss = 10;
                while (exp[i] >= '0' && exp[i] <= '9')
                {
                    unit = exp[i] - '0';
                    x += (T) unit / puiss;
                    puiss *= 10;
                    i++;
                    if (i == exp.length()) break;
                }

            }

            operands.push(x);
            // to reset to the current place after incrementation
            i--;
        }

        // case: operator
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            
            // testing double operators
            unsigned j = i - 1;
            while (j >= 0 && exp[j] == ' ') {
                j--;
            }
            if (exp[j] == '+' || exp[j] == '-' || exp[j] == '*' || exp[j] == '/')
                throw Error("Invalid Expression::Double Operator");

            else if (operators.empty() || operators.top() == '(') operators.push(exp[i]);
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

        // case: space
        else if (exp[i] == ' ') continue;

        // case: Invalid Expression
        else throw Error("Invalid Expression::Unknown Character");
        
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
    
    try {
        assert(eval<int>("14 * 5 + (55 - 20) - 9 / 8") == 14 * 5 + (55 - 20) - 9 / 8);

        // Testing errors:
        // cout << eval<double>("14.05 /f 0.5 + (100 * 20) - 9 / 8") << endl;
        // cout << eval<double>("14..05 / 0.5 + (100 * 20) - 9 / 8") << endl;
        // cout << eval<double>("14.0.5 / 0.5 + (100 * 20) - 9 / 8") << endl;
        // cout << eval<double>("14.05 / / 0.5 + (100 * 20) - 9 / 8") << endl;
        // cout << eval<int>("14 * 5 + (55 - 20) - 9 / 0");

        cout << eval<float>("14 / 5 + (100 * 20) - 9 / 8") << endl;
        cout << eval<int>("14 / 5 + (100 * 20) - 9 / 8") << endl;
        cout << "All tests have been passed successfully" << endl;

    }
    catch (std::exception const& e) {
        cerr << "Error: " << e.what();
    }
    
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