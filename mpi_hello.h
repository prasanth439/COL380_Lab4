#ifndef MPI_HELLO_H
#define MPI_HELLO_H

int 
duelCompute(char* partial_text,
            char* patt_str,
            int* witness_function,
            int i,
            int j,
            int partial_text_size);

void 
witness_compute(char* pat_str,
                int pat_len,
                int * witness_function,
                const int period);

int 
check_pattern(char* text,
            char* pattern,
            int pos,
            int pattern_length,
            int text_length);

int* 
np_text_analysis(char* text,
                char* pattern,
                int* witness_function,
                int text_length,
                int pattern_length,
                int witness_size);

void 
p_text_analysis(char* text_str,
                char* patt_str,
                int text_length,
                int patt_length,
                int period);

#endif