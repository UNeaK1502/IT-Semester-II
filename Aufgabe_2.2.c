
/// <summary>
/// Die n-te Fibonacci-Zahl wird rekursiv berechnet.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int fibonacci(int number) {
	if (number == 0) {
		return 0;
	}
	else if (number == 1) {
		return 1;
	}
	else {
		return fibonacci(number - 1) + fibonacci(number - 2);
	}
}