#include <cstdio>

/**
 * @brief compute the best tile factor to fully utilize vectorization
 * @param V vector width
 * @param H array height
 * @param W array width
 * @return best tile factor
 */
int getBestTileFactor(const int& V, const int& H, const int& W);

/**
 * @brief a fast method to compute the best tile factor
 * @param V vector width
 * @param H array height
 * @param W array width
 * @return best tile factor
 */
int fastGetBestTileFactor(const int& V, const int& H, const int& W);

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
					/* thus simple multiply H / h NUM_VECs */
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
        std::printf("J = %d, NUM_VEC = %d\r\n", J, NUM_VEC);
        if (NUM_VEC > MAX_NUM_VEC)
        {
            MAX_NUM_VEC = NUM_VEC;
            res = J;
        }
    }
    std::printf("MAX_NUM_VEC = %d, ", MAX_NUM_VEC);
    return res;
}