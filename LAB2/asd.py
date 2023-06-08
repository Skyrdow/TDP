OPERATORS = {'+': 1, '-': 1, '*': 2, '/': 2}

def infix_to_rpn(expression):
    output = []
    stack = []

    for token in expression:
        if token.isdigit():
            output.append(token)
        elif token in OPERATORS:
            while stack and stack[-1] in OPERATORS and OPERATORS[token] <= OPERATORS[stack[-1]]:
                output.append(stack.pop())
            stack.append(token)
        elif token == '(':
            stack.append(token)
        elif token == ')':
            while stack and stack[-1] != '(':
                output.append(stack.pop())
            stack.pop()

    while stack:
        output.append(stack.pop())

    return output

def transform_equation(equation):
    equation = equation.replace(' ', '')
    output = infix_to_rpn(equation)
    return ' '.join(output)

equation = "3 + 4 * 2 / ( 1 - 5 )"
transformed_equation = transform_equation(equation)
print("Ecuación en notación polaca inversa (RPN):", transformed_equation)
