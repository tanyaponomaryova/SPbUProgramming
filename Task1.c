#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE ((int)sizeof(int) * 8) // размер типа int в битах

void printBinaryNumber(int array[])
{
    int j = 0;
    for (; j < SIZE - 1 && array[j] == 0; j++); // пропускаем незначащие нули и останавливаемся на первом разряде на случай если распечатываемое число == 0
    for (int i = j; i < SIZE; i++)
    {
        printf("%d", array[i]);
    }
    printf("\n");
}

void convertToBinary(int decimalNumber, int binaryNumber[])
{
    int bit = 1;
    for (int i = SIZE - 1; i >= 0; i--)
    {
        binaryNumber[i] = (decimalNumber & bit) ? 1 : 0;
        bit = bit << 1;
    }
}

void sumOfTwoBinaryNumbers(int firstNumber[], int secondNumber[], int sumOfNumbers[])
{
    int carryToNextPosition = 0;
    for (int i = SIZE - 1; i >= 0; i--)
    {
        sumOfNumbers[i] = (firstNumber[i] + secondNumber[i] + carryToNextPosition) % 2;
        carryToNextPosition = (firstNumber[i] + secondNumber[i] + carryToNextPosition) / 2;
    }
}

int convertToDecimal(int binaryNumber[])
{
    int decimalNumber = 0;
    int powerOfTwo = 1;
    for (int i = SIZE - 1; i >= 0; i--)
    {
        decimalNumber += powerOfTwo * binaryNumber[i];
        powerOfTwo *= 2;
    }
    return decimalNumber;
}

int main()
{
    printf("This program takes two integers as input, converts them to binary numbers, \n");
    printf("calculates their sum in binary representation and then converts their sum to decimal number!\n");
    printf("Enter first number: ");
    int firstNumber = 0;
    int scanned = scanf("%d", &firstNumber);
    while (scanned == 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a number, try again: ");
        scanned = scanf("%d", &firstNumber);
    }
    printf("Enter second number: ");
    int secondNumber = 0;
    scanned = scanf("%d", &secondNumber);
    while (scanned == 0)
    {
        scanf("%*[^\n]");
        printf("You didn't enter a number, try again: ");
        scanned = scanf("%d", &secondNumber);
    }
    printf("Binary representation of first number: ");
    int firstBin[SIZE] = {0};
    convertToBinary(firstNumber, firstBin);
    printBinaryNumber(firstBin);

    printf("Binary representation of second number: ");
    int secondBin[SIZE] = {0};
    convertToBinary(secondNumber, secondBin);
    printBinaryNumber(secondBin);

    printf("Sum of entered numbers in binary representation: ");
    int sumOfNumbers[SIZE] = {0};
    sumOfTwoBinaryNumbers(firstBin, secondBin, sumOfNumbers);
    printBinaryNumber(sumOfNumbers);

    printf("Sum of entered numbers in decimal representation: ");
    printf("%d", convertToDecimal(sumOfNumbers));
    return 0;
}