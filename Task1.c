#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#define size (int)sizeof(int) * 8

void printBinaryNumber(int array[])
{
    for (int i = 0; i < size; i++)
    {
        printf("%d", array[i]);
    }
    printf("\n");
}

void convertToBinary(int decimalNumber, int binaryNumber[])
{
    int bit = 0b10000000;
    for (int i = 0; i < size; i++)
    {
        binaryNumber[i] = (decimalNumber & bit) ? 1 : 0;
        bit = bit >> 1;
    }
}

void sumOfTwoBinaryNumbers(int firstNumber[], int secondNumber[], int sumOfNumbers[])
{
    int carryToNextPosition = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        sumOfNumbers[i] = (firstNumber[i] + secondNumber[i] + carryToNextPosition) % 2;
        carryToNextPosition = (firstNumber[i] + secondNumber[i] + carryToNextPosition) / 2;
    }
}

int convertToDecimal(int binaryNumber[])
{
    int decimalNumber = 0;
    int powerOfTwo = 1;
    for (int i = size - 1; i >= 0; i--)
    {
        decimalNumber += powerOfTwo * binaryNumber[i];
        powerOfTwo *= 2; 
    }
    return decimalNumber;
}

int main()
{
    printf("Enter first number: ");
    int firstNumber = 0;
    int scanned = scanf("%d", &firstNumber);
    while (scanned == 0 || firstNumber <= 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a natural number, try again: ");
        scanned = scanf("%d", &firstNumber);
    }
    printf("Enter second number: ");
    int secondNumber = 0;
    scanned = scanf("%d", &secondNumber);
    while (scanned == 0 || secondNumber <= 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a natural number, try again: ");
        scanned = scanf("%d", &secondNumber);
    }

    printf("Binary representation of first number: ");
    int firstBin[size] = {0};
    convertToBinary(firstNumber, firstBin);
    printBinaryNumber(firstBin);

    printf("Binary representation of second number: ");
    int secondBin[size] = {0};
    convertToBinary(secondNumber, secondBin);
    printBinaryNumber(secondBin);

    printf("Sum of entered numbers in binary representation: ");
    int sumOfNumbers[size] = {0};
    sumOfTwoBinaryNumbers(firstBin, secondBin, sumOfNumbers);
    printBinaryNumber(sumOfNumbers);

    printf("Sum of entered numbers in decimal representation: ");
    printf("%d", convertToDecimal(sumOfNumbers));

    return 0;
}
