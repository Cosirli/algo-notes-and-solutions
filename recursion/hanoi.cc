#include <iostream>
#include <vector>
#include <numeric>

using ull_t = unsigned long long;

class Hanoi {
private:
    static void hanoi_rec(int n, char from, char to, char aux, ull_t& moves_count) {
        if (n <= 0) return;
        hanoi_rec(n - 1, from, aux, to, moves_count);
        move(n, from, to, moves_count);
        hanoi_rec(n - 1, aux, to, from, moves_count);
    }

    static void moveDisk(std::vector<int>& from, std::vector<int>& to, 
                         char from_peg, char to_peg, ull_t& moves_count) 
    {
        int disk = from.back();
        from.pop_back();
        to.push_back(disk);
        move(disk, from_peg, to_peg, moves_count);
    }

    static void move(int disk, char from_peg, char to_peg, ull_t& moves) {
        ++moves;
        std::cout << "Move disk " << disk 
            << " from " << from_peg << " to " << to_peg << std::endl;
    }

public:
    static void recursive(int n) {
        ull_t moves_count = 0;
        hanoi_rec(n, 'A', 'C', 'B', moves_count);
        std::cout << "Total moves: " << moves_count << std::endl;
    }

    static void nonrec(int n) {
        ull_t total_moves = (n == 0) ? 0 : (1ULL << n) - 1;
        ull_t moves_cnt = 0;
        std::vector<int> peg[3];  // Source, Auxiliary, Destination
        constexpr char pname[3]{'A', 'B', 'C'};  // used for printing

        // Initially, all disks are placed on A
        // for (int i = n; i >= 1; --i) peg[0].push_back(i);
        peg[0].resize(n);
        std::iota(peg[0].rbegin(), peg[0].rend(), 1);

        // index of peg
        int curr_smallest = 0;

        const auto nextPeg = [n](int current) {
            return (n % 2) ? (current + 2) % 3 : (current + 1) % 3;
        };

        // auto nextPeg = [n](int current) -> int {
        //     if (n % 2 != 0) {
        //         // A - C - B - A
        //         if      (current == 0)  return 2;  
        //         else if (current == 2)  return 1;  
        //         else                    return 0; 
        //     } else {
        //         // A - B - C - A
        //         if      (current == 0)  return 1;
        //         else if (current == 1)  return 2;
        //         else                    return 0;
        //     }
        // };

        for (ull_t moves = 1; moves <= total_moves; ++moves) {
            if (moves % 2) {
                const int next = nextPeg(curr_smallest);
                moveDisk(peg[curr_smallest], peg[next], 
                         pname[curr_smallest], pname[next], moves_cnt);
                curr_smallest = next;
                continue;
            }

            constexpr static int other_pegs[3][2]{{1, 2}, {0, 2}, {0, 1}};
            const auto& [p1, p2] = other_pegs[curr_smallest];

            // switch (curr_smallest) {
            //     case 0: p1 = 1; p2 = 2; break;
            //     case 1: p1 = 0; p2 = 2; break;
            //     case 2: p1 = 0; p2 = 1; break;
            // }
            
            if (peg[p1].empty()) {
                moveDisk(peg[p2], peg[p1], pname[p2], pname[p1], moves_cnt);
            } else if (peg[p2].empty()) {
                moveDisk(peg[p1], peg[p2], pname[p1], pname[p2], moves_cnt);
            } else {
                if (peg[p1].back() < peg[p2].back()) {
                    moveDisk(peg[p1], peg[p2], pname[p1], pname[p2], moves_cnt);
                } else {
                    moveDisk(peg[p2], peg[p1], pname[p2], pname[p1], moves_cnt);
                }
            }
        }

        std::cout << "Number of moves: " << moves_cnt << std::endl;
    }
};

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_disks>" << std::endl;
    }

    int n = std::atoi(argv[1]);
    if (n < 0) {
        std::cerr << "Number of disks cannot be negative" << std::endl;
        return 1;
    }
    Hanoi::recursive(n);
    Hanoi::nonrec(n);
    return 0;
}
