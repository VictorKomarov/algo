#include <iostream>
#include <functional>
#include <string>
#include <bitset>
#include <vector>

using bits = std::bitset<64>;
using board = std::vector<bits>;

struct Figure {
    bits init, zero;

    Figure(uint64_t init_)
    {
        init[init_] = 1;
        zero.reset();
    }
};

struct King : Figure{
    bits r_masked, u_masked;
    bits b_masked, l_masked;
 
    King(uint64_t init_) : Figure(init_)
    {
        l_masked.set(), r_masked.set();
        for(int count = 0; count < 8; ++count)
        {
            l_masked[count*8] = 0;
            r_masked[count*8+7] = 0;
        }
        l_masked &= init;
        r_masked &= init;
    };

    uint64_t mask()
    {
        auto mask = (l_masked << 7) | (init << 8) | (r_masked << 9)|
                    (l_masked >> 1) |    zero     | (r_masked << 1)|
                    (l_masked >> 9) | (init >> 8) | (r_masked >> 7);
        return mask.to_ullong();
    }
};

struct Horse : Figure{
    bits double_l, l, double_b;
    bits double_r, r, double_u;
 
    Horse(uint64_t init_) : Figure(init_)
    {
        double_l.set(), l.set(), double_b.set();
        double_r.set(), r.set(), double_u.set();
        for(int count = 0; count < 8; ++count)
        {
            l[count*8] = 0;
            double_l[count*8] = 0, double_l[count*8+1] = 0;
            double_b[count] = 0, double_b[count+8] = 0;
            r[count*8 + 7] = 0;
            double_r[count*8 + 7] = 0, double_r[count*8+6] = 0;
            double_u[count + 56] = 0, double_u[count+48] = 0;
        }
        double_r &= init, double_u &= init, r &= init;
        double_l &= init, double_b &= init, l &= init;
    };

    uint64_t mask()
    {
        auto mask = (double_l << 6) | (double_r << 10) | ((double_u & l) << 15) | ((double_u & r) << 17)|
                    (double_r >> 6) | (double_l >> 10) | ((double_b & r) >> 15) | ((double_b & l)  >> 17);
        return mask.to_ullong();
    }
};

struct Rook {
    int start;
    bits left, right;
    Rook(uint64_t init) : start(init)
    {
        auto line = start / 8;
        auto left_begin = line * 8;
        auto right_end = line * 8 + 7;

        for(int i = start-1; i >= left_begin; --i)
        {
            left[i] = 1;
        }

        for(int i = start+1; i <= right_end; ++i)
        {
            right[i] = 1;
        }
    }

    uint64_t mask()
    {
        bits mask;
        for(uint64_t i = 1; i < 8; ++i)
        {
            bits up, down;
            up[start + i*8] = 1, down[start - i*8] = 1;

            mask |= up | down;
        }

        mask |= left | right;
        return mask.to_ullong();
    }
};

struct Elephant {
    bits up_steps, down_steps;
    
    Elephant(uint64_t init)
    {
        auto line = init / 8;
        for(int i = line - 1, j = 1; i >= 0; --i, ++j)
        {
            auto c_pos = init - (8*j);
            auto begin = i*8;
            auto end = begin + 7;
            if(c_pos - j >= begin && c_pos - j <= end) {
                down_steps[c_pos-j] = 1;
            }

            if (c_pos + j <= end && c_pos + j >= begin) {
                down_steps[c_pos+j] = 1;
            }
        }

        for(int i = line + 1, j = 1; i < 8; ++i, ++j)
        {
            auto c_pos = init + (8 * j);
            auto begin = i*8;
            auto end = begin + 7;
            if(c_pos - j >= begin && c_pos - j <= end) {
                up_steps[c_pos-j] = 1;
            }

            if (c_pos + j <= end && c_pos + j >= begin) {
                up_steps[c_pos+j] = 1;
            }
        }
    }

    uint64_t mask()
    {
        return (up_steps | down_steps).to_ullong();
    }
};

struct Queen {
    bits mask_;
    Queen(uint64_t init)
    {
        mask_.set();
        mask_[init]=0;
    }

    uint64_t mask()
    {
        return mask_.to_ullong();
    }
};


int count_step(uint64_t mask)
{
    int count = 0;
    while (mask > 0)
    {
        if (mask & 1) ++count;
        mask >>= 1;
    }
    return count;
}


void Do(const std::string& fig, uint64_t init)
{
    uint64_t mask = 0;
    if(fig == "king") {
        mask = King(init).mask();
    } else if (fig == "horse") {
        mask = Horse(init).mask();
    } else if (fig == "rook") {
        mask = Rook(init).mask();
    } else if (fig == "elephant") {
        mask = Elephant(init).mask();
    } else if (fig == "queen") {
        mask = Queen(init).mask();
    }
        
    std::cout << count_step(mask) << std::endl << mask << std::endl;
}

int main(int argc, char **argv)
{
    uint64_t n = atoi(argv[1]);
    std::string str = argv[2];

    Do(str, n);
}