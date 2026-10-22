/*===============================
--- Problema de Fibbonaci ---
Implementar as versões:

- recursiva

- memoization

- tabulation
===============================*/

// 1. Recursiva
int recursiva(int n) {
    if(n <= 1) 
        return n;
    else 
        return recursiva(n - 1) + recursiva(n - 2);
}

// 2. Top-Down
int top(int n, int memo[]) {
    if(n <= 1) 
        return n;
        
    if(memo[n] != -1) 
        return memo[n];
        
    memo[n] = top(n - 1, memo) + top(n - 2, memo);
    return memo[n];
}

// 3. Bottom-Up
int bottom(int n) {
    if (n <= 1) 
        return n;
    
    int f[n + 1];
    f[0] = 0;
    f[1] = 1;
    
    for(int i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    return f[n];
}

int main() {
    int n = 10; 
    
    printf("=== Testando Fibonacci para n = %d ===\n\n", n);

    // 1. Versão Recursiva Simples
    printf("1. Recursiva: %d\n", recursiva(n));

    // 2. Versão Memoization (Top-Down)
    int memo[n + 1];
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }
    printf("2. Memoization: %d\n", top(n, memo));

    // 3. Versão Tabulation (Bottom-Up)
    printf("3. Tabulation: %d\n", bottom(n));

    return 0;
}