#include "SHA256.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    std::string filename;
    uint32_t tickets;
    int64_t salt;

    if (argc != 1 + 6) {
        std::cerr << "USAGE: hw7 --filename <filename> --tickets <number of tickets> --salt <int64_t nuber>";
        return 1;
    }

    for (size_t i = 1; i != static_cast<size_t>(argc); ++i) {
        if (std::string(argv[i]) == "--filename") {
            filename = std::string(argv[i + 1]);
            ++i;
        } else if (std::string(argv[i]) == "--tickets") {
            tickets = std::atoi(argv[i + 1]);
            ++i;
        } else if (std::string(argv[i]) == "--salt") {
            salt = std::atoll(argv[i + 1]);
            ++i;
        }
    }

    freopen(filename.c_str(), "r", stdin);

    std::vector<std::pair<std::string, uint32_t>> personWithTicket;
    std::vector<uint32_t> personAmountByTicket(tickets + 1, 0);

    std::string name;
    while (getline(std::cin, name)) {
        std::string joined;
        for (const char& ch : name) {
            if (ch != ' ') {
                joined += ch;
            }
        }

        SHA256 sha256;
        sha256.update(joined + std::to_string(salt));
        std::string hash = SHA256::toString(sha256.digest());

        uint64_t ticket = 0;
        for (const char& ch : hash) {
            ticket *= 16;
            ticket += ('0' <= ch && ch <= '9' ? static_cast<uint64_t>(ch - '0') : 10 + static_cast<uint64_t>(ch - 'a'));
            ticket %= tickets;
        }

        personWithTicket.emplace_back(name, ticket + 1);
        ++personAmountByTicket[ticket + 1];
    }

    for (auto const& [person, ticket] : personWithTicket) {
        std::cout << person << ' ' << ticket << '\n';
    }

    std::cout << "\n\nTickets distribution:\n";
    for (size_t i = 1; i != personAmountByTicket.size(); ++i) {
        std::cout << "Ticket # " << i << "   " << personAmountByTicket[i] << '\n';
    }

}
