#include "opcode.hpp"

Opcode::Opcode() : instruction(0) {}

Opcode::Opcode(uint16_t inst) : instruction(inst) {}

Opcode::Opcode(uint8_t byte1, uint8_t byte2) {
    set_instruction(byte1, byte2);
}

void Opcode::set_instruction(uint16_t inst) {
    this->instruction = inst;
}

void Opcode::set_instruction(uint8_t byte1, uint8_t byte2) {
    // CHIP-8 menggunakan big-endian, sehingga byte pertama digeser 8 bit ke kiri
    this->instruction = (byte1 << 8) | byte2;
}

uint16_t Opcode::get_instruction() const {
    return this->instruction;
}

uint8_t Opcode::get_type() const {
    return (this->instruction & 0xF000) >> 12;
}

uint8_t Opcode::get_x() const {
    return (this->instruction & 0x0F00) >> 8;
}

uint8_t Opcode::get_y() const {
    return (this->instruction & 0x00F0) >> 4;
}

uint8_t Opcode::get_n() const {
    return this->instruction & 0x000F;
}

uint8_t Opcode::get_nn() const {
    return this->instruction & 0x00FF;
}

uint16_t Opcode::get_nnn() const {
    return this->instruction & 0x0FFF;
}

InstructionType Opcode::decode() const {
    switch (get_type()) {
        case 0x0:
            if (get_nn() == 0xE0) return InstructionType::CLS;
            if (get_nn() == 0xEE) return InstructionType::RET;
            return InstructionType::SYS;
        case 0x1: return InstructionType::JP;
        case 0x2: return InstructionType::CALL;
        case 0x3: return InstructionType::SE_BYTE;
        case 0x4: return InstructionType::SNE_BYTE;
        case 0x5: 
            if (get_n() == 0x0) return InstructionType::SE_REG;
            break;
        case 0x6: return InstructionType::LD_BYTE;
        case 0x7: return InstructionType::ADD_BYTE;
        case 0x8:
            switch (get_n()) {
                case 0x0: return InstructionType::LD_REG;
                case 0x1: return InstructionType::OR_REG;
                case 0x2: return InstructionType::AND_REG;
                case 0x3: return InstructionType::XOR_REG;
                case 0x4: return InstructionType::ADD_REG;
                case 0x5: return InstructionType::SUB_REG;
                case 0x6: return InstructionType::SHR_REG;
                case 0x7: return InstructionType::SUBN_REG;
                case 0xE: return InstructionType::SHL_REG;
            }
            break;
        case 0x9:
            if (get_n() == 0x0) return InstructionType::SNE_REG;
            break;
        case 0xA: return InstructionType::LD_I;
        case 0xB: return InstructionType::JP_V0;
        case 0xC: return InstructionType::RND;
        case 0xD: return InstructionType::DRW;
        case 0xE:
            if (get_nn() == 0x9E) return InstructionType::SKP;
            if (get_nn() == 0xA1) return InstructionType::SKNP;
            break;
        case 0xF:
            switch (get_nn()) {
                case 0x07: return InstructionType::LD_VX_DT;
                case 0x0A: return InstructionType::LD_KEY;
                case 0x15: return InstructionType::LD_DT_VX;
                case 0x18: return InstructionType::LD_ST_VX;
                case 0x1E: return InstructionType::ADD_I_VX;
                case 0x29: return InstructionType::LD_F_VX;
                case 0x33: return InstructionType::LD_B_VX;
                case 0x55: return InstructionType::LD_I_VX;
                case 0x65: return InstructionType::LD_VX_I;
            }
            break;
    }
    return InstructionType::UNKNOWN;
}

std::string Opcode::get_mnemonic() const {
    switch (decode()) {
        case InstructionType::SYS:      return "SYS addr";
        case InstructionType::CLS:      return "CLS";
        case InstructionType::RET:      return "RET";
        case InstructionType::JP:       return "JP addr";
        case InstructionType::CALL:     return "CALL addr";
        case InstructionType::SE_BYTE:  return "SE Vx, byte";
        case InstructionType::SNE_BYTE: return "SNE Vx, byte";
        case InstructionType::SE_REG:   return "SE Vx, Vy";
        case InstructionType::LD_BYTE:  return "LD Vx, byte";
        case InstructionType::ADD_BYTE: return "ADD Vx, byte";
        case InstructionType::LD_REG:   return "LD Vx, Vy";
        case InstructionType::OR_REG:   return "OR Vx, Vy";
        case InstructionType::AND_REG:  return "AND Vx, Vy";
        case InstructionType::XOR_REG:  return "XOR Vx, Vy";
        case InstructionType::ADD_REG:  return "ADD Vx, Vy";
        case InstructionType::SUB_REG:  return "SUB Vx, Vy";
        case InstructionType::SHR_REG:  return "SHR Vx {, Vy}";
        case InstructionType::SUBN_REG: return "SUBN Vx, Vy";
        case InstructionType::SHL_REG:  return "SHL Vx {, Vy}";
        case InstructionType::SNE_REG:  return "SNE Vx, Vy";
        case InstructionType::LD_I:     return "LD I, addr";
        case InstructionType::JP_V0:    return "JP V0, addr";
        case InstructionType::RND:      return "RND Vx, byte";
        case InstructionType::DRW:      return "DRW Vx, Vy, nibble";
        case InstructionType::SKP:      return "SKP Vx";
        case InstructionType::SKNP:     return "SKNP Vx";
        case InstructionType::LD_VX_DT: return "LD Vx, DT";
        case InstructionType::LD_KEY:   return "LD Vx, K";
        case InstructionType::LD_DT_VX: return "LD DT, Vx";
        case InstructionType::LD_ST_VX: return "LD ST, Vx";
        case InstructionType::ADD_I_VX: return "ADD I, Vx";
        case InstructionType::LD_F_VX:  return "LD F, Vx";
        case InstructionType::LD_B_VX:  return "LD B, Vx";
        case InstructionType::LD_I_VX:  return "LD [I], Vx";
        case InstructionType::LD_VX_I:  return "LD Vx, [I]";
        default:                        return "UNKNOWN";
    }
}
