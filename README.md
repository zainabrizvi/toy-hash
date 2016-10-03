# toy-hash
A simple C application exploring password authentication

## 1 OLMHash Password Scheme

* The result of OLMHash should be an updatable table of two columns
- the user id and the hash of the corresponding user’s password. You
may store the table in a text file.
 * Upon launch, OLMHash should prompt for an user id
  
  * If the user id is not found in the table, the program asks the user to
enter a new password. The hash of the password is then computed
and added to the table alongside the user id.

  * If the user id already exists in the table, the user is prompted for
his old password. The hash of the entered password is computed
and compared to the hash of the user’s old password stored in the table. If the hashes match, the user is prompted for a new
password. The hash of the new password then replaces that of the old password.

  * The defend against brute-force type attacks, many password systems
limit the number of ’wrong’ attempts for a given user. Define
a user-defined security parameter n in your code, which represents
the number of unsuccessful attempts. In the execution of your
program, once this limit is reached, the program should output
the message “Too many unsuccessful attempts - your account is
locked”. However, you should ensure that the counter that you
use is reset to zero, once you exit the program, i. e. if you re-run
your program, up to n attempts are again allowed for any user
ids.

* User id’s must be at least 4 characters, but less than 32 characters long.

* Passwords must include upper and lower case letters and numbers only,
i.e. no special characters.

* Passwords can contain a maximum of 12 characters. If the chosen
passwords are longer than 12, any extra characters after the 12th are
ignored. If the chosen passwords are less than 12 characters, they will
be padded with null characters (\0) to make it exactly 12 characters.

* The hashing algorithm first converts all the lower case letters to their
upper case equivalent. This will give us 36 possible ‘true’ characters to
pick from.

* The 12 characters of the chosen password are then split into three 4-
character blocks, B0B1B2. We will use the ASCII representation of
each character, i.e. each block Bi contains 32 bits.

* Encryption algorithms (such as DES or AES) could be used to produce
the hash of a given password. BUT, here, we will instead use an encryption
function, E() which takes 32 bits as input and produces 32
bits as output. To produce the hash, we take each block of 4 characters
Bi and compute hi = E(Bi). The hash of the password is simply the
concatenation of h1, h2, and h3, i.e. h = h1h2h3. The C code for the
function, E(), is provided to you below:


