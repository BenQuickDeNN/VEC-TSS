# VEC-TSS: a Tile Size Selection Tool that Aligns Vectorizable Data for GEMM

## Algorithm 1: Periodically Iteration
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
* n: the tile ID of current row.
### Code
```C++
int getBestTileFactor(const int& V, const int& H, const int& W)
{
    /* tile factor */
    int res = -1;

    /* number of vectorizable data units */
    int MAX_NUM_VEC = 0;
    int NUM_VEC = 0;

    /* do a tile size J traverse from V to W */
    int w;
    int j;
    int n;
    for (int J = V; J <= W; J++)
    {
        NUM_VEC = 0;
        for (int h = 0; h < H; h++)
        {
            if (h == 0)
            {
                j = J;
                w = W;
            }
            else
            {
                if (w % V > 0)
                {
                    j = J - (V - (w % V));
                    w = W - (V - (w % V));
                }
                else
                {
                    j = J;
                    w = W;
					/* because the data layout is periodic, the following NUM_VEC will be the same */
					/* thus simply multiply H / h NUM_VECs */
                    NUM_VEC *= (H / h);
                    h *= (H / h);
                    if (h >= H)
                        break;
                }
            }
            for (n = 0; n * J < w - (w % V); n++)
            {
                NUM_VEC += (j / V) * V;
                if (j % V > 0)
                    j = J - (V - (j % V));
                else
                    j = J;
            }
        }
        if (NUM_VEC > MAX_NUM_VEC)
        {
            MAX_NUM_VEC = NUM_VEC;
            res = J;
        }
    }
    std::printf("MAX_NUM_VEC = %d, ", MAX_NUM_VEC);
    return res;
}
```
## Algorithm 2: Formula Method (to Be Compeleted)
### Constant Variable Declaration
* V: the width of vector processing unit.
* H: the height of matrix.
* W: the width of matrix.
### Nonconstant Variable Declaration
* T: the number of rows in a period.
### Code
T:
```C++
if (W % V == 0)
    T = 1;
else
    if (V % (W % V) == 0)
        T = V / (W % V);
    else
        T = V;
```