def evaluate(operands, operators):
    
    a = operands.pop()
    b = operands.pop()
    
    if operators[len(operators)-1] == '+':
        operands.append(b + a)
        return b + a
    elif operators[len(operators)-1] == '-':
        operands.append(b - a)
        return b - a
    elif operators[len(operators)-1] == '*':
        operands.append(b * a)
        return b * a
    elif operators[len(operators)-1] == '/':
        if a == 0: raise ZeroDivisionError
        operands.append(b / a)
        return b / a
        
    # handle default case
    else: raise ValueError


def precedence(operator):
    if operator == '+' or operator == '-':
        return 0
    elif operator == '*' or operator == '/':
        return 1
    # case: math functions
    else: raise ValueError


def eval_exp(exp):

    operands = []
    operators = []

    i = 0
    # to track the last element
    last = '0'
    # to track parenthesis
    open_p = 0
    
    while i < len(exp):

        # case: operand
        if exp[i] >= '0' and exp[i] <= '9':

            if last == 'N': raise SyntaxError
            
            x = 0
            while exp[i] >= '0' and exp[i] <= '9':
                x = 10 * x + int(exp[i])
                i += 1
                if i == len(exp): break
                
            if i < len(exp):
                if exp[i] == '.':
                    i += 1
                    puiss = 10
                    while exp[i] >= '0' and exp[i] <= '9':
                        x += int(exp[i]) / puiss
                        puiss *= 10
                        i += 1
                        if i == len(exp): break 

            operands.append(x)
            last = 'N'

            # to reset to the current place after incrementation
            i -= 1
            
        # case: operator
        elif exp[i] == '+' or exp[i] == '-' or exp[i] == '*' or exp[i] == '/':

            if last == 'O': raise SyntaxError

            if len(operators) == 0 or operators[len(operators)-1] == '(':
                operators.append(exp[i])
            elif precedence(exp[i]) > precedence(operators[len(operators)-1]):
                operators.append(exp[i])
            else:

                while len(operators) != 0 and operators[len(operators)-1] != '(':
                    evaluate(operands, operators)
                    operators.pop()
                    
                operators.append(exp[i])
            last = 'O'

        # case: open parentheses
        elif exp[i] == '(':
            operators.append('(')
            open_p += 1

        # case: close parantheses
        elif exp[i] == ')':

            if open_p < 1: raise SyntaxError

            while operators[len(operators)-1] != '(':

                evaluate(operands, operators)
                operators.pop()

            
            operators.pop()
            open_p -= 1

        # case: space
        elif exp[i] == ' ': pass

        # case: default
        else: raise SyntaxError
        
        # increment i inside the while loop
        i += 1
    
    # final calculations
    if len(operators) != 0:

        while len(operators) != 0:

            evaluate(operands, operators)
            operators.pop()

    
    return operands.pop()

#testing our function
#the following block is not imported, but run as script
# __name__ is special variable defined by the iterpreter before execution
if __name__ == "__main__":
    
    try:
        print('Enter Q to quit the test')
        while True:
            test = input('Enter expression to evaluate: ')
            if test == 'Q':
                break
            assert eval(test) == eval_exp(test)
            print(eval_exp(test))
        

    except SyntaxError:
        print("Invalid Expression")
    except ZeroDivisionError:
        print("Zero Division Error")
    except ValueError:
        print("Invalid Operator")
    except AssertionError:
        print("Assert Error")
    except:
        print("Error Occured")
    finally:
        print('Finished')

