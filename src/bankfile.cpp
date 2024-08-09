// Bank file management
#include <optional>
#include <string>
#include <toml++/toml.h>

#define id unsigned int

enum account_type {
  debit,
  credit,
  savings,
};

enum action_type {
  withdrawal,
  deposit,
  payment,
};

/* Abstract account - Instead of having a vector every time i wanna return data,
 * i can just use this as an template account */
struct abstract_account {
  std::string name;
  account_type account_type;
  int balance;

  abstract_account(std::string name, enum account_type account_type,
                   int balance)
      : name(name), account_type(account_type), balance(balance) {}
};

struct abstract_action {
  std::optional<id> get_id;
  std::optional<id> drain_id;
  int action_amt;
  action_type action_type;

  abstract_action(std::optional<id> get_id, std::optional<id> drain_id,
                  int action_amt, enum action_type action_type)
      : get_id(get_id), drain_id(drain_id), action_amt(action_amt),
        action_type(action_type) {}
};
