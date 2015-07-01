#ifndef VM_H
#define VM_H
#include <inttypes.h>
#include <sys/time.h>

unsigned long millis() {
  struct timeval tv; 
  gettimeofday (&tv, NULL); 
  return (tv.tv_sec*1000 + tv.tv_usec/1000);
}

/*
  add
  sub
  mul
  div
  cp
  cpi
  load
  save
  
 */

enum idk_instruction_type {
  idk_t_add = 0,
  idk_t_sub = 1,
  idk_t_mul = 2,
  idk_t_div = 3,
  idk_t_cp = 4,
  idk_t_cpi = 5,
  idk_t_nor = 6,
  idk_t_nand = 7,
  idk_t_load = 8,
  idk_t_save = 9,
  idk_t_sys = 10
};

typedef int16_t idk_word;
typedef uint16_t idk_instruction;
typedef uint8_t idk_register;

idk_word idk_ram[2000];

idk_instruction idk_program[20000];

typedef struct {
  idk_instruction* thread_pc;
  unsigned long sleep;
} idk_thread;

#define IDK_THREAD_COUNT (5)
idk_thread idk_threads[IDK_THREAD_COUNT];

const idk_instruction idk_instruction_type_bits   = 0b1111000000000000;
const idk_instruction idk_instruction_reg_a_bits  = 0b0000111110000000;
const idk_instruction idk_instruction_reg_b_bits  = 0b0000000001111100;
const idk_instruction idk_instruction_offset_bits = 0b0000000000000011;

void idk_i_clear_type(idk_instruction* inst) {
  *inst |= (~idk_instruction_type_bits);
}

void idk_i_set_type(idk_instruction* inst, enum idk_instruction_type type) {
  idk_i_clear_type(inst);
  *inst |= ((idk_instruction) type) << 12;
}

/**
 * Get the actual instruction from i
 */
enum idk_instruction_type idk_i_get_type(idk_instruction i) {
  return i & idk_instruction_type_bits;
}

/**
 * Get the register A number
 */
idk_register idk_i_get_reg_a(idk_instruction i) {
  return i & idk_instruction_reg_a_bits;
}

/**
 * Get the register B number
 */
idk_register idk_i_get_reg_b(idk_instruction i) {
  return i & idk_instruction_reg_b_bits;
}

/**
 * idk time tracker
 */
unsigned long idk_running_millis;

/**
 * Initialize idk vm
 */
void idk_init() {
  idk_running_millis = millis();
}

void idk_perform_instructions(idk_thread thread, int max_instructions) {
  idk_instruction* position = thread.thread_pc;
  for (int i = 0; i < max_instructions; i++) {
    switch (idk_i_get_type(*position)) {
    case idk_t_add: {
      
      break;
    }
    case idk_t_sub: {
      break;
    }
    case idk_t_mul: {
      break;
    }
    case idk_t_div: {
      break;
    }
    case idk_t_cp: {
      break;
    }
    case idk_t_cpi: {
      break;
    }
    case idk_t_nor: {
      break;
    }
    case idk_t_nand: {
      break;
    }
    case idk_t_load: {
      break;
    }
    case idk_t_save: {
      break;
    }
    case idk_t_sys: {
      break;
    }
    }
  }
}

/**
 * idk un loop
 */
void idk_run_program () {

  unsigned long last_running_millis = idk_running_millis;

  idk_running_millis = millis();

  unsigned long elapsed_millis = idk_running_millis - last_running_millis;

  for (int thread_index = 0; thread_index < IDK_THREAD_COUNT; thread_index++) {
    idk_thread thread = idk_threads[thread_index];
    if (thread.sleep > 0) {
      thread.sleep = (elapsed_millis > thread.sleep) ? 0 : thread.sleep - elapsed_millis;
    }
    if (!thread.sleep) {
      idk_perform_instructions(thread, 100);
    }
  }
}




#endif
