
# lets try naive solution first
# lets assume we use "and", "or", "=>"

logicalConnectors = ["and", "or", "=>", "<=>"]

def solveEquation(cleanedEquation):
    # lets ignore parentheses for now
    # assume it's a valid equation
    equationParts = cleanedEquation.split(' ')
    solveQueue = [] # use python list as queue
    expression = []
    for part in equationParts:
        expression.append(part)
        if len(expression) == 3:
            solveQueue.append(expression)
    print(solveQueue)

solveEquation("a or b")
