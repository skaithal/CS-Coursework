/* Created by Sanjana Aithal, Student ID: 917496419 */

#include <math.h>
#include <string.h>

#include <iostream>
#include <stack>

#include "multiset.h"

/* findFactors >> method to find the prime factors, and create a bst */
void findFactors(int n, Multiset<int> &prime) {
  /* find the factors that are 2 */
  while (n % 2 == 0) {
    prime.Insert(2);
    n = n / 2;
  }

  /* now n is odd, takes care of the composite numbers */
  for (int i = 3; i <= sqrt(n); i = i + 2) {
    while (n % i == 0) {
      prime.Insert(i);
      n = n / i;
    }
  }

  /* once composite numbers have been inserted, addresses the prime numbers */
  if (n > 2) prime.Insert(n);

  /* if the number's only factor is itself, there are no prime factors */
  if (prime.Size() <= 1) {
    std::cerr << "No prime factors" << std::endl;
  }
}

/* all >> a method to output all the number's prime factors */
void all(Multiset<int> &prime) {
  /* only bother printing if the number has more factors than itself */
  if (prime.Size() > 1) {
    /* print minimum */
    std::cout << prime.Min() << " (x" << prime.Count(prime.Min()) << "), ";

    /* int n traverses through the bst, using the ceil method to find the next
     * highest key value */
    int n = prime.Min() + 1;
    while (n <= prime.Max()) {
      std::cout << prime.Ceil(n) << " (x" << prime.Count(prime.Ceil(n))
                << "), ";
      n = prime.Ceil(n) + 1;
    }
    std::cout << std::endl;
  }
}

/* min >> a method to ouput a number's lowest factor */
void min(Multiset<int> &prime) {
  /* uses multiset implementation to find the min */
  std::cout << prime.Min() << " (x" << prime.Count(prime.Min()) << ")";
}

/* max >> a method to ouput a number's greatest factor */
void max(Multiset<int> &prime) {
  /* uses multiset implementation to find the max */
  std::cout << prime.Max() << " (x" << prime.Count(prime.Max()) << ")"
            << std::endl;
}

/* floor >> a method to output the number's floor, contained in the bst */
void floor(Multiset<int> &prime, int n) {
  /* count will be used to safely remove the identical values */
  int count = 0;

  /* if the number is a negative value, make it positive */
  if (n < 0) n = n * -1;

  /* if n exists in the bst, remove it to find the true floor */
  if (prime.Contains(n)) {
    count = prime.Count(n);
    while (count) {
      prime.Remove(n);
      count--;
    }
  }

  /* if n is greater than the minimum print the floor value --> there is no
   * match  */
  if (n > prime.Min())
    std::cout << prime.Floor(n) << " (x" << prime.Count(prime.Floor(n)) << ")"
              << std::endl;
  else
    std::cout << "No match" << std::endl;
}

/* contains >> a method to determine if a given factor exists in the bst */
void contains(Multiset<int> &prime, int n) {
  /* if the bst contains n, print it --> otherwise, no match */
  if (prime.Contains(n))
    std::cout << n << " (x" << prime.Count(n) << ")" << std::endl;
  else
    std::cout << "No match" << std::endl;
}

/* ceil >> a method to output a number's floor, contained in the bst
 * --same implementation as the floor method -- */
void ceil(Multiset<int> &prime, int n) {
  int count = 0;

  if (n < 0) n = n * -1;

  if (prime.Contains(n)) {
    count = prime.Count(n);
    while (count) {
      prime.Remove(n);
      count--;
    }
  }

  if (n < prime.Max())
    std::cout << prime.Ceil(n) << " (x" << prime.Count(prime.Ceil(n)) << ")";
  else
    std::cout << "No match" << std::endl;
}

int main(int argc, char *argv[]) {
  /* Create the object */
  Multiset<int> m;

  /* Handling the command line
   * If the command line has 3 arguments ... */
  if (argc == 3) {
    /* Check that the number contains only digits --> is a valid number
     * if so, find the factors --> otherwise, return error */
    std::string str = argv[1];

    if (std::all_of(str.begin(), str.end(), ::isdigit))
      findFactors(atoi(argv[1]), m);
    else {
      std::cerr << "Invalid number" << std::endl;
      return 1;
    }

    /* Check that the next argument is a valid command...
     * if yes, execute function --> if not, return error */
    std::string s = argv[2];
    if (s.compare("all") == 0)
      all(m);
    else if (s.compare("min") == 0) {
      min(m);
      std::cout << std::endl;
    } else if (s.compare("max") == 0)
      max(m);
    else if (s.compare("near") == 0) {
      std::cerr << "Command 'near' expects another argument: [+/-]prime"
                << std::endl;
      return 1;
    } else {
      std::cerr << "Command '" << argv[2] << "' is invalid" << std::endl;
      std::cerr << "Possible commands are: all|min|max|near" << std::endl;
      return 1;
    }

  } else if (argc == 4) {
    /* If the commandline has 4 arguments...
     * Check that the number contains only digits --> is a valid number
     * if so, find the factors --> otherwise, return error */
    std::string str = argv[1];
    if (std::all_of(str.begin(), str.end(), ::isdigit))
      findFactors(atoi(argv[1]), m);
    else {
      std::cerr << "Invalid number" << std::endl;
      return 1;
    }

    /* Check that the next argument corresponds to a valid command
     * if so, execute function --> otherwise return error */
    std::string s = argv[3];
    if (s[0] == '+') {
      ceil(m, stoi(s));
    } else if (s[0] == '-')
      floor(m, stoi(s));
    else if (std::all_of(s.begin(), s.end(), ::isdigit))
      contains(m, stoi(s));
    else {
      std::cerr << "Invalid prime" << std::endl;
      return 1;
    }
  } else /* if the correct number of commands are not inputted, output usage
            error */
    std::cerr << "Usage: " << argv[0] << " <number> <command> [<args>]"
              << std::endl;

  return 0;
}