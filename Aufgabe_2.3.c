int findMax(int * array, int length) {
	if (length == 0) return 0;
	int largestNumber = 0;
	if (array[0] > largestNumber) {
		largestNumber = array[0];
	}
	int maxOfRest = findMax(array+1, length - 1);
	return largestNumber;
}