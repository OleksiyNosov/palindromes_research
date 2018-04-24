#define ulli unsigned long long int
#define ld long double

#include <iostream>
#include <math.h>

int array_size = 10000000;

ulli * primes = new ulli[array_size];
ulli * primes_squares = new ulli[array_size];
ulli * palindromes = new ulli[array_size];

// Variables that will be returned
ulli first_prime_multiplier = 0;
ulli second_prime_multiplier = 0;
ulli max_palindrome = 0;

// Variables for task that can be tweaked
int min_primes_boundary = 10000;
int max_primes_boundary = 99999;

int min_primes_boundary_p2 = min_primes_boundary * min_primes_boundary;
int max_primes_boundary_p2 = max_primes_boundary * max_primes_boundary;

// Variables for temporary calculations
int last_prime_index = 1;
int last_palindrome_index = 0;

// Main functions
void execute_task();
void task();

void calculate_primes_to_boundary();
bool check_if_is_prime(ulli boundary_number);
bool is_in_primes(ld number);

void find_max_palindrome();
ulli create_palindrome(ulli number, ulli digits);
ulli calculate_number_of_digits(ulli number);
void find_max_palindrome_in_range_of_digits(ulli digits);
ulli divisible_by(ld number);
bool is_divisible_by_small_primes(ld number);

bool is_palindrome(ulli number);
bool is_not_palindrome(ulli number);
bool is_in_primes_boundaries(ulli number);

void print_result();
void release_memory();

int main(int argc, const char * argv[]) {
    execute_task();

    return 0;
}

void execute_task() {
    clock_t tStart = clock();

    task();

    print_result();

    printf("Time taken: %.3f sec.\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    release_memory();
}

void task() {
    calculate_primes_to_boundary();

    find_max_palindrome();
}

void calculate_primes_to_boundary() {
    primes_squares[0] = (ulli)4;
    primes_squares[1] = (ulli)9;

    primes[0] = (ulli)2;
    primes[1] = (ulli)3;

    check_if_is_prime(max_primes_boundary);

    return;
}

bool check_if_is_prime(ulli boundary_number) {
    if (primes[last_prime_index] == boundary_number) {
        return true;
    } else if (primes[last_prime_index] > boundary_number) {
        return is_in_primes(boundary_number);
    } else {
        for (ld number = primes[last_prime_index] + 2; number <= boundary_number; number += 2) {
            if (is_in_primes(number)) {
                last_prime_index++;
                primes[last_prime_index] = number;
                primes_squares[last_prime_index] = number * number;

                if (primes[last_prime_index] == boundary_number)
                    return true;
            }
        }
        return false;
    }
}

bool is_in_primes(ld number) {
    for (int i = 0; i < last_prime_index; i++) {
        if (number < primes_squares[i])
            return true;

        if (fmod(number, (ld)primes[i]) == 0)
            return false;
    }

    return true;
}

bool is_in_primes_boundaries(ulli number) {
    return (number >= min_primes_boundary && number <= max_primes_boundary);
}

void find_max_palindrome() {
    ulli max_digits = calculate_number_of_digits(max_primes_boundary_p2);
    ulli min_digits = calculate_number_of_digits(min_primes_boundary_p2);

    for (ulli digits = max_digits; digits >= min_digits; digits--) {
        find_max_palindrome_in_range_of_digits(digits);
    }
}

void find_max_palindrome_in_range_of_digits(ulli digits) {
    ulli palindrome = 0;
    ulli divisor = 0;
    ulli second_divisor = 0;

    ulli local_max_primes_boundary = max_primes_boundary * 2;

    for (ulli i = local_max_primes_boundary; i >= min_primes_boundary; i--) {

        palindrome = create_palindrome(i, digits);

        if (palindrome == 0 || is_not_palindrome(palindrome))
            continue;

        divisor = divisible_by(palindrome);

        if (divisor > min_primes_boundary && max_palindrome < palindrome) {
            second_divisor = palindrome / divisor;

            if (check_if_is_prime(divisor) && check_if_is_prime(second_divisor)) {
                if (is_in_primes_boundaries(divisor) && is_in_primes_boundaries(second_divisor)) {
                    max_palindrome = palindrome;
                    first_prime_multiplier = divisor;
                    second_prime_multiplier = second_divisor;

                    return;
                }
            }
        }
    }
}

ulli create_palindrome(ulli number, ulli required_digits) {
    if (calculate_number_of_digits(number) > ((required_digits + 1) / 2))
        return NULL;

    ulli result = number;
    ulli reversed = 0;
    ulli powers = 0;
    ulli digit = 0;

    while (number != 0) {
        digit = fmod(number, 10);
        number /= 10;
        reversed = reversed * 10 + digit;

        powers++;
    }

    if (required_digits % 2 != 0)
        result = (result / 10) * 10;

    return (result * pow(10, required_digits - powers)) + reversed;
}

ulli calculate_number_of_digits(ulli number) {
    ulli digits = 0;

    while (number != 0) {
        number /= 10;

        digits++;
    }

    return digits;
}

ulli divisible_by(ld number) {
    for (int i = 0; i < last_prime_index; i++) {
        if (fmod(number, (ld)primes[i]) == 0)
            return primes[i];
    }

    return NULL;
}

bool is_palindrome(ulli number) {
    ulli original = number;
    ulli reversed = 0;
    ulli digit = 0;

    while (number != 0) {
        digit = fmod(number, 10);
        number /= 10;
        reversed = reversed * 10 + digit;
    }

    return original == reversed;
}

bool is_not_palindrome(ulli number) {
    return ! is_palindrome(number);
}

void print_result() {
    printf("First prime: %llu\n", first_prime_multiplier);
    printf("Second prime: %llu\n", second_prime_multiplier);
    printf("Palindrome: %llu\n", max_palindrome);

    return;
}

void release_memory() {
    delete [] primes;
    delete [] primes_squares;
    delete [] palindromes;
}
