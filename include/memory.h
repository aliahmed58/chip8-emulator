#pragma once

extern short *memory;

// method to init memory with needed data in the start
void init_memory();

// method to add bytes to memory from start_index to end_index
int nbytes_tm(int start_index, int end_index, int b_size, short *bytes);
