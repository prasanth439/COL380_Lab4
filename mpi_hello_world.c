// #include <mpi.h>
#include <stdio.h>
#include <malloc.h>
#include <omp.h>
#include <math.h>
void witnessCompute(char* pattern_string,int length,int * witFn,int PIy)
{
    witFn[0] = 0;
    for(int i=1;i<PIy;i++)
    {
        for(int k=0;i+k<length;k++)
            if(pattern_string[k]!=pattern_string[i+k])
            {
                witFn[i] = k+1;
                break;
            }
    }
};
int check_pattern(char* text,int pos,char* pattern,int pattern_length)
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

    for(int i=0;i<n/ceil(m/2);i++)
    {
        i = ceil(m/2)*i;
        for(int j=i+1 ;j<;j++)
        {
            i = duelCompute(text,pattern,phIp,i,j,n,m);
        }
        potential_pos[i] = il;
    }
    match_pos = {};
    for(int i=0;i<potential_pos.size();i++)
    {
        if(check_pattern(text,pattern,potential_pos[i],m))
        {
            match_pos.push_back(potential_pos[i]);
        }
    }
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
    witnessCompute(pattern,p_L,pi,2);
    for(int i=0;i<2;i++)
    {
        printf("%d\n",pi[i]);
    }
    // duelCompute(text,pattern,pi,1,2,t_L,p_L);

    // Finalize the MPI environment.
    // MPI_Finalize();
}