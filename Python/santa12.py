import json

data = ""

fin = open("in", 'r')

for line in fin:
    data += line

parsedJson = json.loads(data)

def getNum(element):

    sum = 0

    if isinstance(element, dict):
        for i in element:
            if element[i] == "red":
                return 0
            else:
                sum += getNum(element[i])

    elif isinstance(element, list):
        for i in element:
            sum += getNum(i)

    else:
        if isinstance(element, int):
            return (element)
        else:
            return 0

    return sum

print(getNum(parsedJson))
