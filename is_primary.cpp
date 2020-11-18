#include <iostream>
#include <climits>
#include <vector>
#include <cmath>
#include <bitset>
#include <cstring>

bool is_prime_eratosthenes(bool* not_prime, size_t num, size_t limit)
{
    if(not_prime[num]) return false;

    for(size_t j = num; j*num < limit; ++j)
    {
        not_prime[num*j] = true;
    }

    return true;
}

bool is_prime_heuristic(size_t n)
{
    if (n == 2) return true;
    if (!(n % 2)) return false;
    for(size_t i = 3; i <= sqrt(n); i+=2)
    {
        if (!(n%i)) {
            return false;
        }
    }
    return true;
}

bool is_prime_by_primes(std::vector<int>& primes, size_t n)
{
    for(int num : primes) {
        if(!(n%num)) return false;
    }

    return true;
}

bool is_not_prime(std::vector<int64_t>& n_primes, int64_t num)
{
    int64_t idx = num/32;
    if (num > 31) {
        num -= 32 * (num/32);
    }
 
    return n_primes[idx] & (1 << num);
}

void set_n_byte(std::vector<int64_t>& n_primes, int64_t num)
{
    int64_t idx = num/32;
    if (num > 31) {
        num -= 32 * (num/32);
    }
    
    //std::cout << idx << std::endl;
    n_primes[idx] |= (1 << num);
}

int prime_count_optimization(int64_t n)
{
    int count = 1;
    std::vector<int64_t> nums(n); // n/32 + 1

    for(int64_t i = 3; i < n; i+=2)
    {
        if (!is_not_prime(nums, i)) {
            ++count;
            for(int64_t j = i; j*i < n; j+=2)
            {
                set_n_byte(nums, j*i);
            }
        }
    }

    return count;    
}

int main(int argc, char **argv)
{
    std::string func_type = argv[1];
    size_t n = atoi(argv[2]);

    if (n <= 2) {
        int result = 0;
        if (n == 2) {
            result = 1;
        } 

        std::cout << result << std::endl;
        return 1;
    }
    if (func_type == "prime_heuristic") {

        int count = 1;
        for(size_t i = 3; i < n; i+=2)
        {
            if (is_prime_heuristic(i)) {
                count++;
            }
        }
        std::cout << count << std::endl;

    } else if (func_type == "prime_del_primes") {

        std::vector<int> nums = {2,3};
        for(size_t i = 5; i < n; i+=2)
        {
            if (is_prime_by_primes(nums, i)) {
                nums.push_back(i);
            }
        }
        std::cout << nums.size() << std::endl;

    } else if (func_type == "eratosthenes") {
        bool* not_prime = new bool[INT_MAX];

        int count = 0;
        for(size_t i = 2; i < n; i++)
        {
            if (is_prime_eratosthenes(not_prime, i, n)) ++count;
        }
        delete[] not_prime;

        std::cout<< count << std::endl;
    } else if (func_type == "eratosthenes_op") {

         std::cout << prime_count_optimization(n) << std::endl;
    
    }  else {
        std::cout << "UNKNOWN FUNC TYPE" << std::endl;
    }

}