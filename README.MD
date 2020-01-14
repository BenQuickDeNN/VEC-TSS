# VEC-TSS: a Tile Size Selection Tool that Aligns Vectorizable Data for GEMM

## Algorithm 1
### Constant Variable Declaration
* V: the width of vector processing unit.
* H: the height of matrix.
* W: the width of matrix.
### Nonconstant Variable Declaration
* res: the result, the best tile size.
* MAX_NUM_VEC: the maximal number of vectorizable data.
* NUM_VEC: the temporal number of vectorizable data.
* w: the efficient width of current row.
* j: the efficient size of current tile.
* n: 
### Workflow
```mermaid
graph TD
    step1(J = V) --> step2{j <= W ?}

    step2 --yes--> step3(J++, NUM_VEC = 0, h = 0)

    step3 --> step4{h < H ?}

    step4 --yes--> step5{h == 0 ?}

    step5 --yes--> step6(j = J, w = W)
    step5 --no--> step7{w % V > 0 ?}

    step7 --yes--> step8(j = J - V + w % V, w = W - V + w % V)
    step7 --no--> step9(j = J, w = W, NUM_VEC *= H / h, h *= H / h)

    step9 --> step10{h >= H}
```