#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    int n;
    std::cin >> n; // n*2
    std::vector<int> tickets((n*9/2)+1);

    for(size_t i = 0; i < pow(10, n); ++i)
    {
        size_t num = i, sum = 0;
        while(num > 0)
        {   
            sum += (num % 10);
            num /= 10;
        }
        if (sum >= tickets.size()) continue;
        ++tickets[sum];
    }

    long long count = 0;
    for(size_t i = 0; i < tickets.size(); ++i) {
        auto test = static_cast<long long>(tickets[i]);
        if(n%2 == 0 && i == tickets.size()-1) {
            count += (test*test);
            continue;
        }

        count += (test*test*2);
    }
    std::cout << count << std::endl;
}