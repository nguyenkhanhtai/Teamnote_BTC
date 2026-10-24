#include <bits/stdc++.h>
#if !defined(BASELINE_LAYOUT)
#define TRANSPOSED
#endif
#if !defined(STREAMING) && !defined(BASELINE_LAYOUT) && !defined(BATCHED)
#define BATCHED
#endif
#if defined(USE_PRAGMA)
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif
using namespace std;
using Energy = long long;

struct Input {
    static constexpr size_t capacity = 1 << 16;
    char buffer[capacity];
    size_t position = 0, length = 0;
    char next() {
        if (position == length) {
            length = fread(buffer, 1, capacity, stdin);
            position = 0;
            if (!length) return 0;
        }
        return buffer[position++];
    }
    Energy read() {
        char symbol = next();
        while (symbol && symbol <= ' ') symbol = next();
        bool negative = symbol == '-';
        if (negative) symbol = next();
        Energy value = 0;
        while (symbol >= '0' && symbol <= '9') {
            value = value * 10 + symbol - '0';
            symbol = next();
        }
        return negative ? -value : value;
    }
};

struct PlaneDifference {
    int layers, rows, columns, rowStride, layerStride;
    vector<Energy> data;
    PlaneDifference(int layerCount, int rowCount, int columnCount)
        : layers(layerCount), rows(rowCount), columns(columnCount) {
#ifdef FIXED_STRIDE
        rowStride = 202;
        layerStride = 202 * 202;
        data.resize(202 * 202 * 202);
#else
        rowStride = columns + 2;
        layerStride = (rows + 2) * rowStride;
        data.resize((layers + 2) * layerStride);
#endif
    }
    int index(int layer, int row, int column) const {
        return layer * layerStride + row * rowStride + column;
    }
    void update(int layerLow, int layerHigh, int rowLow, int rowHigh,
                int columnLow, int columnHigh, Energy start, Energy step) {
#ifdef TRANSPOSED
        int offsets[4] = {
            index(rowLow, columnLow, layerLow),
            index(rowLow, columnHigh + 1, layerLow),
            index(rowHigh + 1, columnLow, layerLow),
            index(rowHigh + 1, columnHigh + 1, layerLow)
        };
        constexpr int stride = 1;
#else
        int offsets[4] = {
            index(layerLow, rowLow, columnLow),
            index(layerLow, rowLow, columnHigh + 1),
            index(layerLow, rowHigh + 1, columnLow),
            index(layerLow, rowHigh + 1, columnHigh + 1)
        };
        int stride = layerStride;
#endif
        if (start == 0 && step == 0) return;
        Energy* first = data.data() + offsets[0];
        Energy* second = data.data() + offsets[1];
        Energy* third = data.data() + offsets[2];
        Energy* fourth = data.data() + offsets[3];
        for (int offset = 0; offset <= layerHigh - layerLow; ++offset) {
            *first += start;
            *second -= start;
            *third -= start;
            *fourth += start;
            start += step;
            first += stride;
            second += stride;
            third += stride;
            fourth += stride;
        }
    }
    void prefix(int firstAxis, int secondAxis) {
        int strides[3] = {layerStride, rowStride, 1};
        for (int layer = 1; layer <= layers; ++layer) {
            for (int row = 1; row <= rows; ++row) {
                int base = index(layer, row, 1);
                for (int column = 0; column < columns; ++column) {
                    int position = base + column;
                    data[position] += data[position - strides[firstAxis]]
                        + data[position - strides[secondAxis]]
                        - data[position - strides[firstAxis] - strides[secondAxis]];
                }
            }
        }
    }
    Energy get(int layer, int row, int column) const {
        return data[index(layer, row, column)];
    }
};

int main() {
    Input input;
    int rows = input.read(), columns = input.read(), depth = input.read();
    int updates = input.read(), queries = input.read();
#ifdef TRANSPOSED
    PlaneDifference alongX(columns, depth, rows);
    PlaneDifference alongY(rows, depth, columns);
#else
    PlaneDifference alongX(rows, columns, depth);
    PlaneDifference alongY(columns, rows, depth);
#endif
    PlaneDifference alongZ(rows, columns, depth);
#ifdef BATCHED
    struct Activation {
        int xLow, yLow, zLow, xHigh, yHigh, zHigh;
        Energy initial, slopeX, slopeY, slopeZ;
    };
    vector<Activation> operations;
    operations.reserve(updates);
#endif
    for (int operation = 0; operation < updates; ++operation) {
        int xLow = input.read(), yLow = input.read(), zLow = input.read();
        int xHigh = input.read(), yHigh = input.read(), zHigh = input.read();
        Energy initial = input.read(), slopeX = input.read();
        Energy slopeY = input.read(), slopeZ = input.read();
#ifdef BATCHED
        operations.push_back({xLow, yLow, zLow, xHigh, yHigh, zHigh,
                              initial, slopeX, slopeY, slopeZ});
#else
        alongX.update(xLow, xHigh, yLow, yHigh, zLow, zHigh, initial, slopeX);
        alongY.update(yLow, yHigh, xLow, xHigh, zLow, zHigh, 0, slopeY);
#ifdef TRANSPOSED
        alongZ.update(zLow, zHigh, xLow, xHigh, yLow, yHigh, 0, slopeZ);
#else
        for (int z = zLow; z <= zHigh; ++z) {
            Energy value = slopeZ * (z - zLow);
            alongZ.data[alongZ.index(xLow, yLow, z)] += value;
            alongZ.data[alongZ.index(xHigh + 1, yLow, z)] -= value;
            alongZ.data[alongZ.index(xLow, yHigh + 1, z)] -= value;
            alongZ.data[alongZ.index(xHigh + 1, yHigh + 1, z)] += value;
        }
#endif
#endif
    }
#ifdef BATCHED
    for (const auto& operation : operations) {
        alongX.update(operation.xLow, operation.xHigh, operation.yLow, operation.yHigh,
                      operation.zLow, operation.zHigh, operation.initial, operation.slopeX);
    }
    for (const auto& operation : operations) {
        alongY.update(operation.yLow, operation.yHigh, operation.xLow, operation.xHigh,
                      operation.zLow, operation.zHigh, 0, operation.slopeY);
    }
    for (const auto& operation : operations) {
        alongZ.update(operation.zLow, operation.zHigh, operation.xLow, operation.xHigh,
                      operation.yLow, operation.yHigh, 0, operation.slopeZ);
    }
#endif
#ifdef TRANSPOSED
    alongX.prefix(0, 1);
    alongY.prefix(0, 1);
#else
    alongX.prefix(1, 2);
    alongY.prefix(1, 2);
#endif
    alongZ.prefix(0, 1);
    string output;
    output.reserve(size_t(queries) * 22);
    for (int query = 0; query < queries; ++query) {
        int x = input.read(), y = input.read(), z = input.read();
#ifdef TRANSPOSED
        Energy result = alongX.get(y, z, x) + alongY.get(x, z, y);
#else
        Energy result = alongX.get(x, y, z) + alongY.get(y, x, z);
#endif
        result += alongZ.get(x, y, z);
        output += to_string(result);
        output += '\n';
    }
    fwrite(output.data(), 1, output.size(), stdout);
}
