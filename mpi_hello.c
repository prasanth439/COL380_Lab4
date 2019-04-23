#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <malloc.h>
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
                int witness_size)
{
    const int block_size = ceil(pattern_length/2.0);
    int num_blocks = text_length/block_size;
    int block_offset_limit;
    int* potential_pos = (int*)malloc(sizeof(int)*(num_blocks));
    int* match_pos = (int*)malloc(sizeof(int)*(num_blocks+1));
    match_pos[0]=0;
    int i;
    for(int k=0;k<num_blocks;k++)
    {
        i = block_size*k;
        if(k==num_blocks-1)
        {
            block_offset_limit = text_length;
        }
        else{
            block_offset_limit = (k+1)*block_size;
        }
        for(int j=i+1;j<block_offset_limit;j++)
        {
            i = duelCompute(text,pattern,witness_function,i,j,text_length);
        }
        potential_pos[k] = i;
    }
    for(int i=0;i<num_blocks;i++)
    {
        if(check_pattern(text,pattern,potential_pos[i],pattern_length,text_length))
        {
            match_pos[0]++;
            match_pos[match_pos[0]] = potential_pos[i];
        }
    }
    free(potential_pos);
    return match_pos;
};

int* 
p_text_analysis(char* text_str,
                char* patt_str,
                int text_length,
                int patt_length,
                int period)
{
    int p = period;
    int* witness_function = (int*)malloc(sizeof(int)*p);
    witness_compute(patt_str,patt_length,witness_function,p);
    int * pos = np_text_analysis(text_str,patt_str,witness_function,text_length,patt_length,p);
    int k = (int)floor(patt_length/(double)p);
    int* M = (int*)calloc(text_length,sizeof(int));
    int dim_x=ceil(text_length/(double)p),dim_y=p;
    int size_u_v =(patt_length-(k-2)*p);
    int* MATCH = (int*)calloc((text_length-patt_length),sizeof(int));

    for(int i=1;i<=pos[0];i++)
    {
        // check the u2v at i
        M[pos[i]] = 1;
        for(int j=2*p-1;j<size_u_v;j++)
        {
            if(text_str[pos[i]+j]!=patt_str[j])
            {
                M[pos[i]] = 0;
                break;
            }
        }
    }
    for(int i =0;i<p;i++)
    {
        int count = 0;
        for(int j=0;j<dim_x;j++)
        {
            if(count==k-1)
            {
                MATCH[i+(j-k)*p] = 1;
            }
            count+= (-1*M[i+p*(j-k)]+M[i+p*j]);
        }
    }
    return MATCH;
};


int main(int argc, char** argv) {
    // Initialize the MPI environment
    int world_size,world_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    FILE* fp = fopen("testing.txt","r");
    int a;
    int b;
    fscanf(fp,"%d %d",&a,&b);
    printf("(Size:%d) (Rank:%d) (Read1:%d) (Read2:%d)\n",world_size,world_rank,a,b);
    
    // duelCompute(text,pattern,pi,1,2,t_L,p_L);
    MPI_Finalize();
    // return 0;
};
