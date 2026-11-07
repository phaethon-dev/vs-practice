#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include "bank.h"
#include "parse.h"

namespace
{

    // Prints a prompt and reads one line. Returns nullopt if input has ended.
    std::optional<std::string> readLine(const std::string &prompt)
    {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line))
        {
            return std::nullopt;
        }
        return line;
    }

    // Asks for an account number. Prints an error and returns nullopt if the input
    // is invalid, ended, or names an account that doesn't exist.
    std::optional<long long> askAccount(Bank &bank, const std::string &prompt)
    {
        auto line = readLine(prompt);
        if (!line)
        {
            return std::nullopt;
        }
        auto number = parseInteger(*line);
        if (!number)
        {
            std::cout << "\"" << *line << "\" is not a valid account number.\n";
            return std::nullopt;
        }
        if (bank.find(*number) == nullptr)
        {
            std::cout << "Account #" << *number << " does not exist.\n";
            return std::nullopt;
        }
        return number;
    }

    std::optional<Money> askMoney(const std::string &prompt)
    {
        auto line = readLine(prompt);
        if (!line)
        {
            return std::nullopt;
        }
        auto amount = parseMoney(*line);
        if (!amount)
        {
            std::cout << "\"" << *line << "\" is not a valid amount.\n";
            return std::nullopt;
        }
        return amount;
    }

    // TODO: askMoney(const std::string &prompt), the same idea for amounts

    void openChecking(Bank &bank, const std::string &prompt)
    {
        auto line = readLine("Owner name: ");
        if (!line)
        {
            return; // input ended
        }
        std::string owner = trim(*line);
        if (owner.empty())
        {
            std::cout << "Owner name cannot be empty.\n";
            return;
        }
        long long number = bank.openChecking(owner);
        std::cout << "Opened checking account #" << number << ".\n";
    }

    void openSaving(Bank &bank, const std::string &prompt, const std::string &prompt2, const std::string &prompt3)
    {
        auto line = readLine(prompt);
        if (!line)
        {
            return;
        }
        std::string owner = trim(*line);
        if (owner.empty())
        {
            std::cout << "Owner name cannot be empty.\n";
            return;
        }
        auto input = readLine(prompt2);
        if (!input)
        {
            return;
        }
        auto interest = parseInteger(*input);
        if (!interest)
        {
            return;
        }
        auto minBalance = askMoney(prompt3);
        if (!minBalance)
        {
            return;
        }
        long long number = bank.openSavings(*owner, *interest, *minBalance);
        std::cout << "Opened savings account #" << number << ".\n";
    }

    void deposit(Bank &bank)
    {
        auto number = askAccount(bank, "Account number: ");
        if (!number)
        {
            return;
        }
        auto amount = askMoney("Amount: ");
        if (!amount)
        {
            return;
        }
        if (bank.deposit(*number, *amount))
        {
            std::cout << "Deposited " << *amount << " into #" << *number
                      << ". New balance: " << bank.find(*number)->balance() << "\n";
        }
        else
        {
            std::cout << "Deposit rejected (amounts must be greater than $0.00).\n";
        }
    }

    void withdraw(Bank &bank)
    {
        auto number = askAccount(bank, "Account number: ");
        if (!number)
        {
            return;
        }
        auto amount = askMoney("Amount: ");
        if (!amount)
        {
            return;
        }
        if (bank.withdraw(*number, *amount))
        {
            std::cout << "Withdrew " << *amount << " from #" << *number
                      << ". New balance: " << bank.find(*number)->balance() << "\n";
        }
        else
        {
            std::cout << "Withdraw rejected (balance would fall below the required minimum).\n";
        }
    }

    void listAccounts(const Bank &bank)
    {
        // Work out how wide the Owner column needs to be
        std::size_t ownerWidth = std::string("Owner").size();
        for (const auto &account : bank.accounts())
        {
            ownerWidth = std::max(ownerWidth, account->owner().size());
        }
        ownerWidth += 2; // a gap before the next column

        std::cout << std::left
                  << std::setw(6) << "#"
                  << std::setw(11) << "Type"
                  << std::setw(ownerWidth) << "Owner"
                  << "Balance\n";

        for (const auto &account : bank.accounts())
        {
            std::cout << std::setw(6) << account->accountNumber()
                      << std::setw(11) << account->typeName()
                      << std::setw(ownerWidth) << account->owner()
                      << account->balance() << "\n";
        }
        std::cout << "Total: " << bank.totalBalance() << "\n";
    }

    void transfer(Bank &bank)
    {
        auto fromAccount = askAccount(bank, "From account number: ");
        if (!fromAccount)
        {
            return;
        }
        auto toAccount = askAccount(bank, "To account number: ");
        if (!toAccount)
        {
            return;
        }
        auto amount = askMoney("Amount: ");
        if (!amount)
        {
            return;
        }
        if (toAccount == fromAccount)
        {
            std::cout << "Cannot transfer to same account\n";
            return;
        }
        if (bank.transfer(*fromAccount, *toAccount, *amount))
        {
            std::cout << "Transferred " << *amount << " from account #" << *fromAccount
                      << " to account #" << *toAccount << "\n";
        }
        else
        {
            std::cout << "Transfer rejected (balance would fall below the required minimum).\n";
        }
    }

    void accountHistory(Bank &bank)
    {
        auto fromAccount = askAccount(bank, "Account number: ");
        if (!fromAccount)
        {
            return;
        }
        auto account = bank.find(*fromAccount);
        const auto &history = account->history();
        if (history.empty())
        {
            std::cout << "No transactions yet\n";
        }
        for (Money c : history)
        {
            std::cout << c << "\n";
        }
    }

    void monthEnd(Bank &bank)
    {
        std::cout << "Interest paid: " << bank.monthEnd();
    }

    void printMenu()
    {
        std::cout << "\n=== Bank ===\n"
                  << "1) Open checking account    5) Transfer\n"
                  << "2) Open savings account     6) List accounts\n"
                  << "3) Deposit                  7) Account history\n"
                  << "4) Withdraw                 8) Month end\n"
                  << "0) Quit\n";
    }

} // namespace

int main()
{
    Bank bank;
    bool loop = true;
    while (loop)
    {
        printMenu();
        auto line = readLine("\nChoice: ");
        if (!line)
        {
            break; // input ended
        }
        auto choice = parseInteger(*line);
        if (!choice)
        {
            std::cout << "Please enter a number from the menu.\n";
            continue;
        }
        switch (*choice)
        {
        case 1:
            openChecking(bank, "Owner: ");
            break;
        case 2:
            openSaving(bank, "Owner: ", "Interest Rate: ", "Minimum Balance: ");
            break;
        case 3:
            deposit(bank);
            break;
        case 4:
            withdraw(bank);
            break;
        case 5:
            transfer(bank);
            break;
        case 6:
            listAccounts(bank);
            break;
        case 7:
            accountHistory(bank);
            break;
        case 8:
            monthEnd(bank);
            break;
        case 0:
            loop = false;
            break;
        default:
            std::cout << "Please enter a number from the menu.\n";
            break;
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}