#include <stdio.h>
#include <string.h>

typedef struct BigInteger
{
    int digits[1000];
    int size;
    int sign;
} BigInt;
void printBigInteger();
BigInt add_bigint();
BigInt sub_bigint();
BigInt mul_bigint();
BigInt subtractaddBigIntegers();
BigInt sub();

BigInt read()
{
    BigInt number;
    int sign_int;
    printf("enter the sign of number: ");
    char sign_string[1];
    scanf("%s", sign_string);
    if (strcmp(sign_string, "+") == 0)
    {
        sign_int = 0;
    }
    else if (strcmp(sign_string, "-") == 0)
    {
        sign_int = 1;
    }
    number.sign = sign_int;
    printf("Enter the magnitude of number: ");
    char inputString[1000];
    scanf("%s", inputString);

    int length = strlen(inputString);

    int index = 0;

    for (int i = length - 1; i >= 0; i--)
    {
        number.digits[index] = inputString[i] - '0';
        index++;
    }

    number.size = index;
    return number;
}

void printBigInteger(BigInt number)
{
    if (number.sign == 1)
    {
        printf("-");
    }
    for (int i = number.size - 1; i >= 0; i--)
    {
        printf("%d", number.digits[i]);
    }
    printf("\n");
}

BigInt add_bigint(BigInt a, BigInt b)
{
    BigInt result;
    if (a.sign == b.sign)
    {
        if (a.size < b.size)
        {
            return add_bigint(b, a);
        }

        int index = 0;
        int carry = 0;

        for (int i = 0; i < b.size; i++)
        {
            int sum = a.digits[i] + b.digits[i] + carry;
            result.digits[index] = sum % 10;
            carry = sum / 10;
            index++;
        }

        for (int i = b.size; i < a.size; i++)
        {
            int sum = a.digits[i] + carry;
            result.digits[index] = sum % 10;
            carry = sum / 10;
            index++;
        }

        while (carry > 0)
        {
            result.digits[index] = carry % 10;
            carry = carry / 10;
            index++;
        }

        result.size = index;
        if (a.sign == 0)
        {
            result.sign = 0;
        }
        else if (a.sign == 1)
        {
            result.sign = 1;
        }
        return result;
    }
    else
    {
        if (a.sign == 0 && b.sign == 1)
        {
            if (a.size < b.size)
            {

                BigInt temp = a;
                a = b;
                b = temp;
            }
            result = sub(a, b);
        }
        else if (a.sign == 1 && b.sign == 0)
        {
            if (a.size > b.size)
            {

                BigInt temp = a;
                a = b;
                b = temp;
            }
            result = sub(b, a);
        }
    }
    return result;
}
BigInt sub(BigInt a, BigInt b)
{
    BigInt result;
    result.sign = a.sign;
    if (a.size == b.size)
    {
        int i = a.size - 1;
        while (i >= 0 && a.digits[i] == b.digits[i])
        {
            i--;
        }
        if (i == -1)
        {
            result.digits[0] = 0;
        }
        if (a.digits[i] < b.digits[i])
        {
            if (a.sign == 0)
            {
                result.sign = 1;
            }

            BigInt temp = a;
            a = b;
            b = temp;
        }
        if (a.digits[i] > b.digits[i])
        {
            if (a.sign == 1)
            {
                result.sign = 1;
            }
        }
    }

    int index = 0;
    int lastNonZeroIndex = 0;

    for (int i = 0; i < b.size; i++)
    {
        if (a.digits[i] - b.digits[i] < 0)
        {
            a.digits[i + 1]--;
            a.digits[i] += 10;
        }
        result.digits[index] = a.digits[i] - b.digits[i];
        if (result.digits[index] != 0)
        {
            lastNonZeroIndex = i;
        }
        index++;
    }

    for (int i = b.size; i < a.size; i++)
    {
        if (a.digits[i] != 0)
        {
            lastNonZeroIndex = i;
        }
        if (a.digits[i] < 0)
        {
            a.digits[i + 1]--;
            a.digits[i] += 10;
        }
        result.digits[index] = a.digits[i];
        index++;
    }

    result.size = lastNonZeroIndex + 1;

    return result;
}
BigInt subtractaddBigIntegers(BigInt a, BigInt b)
{
    BigInt result;

    if (a.size < b.size)
    {

        BigInt temp = a;
        a = b;
        b = temp;
    }
    int index = 0;
    int carry = 0;

    for (int i = 0; i < b.size; i++)
    {
        int sum = a.digits[i] + b.digits[i] + carry;
        result.digits[index] = sum % 10;
        carry = sum / 10;
        index++;
    }

    for (int i = b.size; i < a.size; i++)
    {
        int sum = a.digits[i] + carry;
        result.digits[index] = sum % 10;
        carry = sum / 10;
        index++;
    }

    while (carry > 0)
    {
        result.digits[index] = carry % 10;
        carry = carry / 10;
        index++;
    }

    result.size = index;

    return result;
}

BigInt sub_bigint(BigInt a, BigInt b)
{
    int isNegative = 0;
    BigInt result;
    if (a.sign != b.sign)
    {
        result = subtractaddBigIntegers(a, b);
        if (a.sign == 0)
        {
            result.sign = 0;
        }
        else if (a.sign == 1)
        {
            result.sign = 1;
        }
        return result;
    }
    else if (a.sign == b.sign)
    {
        result.sign = 0;

        if (a.size < b.size)
        {

            BigInt temp = a;
            a = b;
            b = temp;
            if (a.sign == 0)
            {
                result.sign = 1;
            }
            else if (a.sign == 1)
            {
                result.sign = 0;
            }
        }
        else if (a.size > b.size)
        {
            if (a.sign == 0)
            {
                result.sign = 0;
            }
            else if (a.sign == 1)
            {
                result.sign = 1;
            }
        }
        if (a.size == b.size)
        {
            int i = a.size - 1;
            while (i >= 0 && a.digits[i] == b.digits[i])
            {
                i--;
            }
            if (i == -1)
            {
                result.digits[0] = 0;
            }
            if (a.digits[i] < b.digits[i])
            {
                if (a.sign == 0)
                {
                    result.sign = 1;
                }

                BigInt temp = a;
                a = b;
                b = temp;
            }
            else if (a.digits[i] > b.digits[i])
            {
                if (a.sign == 1)
                {
                    result.sign = 1;
                }
            }
        }

        int index = 0;
        int lastNonZeroIndex = 0;

        for (int i = 0; i < b.size; i++)
        {
            if (a.digits[i] - b.digits[i] < 0)
            {
                a.digits[i + 1]--;
                a.digits[i] += 10;
            }
            result.digits[index] = a.digits[i] - b.digits[i];
            if (result.digits[index] != 0)
            {
                lastNonZeroIndex = i;
            }
            index++;
        }

        for (int i = b.size; i < a.size; i++)
        {
            if (a.digits[i] != 0)
            {
                lastNonZeroIndex = i;
            }
            if (a.digits[i] < 0)
            {
                a.digits[i + 1]--;
                a.digits[i] += 10;
            }
            result.digits[index] = a.digits[i];
            index++;
        }

        result.size = lastNonZeroIndex + 1;

        return result;
    }
}

BigInt mul_bigint(BigInt a, BigInt b)
{
    BigInt result;
    result.size = 0;

        for (int i = 0; i < a.size; i++)
    {
        int carry = 0;
        BigInt tempResult;
        int index = 0;

        for (int j = 0; j < b.size; j++)
        {
            int temp = a.digits[i] * b.digits[j] + carry;
            tempResult.digits[index] = temp % 10;
            carry = temp / 10;
            index++;
        }

        while (carry > 0)
        {
            tempResult.digits[index] = carry % 10;
            carry /= 10;
            index++;
        }

        tempResult.size = index;

        BigInt productWithZeros;
        int zeroIndex = 0;

        for (int p = 0; p < i; p++)
        {
            productWithZeros.digits[zeroIndex] = 0;
            zeroIndex++;
        }

        for (int p = 0; p < tempResult.size; p++)
        {
            productWithZeros.digits[zeroIndex] = tempResult.digits[p];
            zeroIndex++;
        }

        productWithZeros.size = zeroIndex;
        result = subtractaddBigIntegers(result, productWithZeros);
    }
    if (a.sign == b.sign)
    {
        result.sign = 0;
    }
    else if (a.sign != b.sign)
    {
        result.sign = 1;
    }

    return result;
}

int main()
{
    BigInt num1 = read();
    BigInt num2 = read();

    BigInt sum = add_bigint(num1, num2);
    printf("Sum: ");
    printBigInteger(sum);

    printf("Difference: ");
    BigInt di = sub_bigint(num1, num2);
    printBigInteger(di);

    BigInt product = mul_bigint(num1, num2);
    printf("Product: ");
    printBigInteger(product);

    return 0;
}
