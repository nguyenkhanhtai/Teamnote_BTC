#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
using Energy = long long;
constexpr int maxDimension = 202;
Energy sumA[maxDimension][maxDimension][maxDimension];
Energy sumB[maxDimension][maxDimension][maxDimension];
Energy sumC[maxDimension][maxDimension][maxDimension];
#ifdef USE_FAST_IO
char inputBuffer[1 << 16], outputBuffer[1 << 16];
int inputPosition = 0, inputLength = 0, outputPosition = 0;
char nextChar() {
    if (inputPosition == inputLength) {
        inputLength = fread(inputBuffer, 1, sizeof(inputBuffer), stdin);
        inputPosition = 0;
        if (!inputLength) return 0;
    }
    return inputBuffer[inputPosition++];
}
Energy readInt() {
    char symbol = nextChar();
    while (symbol && symbol <= ' ') symbol = nextChar();
    bool negative = symbol == '-';
    if (negative) symbol = nextChar();
    Energy value = 0;
    while (symbol >= '0' && symbol <= '9') {
        value = value * 10 + symbol - '0';
        symbol = nextChar();
    }
    return negative ? -value : value;
}
void putChar(char symbol) {
    if (outputPosition == int(sizeof(outputBuffer))) {
        fwrite(outputBuffer, 1, outputPosition, stdout);
        outputPosition = 0;
    }
    outputBuffer[outputPosition++] = symbol;
}
void writeInt(Energy value) {
    unsigned long long magnitude = value;
    if (value < 0) {
        putChar('-');
        magnitude = 0ULL - magnitude;
    }
    char digits[20];
    int count = 0;
    do {
        digits[count++] = '0' + magnitude % 10;
        magnitude /= 10;
    } while (magnitude);
    while (count) putChar(digits[--count]);
    putChar('\n');
}
#endif
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rows, columns, depth, updates, queries;
#ifdef USE_FAST_IO
    rows = readInt(); columns = readInt(); depth = readInt();
    updates = readInt(); queries = readInt();
#else
    cin >> rows >> columns >> depth >> updates >> queries;
#endif
    for (int operation = 0; operation < updates; ++operation) {
        int xLow, yLow, zLow, xHigh, yHigh, zHigh;
        Energy initial, slopeX, slopeY, slopeZ;
#ifdef USE_FAST_IO
        xLow = readInt(); yLow = readInt(); zLow = readInt();
        xHigh = readInt(); yHigh = readInt(); zHigh = readInt();
        initial = readInt(); slopeX = readInt(); slopeY = readInt(); slopeZ = readInt();
#else
        cin >> xLow >> yLow >> zLow >> xHigh >> yHigh >> zHigh
            >> initial >> slopeX >> slopeY >> slopeZ;
#endif
        Energy value = initial;
        for (int x = xLow; x <= xHigh; ++x, value += slopeX) {
            sumA[x][yLow][zLow] += value;
            sumA[x][yLow][zHigh + 1] -= value;
            sumA[x][yHigh + 1][zLow] -= value;
            sumA[x][yHigh + 1][zHigh + 1] += value;
        }
        value = 0;
        for (int y = yLow; y <= yHigh; ++y, value += slopeY) {
            sumB[xLow][y][zLow] += value;
            sumB[xLow][y][zHigh + 1] -= value;
            sumB[xHigh + 1][y][zLow] -= value;
            sumB[xHigh + 1][y][zHigh + 1] += value;
        }
        value = 0;
        for (int z = zLow; z <= zHigh; ++z, value += slopeZ) {
            sumC[xLow][yLow][z] += value;
            sumC[xLow][yHigh + 1][z] -= value;
            sumC[xHigh + 1][yLow][z] -= value;
            sumC[xHigh + 1][yHigh + 1][z] += value;
        }
    }
    for (int x = 1; x <= rows; ++x) {
        for (int y = 1; y <= columns; ++y) {
            for (int z = 1; z <= depth; ++z) {
                sumA[x][y][z] += sumA[x][y - 1][z] + sumA[x][y][z - 1]
                    - sumA[x][y - 1][z - 1];
                sumB[x][y][z] += sumB[x - 1][y][z] + sumB[x][y][z - 1]
                    - sumB[x - 1][y][z - 1];
                sumC[x][y][z] += sumC[x - 1][y][z] + sumC[x][y - 1][z]
                    - sumC[x - 1][y - 1][z];
            }
        }
    }
    for (int query = 0; query < queries; ++query) {
        int x, y, z;
#ifdef USE_FAST_IO
        x = readInt(); y = readInt(); z = readInt();
        writeInt(sumA[x][y][z] + sumB[x][y][z] + sumC[x][y][z]);
#else
        cin >> x >> y >> z;
        cout << sumA[x][y][z] + sumB[x][y][z] + sumC[x][y][z] << '\n';
#endif
    }
#ifdef USE_FAST_IO
    fwrite(outputBuffer, 1, outputPosition, stdout);
#endif
}
