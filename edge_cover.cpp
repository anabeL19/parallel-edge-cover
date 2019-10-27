#include <omp.h>
#include "graph.h"
CGraph<char, int>* graph;
void Omp_MCE();

int main(int argc, char* argv[]) 
{

}

void Omp_MCE() {
    double start, finish;
    start = omp_get_wtime();
    #pragma omp parallel for num_threads(thread_count)\ shared(graph->mnodes.size())
    for (int i=0; i< graph->mnodes.size(); i++) {

    } 
    #pragma omp parallel for num_threads(thread_count)
    for (int i=0; i< graph->mnodes.size(); i++) {
        
    } 
    finish = omp_get_wtime();
}