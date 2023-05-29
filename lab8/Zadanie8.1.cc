#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int main() {
    int numPoints = 10000000;  
    int pointsInsideCircle = 0;  
    int pointsInsideSquare = 0;  
    
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    #pragma omp parallel for reduction(+:pointsInsideCircle, pointsInsideSquare)
    for (int i = 0; i < numPoints; i++) {
        
        double x = static_cast<double>(std::rand()) / RAND_MAX;
        double y = static_cast<double>(std::rand()) / RAND_MAX;

        double r = x * x + y * y;

        pointsInsideSquare++;

        if (r <= 1) {
            pointsInsideCircle++;
        }
    }

    double pi = 4.0 * static_cast<double>(pointsInsideCircle) / static_cast<double>(pointsInsideSquare);

    std::cout << "Przyblizona wartosc liczby PI: " << pi << std::endl;

    return 0;
}
