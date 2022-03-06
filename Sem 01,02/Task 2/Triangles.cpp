#include <iostream>

struct point {
	double x;
	double y;
};

struct triangle {
	point pt1;
	point pt2;
	point pt3;
};

point readPoint() {
	double x, y;
	std::cin >> x >> y;
	return{ x,y };
}

void printPoint(const point& pt) {
	std::cout << pt.x << " " << pt.y << std::endl;
}

double getDistance(const point& pt1, const point& pt2) {
	double dx = pt1.x - pt2.x;
	double dy = pt1.y - pt2.y;
	return sqrt(dx * dx + dy * dy);
}

triangle readTriangle(const point& pt1, const point& pt2, const point& pt3) {
	triangle temp;
	temp.pt1 = pt1;
	temp.pt2 = pt2;
	temp.pt3 = pt3;
	return temp;
}

double getArea(const triangle& tr) {
	double a = getDistance(tr.pt1, tr.pt2);
	double b = getDistance(tr.pt1, tr.pt3);
	double c = getDistance(tr.pt2, tr.pt3);
	double half_perimeter = (a + b + c) / 2;
	return sqrt(half_perimeter * (half_perimeter - a) * (half_perimeter - b) * (half_perimeter - c));
}

void readTriangle(triangle& tr) {
	tr.pt1 = readPoint();
	tr.pt2 = readPoint();
	tr.pt3 = readPoint();
}

void printTriangle(const triangle& tr) {

	std::cout << "Triangle sides" << std::endl << "(" << tr.pt1.x << "," << tr.pt1.y << "), "
		<< "(" << tr.pt2.x << "," << tr.pt2.y << "), " << "(" << tr.pt3.x << "," << tr.pt3.y << ")" << std::endl;
}

void swap(int* arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void swap_areas(double* arr, int i, int j) {
	double temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void swap_triangle(triangle* tr, int i, int j) {
	triangle temp = tr[i];
	tr[i] = tr[j];
	tr[j] = temp;
}

void selectionSort(double* areas, triangle* tr, int len) {
	int min_index;
	for (int i = 0; i < len; ++i) {
		min_index = i;
		for (int j = i + 1; j < len; ++j) {
			if (areas[j] < areas[min_index]) {
				min_index = j;
			}
		}
		if (min_index != i) {
			swap_areas(areas, i, min_index);
			swap_triangle(tr, i, min_index);
		}
	}
}

void bubbleSort(double* areas, triangle* tr, int len) {
	bool swapped = true;
	while (swapped) {
		swapped = false;
		for (int i = 1; i < len; ++i) {
			if (areas[i - 1] > areas[i]) {
				swap_areas(areas, i - 1, i);
				swap_triangle(tr, i - 1, i);
				swapped = true;
			}
		}
	}
}

int main() {
	int N;
	std::cin >> N;
	triangle* tr = new triangle[N];
	double* areas = new double[N];
	for (int i = 0; i < N; ++i) {
		readTriangle(tr[i]);
		areas[i] = getArea(tr[i]);
	}
	std::cout << "Before sorting" << std::endl;
	for (int i = 0; i < N; ++i) {
		std::cout << "Triangle " << i << " area " << areas[i] << std::endl;
	}
	//selectionSort(areas, tr, N);
	bubbleSort(areas, tr, N);
	std::cout << "After sorting" << std::endl;
	for (int i = 0; i < N; ++i) {
		std::cout << "Triangle " << i << " area " << areas[i] << std::endl;
	}

	delete[]areas;
	delete[]tr;
	return 0;
}

