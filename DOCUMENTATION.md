
Function-by-Function Analysis
basic_operations.c

float add(float a, float b) → returns a + b

float subtract(float a, float b) → returns a - b

float multiply(float a, float b) → returns a * b

float divide(float a, float b) → checks if b != 0, then returns a / b, else error

operations.c

float power(float base, int exp) → returns base^exp

float squareRoot(float num) → uses sqrt() to return √num

matrix_operations.c

void addMatrix() → takes two matrices from user, adds them

void multiplyMatrix() → takes two matrices, multiplies them

history.c

void saveHistory(const char *operation, float result) → writes operation/result to history.csv

void displayHistory() → reads and prints previous operations

utils.c

void clearScreen() → clears terminal screen

void pauseScreen() → waits for user to press a key

float getValidNumber() → takes numeric input safely
