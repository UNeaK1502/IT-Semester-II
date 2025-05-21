//Quicksort
void quicksort(int* arr, int low, int high)
{
    int pivot, i, j, temp;
    if (low < high) {
        pivot = low; // Pivot auswhälen - random wäre hier besser
        i = low;
        j = high;
        while (i < j) {
            // I erhöhen bis ein Wert auftritt, der größer dem Pivot ist
            while (arr[i] <= arr[pivot] && i <= high) {
                i++;
            }
            // J verringern, bis ein Wert auftritt, der kleiner als der Pivot ist
            while (arr[j] > arr[pivot] && j >= low) {
                j--;
            }
			if (i < j) {        //Kleinen Wert mit großen Wert tauschen
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
		//Wenn i>= j, dann ist der Pivot an der richtigen Stelle
        temp = arr[j];
        arr[j] = arr[pivot];
        arr[pivot] = temp;
		// Wiederholen mit dem linken und rechten Teil des Arrays, gesehen vom Pivot
        quicksort(arr, low, j - 1);
        quicksort(arr, j + 1, high);
    }
}