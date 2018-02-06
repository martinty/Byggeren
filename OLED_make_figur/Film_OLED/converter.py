

def main():
    matrix = [[0 for col in range(0,64)] for row in range(0,8)]
    D = [[0 for col in range(0,8)] for row in range(0,64)]
    A = [[0 for col in range(0,8)] for row in range(0,64)]
    print("Navnet på filen: ")
    name = input()
    rName = name + ".txt"
    wName = name + ".h"
    with open(rName, "r") as f:
        newFile = open(wName, 'w')
        newFile.write("#include <avr/pgmspace.h>\n\n#define FONTSIZE 8\n\nconst unsigned char PROGMEM fontFigur[64][8] = {\n")
        rowCount = 0
        colCount = 0
        for line in f:
            for element in line:
                if colCount < 64:
                    if element == "0":
                        matrix[rowCount][colCount] = "1"
                    elif element == "1":
                        matrix[rowCount][colCount] = "0"
                    else:
                        matrix[rowCount][colCount] = element
                    colCount += 1
            colCount = 0
            rowCount += 1
            if rowCount == 8:
                rowCount = 0
                for x in range(0, 8, 1):
                    for y in range(0, 64, 1):
                        D[y][x] = matrix[x][y]
                for x in range(0, 8, 1):
                    for y in range(0, 64, 1):
                        A[y][x] = D[y][7-x]
                wordCount = 1
                for word in A:
                    if wordCount == 1:
                        newFile.write("	{0b")
                        for element in word:
                            newFile.write(element)
                        newFile.write(", ")
                    elif wordCount == 8:
                        newFile.write("0b")
                        for element in word:
                            newFile.write(element)
                        newFile.write("},\n")
                        wordCount = 0
                    else:
                        newFile.write("0b")
                        for element in word:
                            newFile.write(element)
                        newFile.write(", ")  
                    wordCount += 1
        newFile.write("};\n")
        newFile.close()

main()
