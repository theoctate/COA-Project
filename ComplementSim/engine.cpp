#include <emscripten.h>

extern "C"
{
    int gate_NOT(int a) { return 1 - a; }
    int gate_AND(int a, int b) { return a & b; }
    int gate_XOR(int a, int b) { return a ^ b; }

    EMSCRIPTEN_KEEPALIVE
    int calculate_complement(int bit3, int bit2, int bit1, int bit0)
    {
        int y3 = gate_NOT(bit3);
        int y2 = gate_NOT(bit2);
        int y1 = gate_NOT(bit1);
        int y0 = gate_NOT(bit0);

        int s0 = gate_NOT(y0);
        int c1 = y0;
        int s1 = gate_XOR(y1, c1);
        int c2 = gate_AND(y1, c1);
        int s2 = gate_XOR(y2, c2);
        int c3 = gate_AND(y2, c2);
        int s3 = gate_XOR(y3, c3);

        int s_pack = (s3 << 3) | (s2 << 2) | (s1 << 1) | s0;
        int y_pack = (y3 << 3) | (y2 << 2) | (y1 << 1) | y0;
        int c_pack = (c3 << 3) | (c2 << 2) | (c1 << 1) | 0;

        return s_pack | (y_pack << 4) | (c_pack << 8);
    }
}