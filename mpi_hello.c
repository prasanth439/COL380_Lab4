// #include <mpi.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "mpi_hello.h"

int 
duelCompute(char* partial_text,
            char* patt_str,
            int* witness_function,
            int i,
            int j,
            int partial_text_size)
{
    int k = witness_function[j-i];
    if((j+k>=partial_text_size)||(partial_text[j+k]!=patt_str[k]))
        return i;
    else
        return j;

};

void 
witness_compute(char* pat_str,
                int pat_len,
                int * witness_function,
                const int period)
{
    witness_function[0] = 0;
    for(int i=1;i<period;i++)
    {
        for(int k=0;i+k<pat_len;k++)
            if(pat_str[k]!=pat_str[i+k])
            {
                witness_function[i] = k;
                break;
            }
    }
};
// brute force checking
int 
check_pattern(char* text,
            char* pattern,
            int pos,
            int pattern_length,
            int text_length)
{
    if(pos+pattern_length>text_length)
        return 0;

    for(int i=0;i<pattern_length;i++)
    {
        if(pattern[i]!=text[pos+i])
            return 0;
    }
    return 1;
};

int* 
np_text_analysis(char* text,
                char* pattern,
                int* witness_function,
                int text_length,
                int pattern_length,
                int witness_size
                )
{
    const int block_size = ceil(m/2);
    int num_blocks = n/block_size,block_offset_limit;
    int* potential_pos = (int*)malloc(sizeof(int)*(num_blocks));
    int* match_pos = (int*)malloc(sizeof(int)*(num_blocks+1));
    match_pos[0]=0;
    int i;
    for(int k=0;k<num_blocks;k++)
    {
        i = block_size*k;
        if(k==num_blocks-1)
        {
            block_offset_limit = n;
        }
        else{
            block_offset_limit = (k+1)*block_size;
        }
        for(int j=i+1;j<block_offset_limit;j++)
        {
            i = duelCompute(text,pattern,witness_function,i,j,n,m);
        }
        potential_pos[k] = i;
    }
    for(int i=0;i<num_blocks;i++)
    {
        if(check_pattern(text,pattern,potential_pos[i],m))
        {
            match_pos[0]++;
            match_pos[match_pos[0]] = potential_pos[i];
        }
    }
    free(potential_pos);
    return match_pos;
};

void 
p_text_analysis(char* text_str,
                char* patt_str,
                int text_length,
                int patt_length,
                int period)
{
    int p = period;
    int* witF = (int*)malloc(sizeof(int)*p);
    witness_compute(patt_str,patt_length,witF,p);
    int * pos = np_text_analysis(text_str,patt_str,witF,text_length,patt_length,p);
    // to write it //
};


int main(int argc, char** argv) {
    // Initialize the MPI environment
    // MPI_Init(argc, argv);

    // duelCompute(text,pattern,pi,1,2,t_L,p_L);

    // MPI_Finalize();
    return 0;
};
