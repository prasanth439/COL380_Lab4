// #include <mpi.h>
#include <stdio.h>
#include <malloc.h>
#include <omp.h>
#include <math.h>

void witness_compute(char* pat_str,int pat_len,int * witness_function,const int piY)
{
    witness_function[0] = 0;
    for(int i=1;i<piY;i++)
    {
        for(int k=0;i+k<pat_len;k++)
            if(pat_str[k]!=pat_str[i+k])
            {
                witness_function[i] = k;
                break;
            }
    }
};
int check_pattern(char* text,char* pattern,int pos,int pattern_length)
{
    for(int i=0;i<pattern_length;i++)
    {
        if(pattern[i]!=text[pos+i])
            return 0;
    }
    return 1;
};
void np_text_analysis(char* text,char* pattern,int* phIp,int n,int m,int p)
{
    int* match_pos;
    const int block_size = ceil(m/2);
    int num_blocks = n/block_size,block_offset_limit;
    int* potential_pos = (int*)malloc(sizeof(int)*num_blocks);
    for(int k=0;k<num_blocks;k++)
    {
        i = ceil(m/2)*k;
        if(k==limit-1)
        {
            block_offset_limit = n;
        }
        else{
            block_offset_limit = (k+1)*block_size
        }
        for(int j=i+1;j<block_offset_limit;j++)
        {
            i = duelCompute(text,pattern,phIp,i,j,n,m);
        }
        potential_pos[k] = i;
    }
    match_pos = {};
    for(int i=0;i<potential_pos.size();i++)
    {
        if(check_pattern(text,pattern,potential_pos[i],m))
        {
            match_pos.push_back(potential_pos[i]);
        }
    }
    free potential_pos;
    // return match_pos;
}
void p_text_analysis()
{

}

int duelCompute(char* Z,char* Y,int* phI,int i,int j,int n,int m)
{
    int k = phI[j-i];
    if((j+k>=n)||(Z[j+k]!=Y[k]))
        return i;
    else
        return j;

};
int main(int argc, char** argv) {
    // Initialize the MPI environment
    // MPI_Init(argc, argv);
    char* text = "babababababaabab";
    char* pattern = "abababa";
    int t_L= 16,p_L = 7;
    int PiI = 2;
    int* pi = (int*)malloc(sizeof(int)*2);
    witness_compute(pattern,p_L,pi,2);
    for(int i=0;i<2;i++)
    {
        printf("%d\n",pi[i]);
    }
    // duelCompute(text,pattern,pi,1,2,t_L,p_L);

    // MPI_Finalize();
    return 0;
};
