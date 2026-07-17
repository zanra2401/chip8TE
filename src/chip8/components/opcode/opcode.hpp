#pragma once

#include <cstdint>
#include <string>

// Enum untuk merepresentasikan jenis-jenis instruksi CHIP-8
enum class InstructionType {
    SYS,            // 0NNN (Diabaikan di emulator modern)
    CLS,            // 00E0 - Clear Screen
    RET,            // 00EE - Return
    JP,             // 1NNN - Jump
    CALL,           // 2NNN - Call
    SE_BYTE,        // 3XNN - Skip if Vx == NN
    SNE_BYTE,       // 4XNN - Skip if Vx != NN
    SE_REG,         // 5XY0 - Skip if Vx == Vy
    LD_BYTE,        // 6XNN - Vx = NN
    ADD_BYTE,       // 7XNN - Vx = Vx + NN
    LD_REG,         // 8XY0 - Vx = Vy
    OR_REG,         // 8XY1 - Vx = Vx | Vy
    AND_REG,        // 8XY2 - Vx = Vx & Vy
    XOR_REG,        // 8XY3 - Vx = Vx ^ Vy
    ADD_REG,        // 8XY4 - Vx = Vx + Vy (Set VF)
    SUB_REG,        // 8XY5 - Vx = Vx - Vy (Set VF)
    SHR_REG,        // 8XY6 - Vx = Vx >> 1 (Set VF)
    SUBN_REG,       // 8XY7 - Vx = Vy - Vx (Set VF)
    SHL_REG,        // 8XYE - Vx = Vx << 1 (Set VF)
    SNE_REG,        // 9XY0 - Skip if Vx != Vy
    LD_I,           // ANNN - I = NNN
    JP_V0,          // BNNN - Jump to V0 + NNN
    RND,            // CXNN - Vx = Rand() & NN
    DRW,            // DXYN - Draw sprite at Vx, Vy
    SKP,            // EX9E - Skip if key(Vx) is pressed
    SKNP,           // EXA1 - Skip if key(Vx) is not pressed
    LD_VX_DT,       // FX07 - Vx = Delay Timer
    LD_KEY,         // FX0A - Wait for key, Vx = key
    LD_DT_VX,       // FX15 - Delay Timer = Vx
    LD_ST_VX,       // FX18 - Sound Timer = Vx
    ADD_I_VX,       // FX1E - I = I + Vx
    LD_F_VX,        // FX29 - I = sprite address for digit Vx
    LD_B_VX,        // FX33 - Store BCD of Vx in I, I+1, I+2
    LD_I_VX,        // FX55 - Store V0..Vx in memory starting at I
    LD_VX_I,        // FX65 - Read V0..Vx from memory starting at I
    UNKNOWN         // Instruksi tidak dikenali
};

class Opcode {
private:
    uint16_t instruction;

public:
    Opcode();
    Opcode(uint16_t inst);
    Opcode(uint8_t byte1, uint8_t byte2);

    void set_instruction(uint16_t inst);
    void set_instruction(uint8_t byte1, uint8_t byte2);
    
    uint16_t get_instruction() const;

    // Bagian-bagian dari opcode CHIP-8 (tiap opcode 16-bit / 2 byte)
    uint8_t get_type() const;  // 4 bit pertama (Prefix/Tipe instruksi)
    uint8_t get_x() const;     // 4 bit kedua (Register X)
    uint8_t get_y() const;     // 4 bit ketiga (Register Y)
    uint8_t get_n() const;     // 4 bit terakhir (Nibble)
    uint8_t get_nn() const;    // 8 bit terakhir (Nilai 1 byte)
    uint16_t get_nnn() const;  // 12 bit terakhir (Address)

    // Method untuk mendeterminasi instruksi apa yang sedang dibaca
    InstructionType decode() const;
    std::string get_mnemonic() const; // Opsional: Untuk debugging, kembalikan nama instruksi sebagai string
};
