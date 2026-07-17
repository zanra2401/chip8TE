#include "./chip8.hpp"


Chip8TE::Chip8TE() {
  graphic.disp_clear();
  memory.clear_stack();
  register_c.clear_registers();
  memory.clear_memory();
  memory.load_font();
}

void Chip8TE::load_program(const char *file_name) {
  program_loader.load_from_file(file_name);
  rom_bytes = program_loader.get_bytes();
  
  // Memuat ROM ke dalam memori
  memory.load_data(rom_bytes, program_loader.get_file_size());
}

void Chip8TE::emulate_cycle() {
  // 1. Fetch
  current_opcode = (memory.get_data_from_memory(pc) << 8) | memory.get_data_from_memory(pc + 1);
  
  // 2. Decode & Execute
  opcode_decoder.set_instruction(current_opcode);
  opcode_handler(current_opcode);
  
  // pc increment is handled within the opcode execution (normally pc += 2 unless Jump/Call)
}

void Chip8TE::opcode_handler(uint16_t opcode) {
  switch (opcode_decoder.decode()) {
    case InstructionType::CLS:
      graphic.disp_clear();
      pc += 2;
      break;
    case InstructionType::RET:
      pc = memory.pop_from_stack();
      pc += 2;
      break;
    case InstructionType::JP:
      pc = opcode_decoder.get_nnn();
      break;
    case InstructionType::CALL:
      memory.push_to_stack(pc);
      pc = opcode_decoder.get_nnn();
      break;
    case InstructionType::LD_BYTE:
      register_c.set_v_register(opcode_decoder.get_x(), opcode_decoder.get_nn());
      pc += 2;
      break;
    case InstructionType::ADD_BYTE: {
      uint8_t vx = register_c.get_v_register(opcode_decoder.get_x());
      register_c.set_v_register(opcode_decoder.get_x(), vx + opcode_decoder.get_nn());
      pc += 2;
      break;
    }
    case InstructionType::LD_I:
      register_c.set_i_register(opcode_decoder.get_nnn());
      pc += 2;
      break;
    case InstructionType::DRW: {
      uint8_t x = register_c.get_v_register(opcode_decoder.get_x());
      uint8_t y = register_c.get_v_register(opcode_decoder.get_y());
      uint8_t height = opcode_decoder.get_n();
      uint8_t* sprite = memory.get_memory_ptr(register_c.get_i_register());
      
      bool collision = graphic.draw_sprite(x, y, sprite, height);
      register_c.set_v_register(0xF, collision ? 1 : 0);
      
      graphic.render(); // Render layar setelah menggambar sprite
      pc += 2;
      break;
    }
    default:
      pc += 2;
      break;
  }
}
