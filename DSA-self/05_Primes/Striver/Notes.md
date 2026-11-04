Striver - All about Primes:
---------------------------
ref: https://www.youtube.com/playlist?list=PLN4aKSfpk8TQDJz7KLiwGFgnoUUwzfl1i

Facts about primes:
- Two is the only even prime
- Every prime can be written as 6n + 1 or 6n - 1 except 2 and 3, where n is a natural number
- Goldbach Conjecture - Every even integer greater than 2 can be expressed as the sum of two primes
- Wilson's Theorem - A natural number n > 1 is a prime if and only if (n-1)! ≡ (n - 1) mod n
- 2 and 3 are the only consecutive primes

6d +- 1 rule: By the process of elimination, 6k, 6k + 2, 6k + 3, and 6k + 4 are all composite numbers. So, the only possible candidates for primes are of the form 6k + 1 and 6k - 1.
Catch: 6k + 1 and 6k - 1 are not guaranteed to be prime. For example, 25 = 6*4 + 1 is not prime. So, we need to check if the number is prime or not.

Wilson's theorem:
eg. n = 5 => LHS = (n-1)! = 4! = 24, RHS = (n-1) mod n = 4 mod 5 = 4. LHS ≡ RHS.

Prime: 
- A prime number is a natural number greater than 1 that has exactly two distinct positive factors: 1 and itself.
- In short, if there are only two factors of a number, then it is prime.
```
// O(n)
boolean checkPrime_basic(int n) { 
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            cnt++;
        }
    }
    return cnt == 2;
}
```

Observation: Factors start repeating after sqrt(n). 
eg. 36
1 * 36 = 36
2 * 18 = 36
3 * 12 = 36
4 * 9 = 36
6 * 6 = 36
9 * 4 = 36
12 * 3 = 36
18 * 2 = 36
36 * 1 = 36

So, if you check for factors from 1 to sqrt(n), you can find all factors of n.
```
// O(sqrt(n))
// Most effective way to check if a number is prime
boolean checkPrime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
```

Note: for(int i=2; i<sqrt(n); i++) will yield O(sqrt(n) * log(n)) time complexity because sqrt(n) is calculated in every iteration. So, it is better to use i*i <= n instead of i < sqrt(n).

Q1: Sum of all factors of a number n
Soln:

```
// O(sqrt(n))
int sumFactors(int n) {
    int sum = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i; // i is a factor
            if (i != n / i) { // IMP. - Avoid counting the same factor twice for perfect squares
                sum += n / i; // n/i is also a factor
            }
        }
    }
    return sum;
}
```

PTR: 1sec time limit on coding platforms signifies max. 10^8 operations. So, some code of complexity 10^9 would take 10sec.

Q2: Given a number n, find 3 numbers a,b and c such that a*b*c = n and a != b != c != 1. Constraint: 1 < n < 10^9.
Soln: Since it talks about factors, we can think about finding factors in O(sqrt(n)) complexity.
Start finding and assigning smallest factor to a. Ensure b is the next smallest factor. This will ensure c is the largest factor.

```
void findFactors(int n) {
    int a = -1, b = -1, c = -1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            a = i; // smallest factor
            break;
        }
    }
    if (a == -1) return -1; // no factors found, n is prime

    for (int i = a + 1; i * i <= n; i++) {
        if (n % i == 0) {
            b = i; // next smallest factor
            break;
        }
    }
    if (b == -1) return -1; // no second factor found

    c = n / (a * b); // largest factor
    if (c > 1 && c != a && c != b)
        System.out.println(a + " " + b + " " + c);
}
```
The above code has flaws. 1. Integer overflow at i * i <=n. 2. a * b can overflow, so use n / a / b.

```
void findFactors(int n) {
    int a = -1, b = -1, c = -1;
    int remaining = n;

    for (int i = 2; i <= remaining / i; i++) {
        if (remaining % i == 0) {
            a = i;
            remaining /= i;
            break;
        }
    }

    if (a == -1) return;

    for (int i = a + 1; i <= remaining / i; i++) {
        if (remaining % i == 0) {
            b = i;
            remaining /= i;
            break;
        }
    }

    if (b == -1) return;

    c = remaining;

    if (c > 1 && c != a && c != b) {
        System.out.println(a + " " + b + " " + c);
    }
}
```

---------------------------------------------------------------------------------------------------------------------------------------

Sieve of Eratosthenes

Question: Given T test cases, for each number in the test case, print Yes/No if that number is a prime or not.
Constraints: 1 < T < 10^6, 1 < n < 10^6.
Soln: Using above approach will yield O(T * sqrt(n)) ~= O(10^9) time complexity since we'd be running isPrime logic for each test case. 
=> 10sec => TLE. To avoid it we can use Sieve of Eratosthenes.

Sieve of Eratosthenes: It's an efficient algorithm used to find all prime numbers up to a given number n.
1. Take an array isPrime of size n+1 and initialize all entries as true.
2. Starting from 2 till n, mark all multiples of the number as false (not prime).
3. Perform (2) only if the number is still marked as true (prime).

```
void sieveOfEratosthenes(int n) {
    boolean[] isPrime = new boolean[n + 1];
    Arrays.fill(isPrime, true);
    isPrime[0] = isPrime[1] = false; // (OPTIONAL if n > 1)

    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            for (int j = 2*i; j <= n; j += i) {
                // 2*2, 2*3, 2*4, 2*5...are marked as false
                // 3*2, 3*3, 3*4, 3*5...are marked as false
                // 5*2, 5*3, 5*4, 5*5...are marked as false
                isPrime[j] = false;
            }
        }
    }
}
```
Time complexity: O(n * log(log(n)))
Reason: 
1. initialization: O(n)
2. Iterating over n: O(n)
3. Inner loop over primes: O(n/2 + n/3 + n/5 + n/7 + ... + n/p) where p is the largest prime <= n. This is a harmonic sum of primes.
=> n/2 + n/3 + n/5 + n/7 + ... + n/p = n * (1/2 + 1/3 + 1/5 + 1/7 + ... + 1/p) = O(n * log(log(sqrt(n)))))

Total: O(n) + O(n) + O(n * log(log(sqrt(n)))) = O(n * log(log(n)))

Note: If you observe above, 
1. there's repetition in marking multiple of prime. Why will 5 have to start from 5*2 when the prev. primes have already marked its multiples?
2. say n = 25, then why should there be an attempt to iterate on 7, 11, 13 i.e. (j = i*i; j<25; j+=i) => 49 < 25, 121 < 25, 169 < 25

```
void sieveOfEratosthenes(int n) {
    boolean[] isPrime = new boolean[n + 1];
    Arrays.fill(isPrime, true);
    isPrime[0] = isPrime[1] = false; // (OPTIONAL if n > 1)

    for (int i = 2; i * i <= n; i++) { // runs till sqrt(n)
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    // Time complexity: O(n) + O(sqrt(n)) + O(n * log(log(sqrt(n)))) = O(n * log(log(n)))
}
```

So, the earlier problem of T test cases can be solved in O(T) + O(n * log(log(n))) ~= O(10^6) which is >> O(T * sqrt(n)) ~= O(10^9).

PTR: Generally, make max. size array (in java) as follows:
For heap memory (-Xmx) 256 MB:
- int[]: 3*10^7
- long[]: 1.5*10^7
- boolean: 10^8 
For heap memory (-Xmx) 512 MB:
- int[]: 8*10^7
- long[]: 4*10^7
- boolean[] / byte[]: 3*10^8 = 300MB

---------------------------------------------------------------------------------------------------------------------------------------

Q3: Find Kth prime number. Given Q queries, for each query print the Kth prime number. Constraints: 1 < Q < 5 * 10^4, 1 < K < 5 * 10^6.
Soln: We can use sieve and collect all primes in an array. But how do we know N i.e. the limit till which we need to run sieve?
1. Figure that limit N.
2. Run sieve till N and collect all primes in an array.
```
void sieveOfEratosthenes() {
    int n = 100_000_000; // 10^8
    boolean[] isPrime = new boolean[n + 1];
    Arrays.fill(isPrime, true);
    isPrime[0] = isPrime[1] = false; // (OPTIONAL if n > 1)

    for(int i=2; i*i<=n; i++) {
        if(isPrime[i]) {
            for(int j=i*i; j<=n; j+=i) {
                isPrime[j] = false;
            }
        }
    }

    int MAX_K = 5 * 10e6;
    int cnt = 0;
    for(int i=2; i<=n; i++) {
        if(isPrime[i]) {
            cnt++;
            if(cnt == MAX_K) {
                System.out.println(i); // Once you have this in console, write the final program based on this value of n
                break;
            }
        }
    }
}
```

```
void createSieve(ArrayList<Integer> primes) {
    int n = 86028121;
    boolean isPrime[] = new boolean[n + 1];
    Arrays.fill(isPrime, true);
    isPrime[0] = isPrime[1] = false; // (OPTIONAL if n > 1)

    for(int i=2; i*i<=n; i++) {
        if(isPrime[i]) {
            for(int j=i*i; j<=n; j+=i) {
                isPrime[j] = false;
            }
        }
    }

    for(int i=2; i<=n; i++) {
        if(isPrime[i]) {
            primes.add(i);
        }
    }
}
void findKthPrime(int[] queries) {
    ArrayList<Integer> primes = new ArrayList<>();
    createSieve(primes); // O(n * log(log(n))) + O(n) ~= O(10^7)

    for(int k: queries) {
        System.out.println(primes.get(k-1));
    }
}
```

Q4: Given Q queries, for each query n, print the count of numbers in range [1, 10^6] which have n as minimum prime factor. Constraints: 1 < Q < 10^6, 1 < n < 10^6. N is always a prime number.
Soln: We can use sieve to keep a count of multiples a prime marks. Hence, that'll help us answer the queries in O(1) time. So, overall complexity will be O(n * log(log(n))) + O(Q) ~= O(10^6).

```
int[] createSieve() {
    int n = 1_000_000;
    int[] primeCount = new int[n + 1];
    Arrays.fill(primeCount, 1);
    primeCount[0] = primeCount[1] = 0; // (OPTIONAL if query > 1)

    for(int i=2; i*i<=n; i++) {
        if(primeCount[i] == 1) {
            for(int j=i*i; j<=n; j+=i) {
                if(primeCount[j] != 0) {
                    primeCount[i]++;
                    primeCount[j] = 0; // mark it zero since it isn't prime and so that no other prime can count it as its multiple
                }
            }
        }
    }
    return primeCount;
}
void countNumbersWithMinPrimeFactor(int T) {
    int[] primeCount = createSieve(); // O(n * log(log(n)))

    for(int i=0; i<T; i++) {
        int q = sc.nextInt();
        System.out.println(primeCount[q]);
    }
}
```

Query problems with factors, primes -> think of sieve

---------------------------------------------------------------------------------------------------------------------------------------

Printing Prime Factorisation

Def: Prime factorization is the process of breaking down a composite number into a product of its constituent prime numbers
eg. 12 = 2 * 2 * 3
2 | 12
--|---
2 | 6
--|---
3 | 3
--|---
  | 1

```
void printPrimeFactors_basic(int n) {
    for(int i=2; i<=n; i++) {
        while(n % i == 0) {
            System.out.print(i + " ");
            n /= i;
        }
    }
}
```
Time complexity: O(n) - worst case when n is prime.

Recall: For a number, the factors can be found in O(sqrt(n)).

```
void printPrimeFactors_optimized(int n) {
    for(int i=2; i*i<=n; i++) {
        while(n % i == 0) {
            System.out.print(i + " ");
            n /= i;
        }
    }
    // This ensures that if n is a prime number greater than 1, it will be printed as well.
    if(n > 1) {
        System.out.print(n + " ");
    }
    // Dry run on 13, 100 and 35 - covers all cases - prime, composite, perfect square, product of 2 primes.
}
```
Time complexity: O(sqrt(n)) - worst case when n is a perfect square of a prime number.

Issue: if T < 10^6 and n < 10^6, then O(T * sqrt(n)) ~= O(10^9) which is too high. 

Fact: Max. number of prime factors of a number n is log(n) base 2.
Reason: To maximize the number of prime factors, we need to use the smallest possible prime factor (2) repeatedly.
In general, if a number has k prime factors, then:
    n >= 2 * 2 * 2...k times = 2^k. eg. 8 = 2*2*2, 12=2*2*3, 30=2*3*5
Taking log base 2 on both sides:
    log(n) >= k
=> k <= log(n) base 2

To optimise above prime factorization code, we can use sieve to precompute the smallest prime factor for each number in range [1, 10^6].
Then, we can use the same technique above to find prime factors, it's just that the prime factor to divide with will not run from 2 to n, but according to sieve table. This would result in O(log(n)) time complexity since the max. number of prime factors of a number n is log(n) base 2.

```
int[] createSieve() {
    // smallest prime factor sieve
    int n = 10e6;
    int[] spfSieve = new int[n+1];
    for(int i=1; i<=n; i++) {
        spfSieve[i] = i; // smallest prime factor of a number is itself (for now)
    }

    for(int i=2; i*i<=n; i++) {
        if(spfSieve[i] == i) { // i is prime
            for(int j=i*i; j<=n; j+=i) {
                if(spfSieve[j] == j) { // j hasn't been marked yet
                    spfSieve[j] = i; // mark the smallest prime factor of j as i
                }
            }
        }
    }
    return spfSieve;
}

void printPrimeFactors(int n, int[] spfSieve) {
    // O(log(n)) - since the max. number of prime factors of a number n is log(n) base 2
    while(n > 1) {
        System.out.print(spfSieve[n] + " ");
        n /= spfSieve[n];
    }
    System.out.println();
}

void solve(int T) {
    int[] spfSieve = createSieve(); // O(n * log(log(n)))

    for(int i=0; i<T; i++) {
        int n = sc.nextInt();
        printPrimeFactors(n, spfSieve);
    }
}
```

This reduces the time complexity from O(T * sqrt(n)) to O(n * log(log(n))) + O(T * log(n)) ~= O(10^6) + O(10^6 * log(10^6)) ~= O(10^7) which is acceptable.

---------------------------------------------------------------------------------------------------------------------------------------

Segmented Sieve
Question: Given T test cases, for each test case print all prime numbers in range [L, R]. 
Constraints: 1 < T < 10, 1 < L < R < 10^12, R - L < 10^6.
Soln: We can't have an array of size 10^12. Was it possible, then we'd just iterate from L to R and check if each number is prime or not.

Segmented Sieve technique:
1. Find all primes up to sqrt(R) using the Sieve of Eratosthenes - O(sqrt(R)) = O(10^6)
- We only find the ones which actually mark a mulitples - so just from 2 to sqrt(R), not beyond that.
2. Create a boolean array of size R - L + 1 and initialize all entries as true. Assume first entry as L...uptil last entry as R.
3. Pick every prime in step 1. and start marking its multiple in range [L, R] created in step 2.
- Sieve starts multiple from i*i, so start from i*i minimum. But if i*i < L, then start from the first multiple of that prime in range [L, R].

```
boolean[] createSieve(int n) {
    int n = 1_000_000; // 10^6
    boolean[] isPrime = new boolean[n + 1];
    Arrays.fill(isPrime, true);
    isPrime[0] = isPrime[1] = false; // (OPTIONAL if n > 1)

    for(int i=2; i*i<=n; i++) {
        if(isPrime[i]) {
            for(int j=i*i; j<=n; j+=i) {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}
void solve(int T) {
    boolean[] isPrime = createSieve(); // O(n * log(log(n))) ~= O(10^6)

    for(int i=0; i<T; i++) {
        int L = sc.nextInt();
        int R = sc.nextInt();

        // Step 1: Find all primes up to sqrt(R)
        ArrayList<Integer> primes = new ArrayList<>();
        for(int j=2; j*j<=R; j++) {
            if(isPrime[j]) {
                primes.add(j);
            }
        }

        // Step 2: Create a boolean array of size R - L + 1 and initialize all entries as true.
        boolean[] segmentedSieve = new boolean[R - L + 1];
        Arrays.fill(segmentedSieve, true);

        // Step 3: Pick every prime in step 1. and start marking its multiple in range [L, R] created in step 2.
        for(int prime: primes) {
            int firstMultiple = (L / prime) * prime;
            if (firstMultiple < L)
                firstMultiple += prime;
            
            int start = Math.max(firstMultiple, prime*prime); eg. L=110, R=130, prime=11 => start=121

            for(int j=start; j<=R; j+=prime) {
                segmentedSieve[j - L] = false;
            }
        }

        // Step 4: Print all prime numbers in range [L, R]
        for(int j=L; j<=R; j++) {
            if(segmentedSieve[j - L]) {
                System.out.print(j + " ");
            }
        }
        System.out.println();
    }
}
```
Time complexity calculation:
- Sieve creation - O(n * log(log(n))) where n = 10^6 => ~= O(10^6)
- Step 1: O(sqrt(R)) = O(10^6)
- Step 2: O(R - L) = O(10^6)
- Step 3: For every prime you're running (R - p^2)/p ~= R/p. This is same as harmonic sum of primes.
    => Time complexity = number of primes + work by each prime = O(10^6) + R * log(log(R)) ~= O(10^6)
- Step 4: O(R - L) = O(10^6)

Time complexity = O(10^6)

