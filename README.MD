# VEC-TSS: a Tile Size Selection Method that Aligns Vectorizable Data for GEMM

## Algorithm 1
### Constant Variable Declaration
* V: the width of vector processing unit.
* H: the height of matrix
* W: the width of matrix
### Workflow
```mermaid
graph TD
    step1(J = V) --> step2{j <= W}
    
    step2 --yes--> step3(J++, NUM_VEC = 0, h = 0)
```