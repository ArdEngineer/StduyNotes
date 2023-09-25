#include <stdio.h>
#include <math.h>

double findmax(double a, double b, double c) {
    return a >= b ? (a >= c ? a : c) : (b >= c ? b : c);
}

double findmin(double a, double b, double c) {
    return a <= b ? (a >= c ? a : c) : (b >= c ? b : c);
}

int main()
{
    int R, G, B;
    double r, g, b;
    double max, min;
    double H, S, V;

    scanf("%d %d %d", &R, &G, &B);

    r = (double)((R > 0 ? R : 0) / 255.0f);
    g = (double)((G > 0 ? G : 0) / 255.0f);
    b = (double)((B > 0 ? B : 0) / 255.0f);
    max = findmax(r, g, b);
    min = findmin(r, g, b);

    V = max;
    S = max < 1e-9 ? 0.0f : (max - min) / max;

    if (max - min < 1e-9) {
        H = 0.0f;
    }
    else {
        if (max == r) {
            H = 60.0f * (g - b) / (max - min);
        }
        else if (max == g) {
            H = 60.0f * (2.0f + (b - r) / (max - min));
        }
        else if (max == b) {
            H = 60.0f * (4.0f + (r - g) / (max - min));
        }
        if (H < 1e-9) {
            H = H + 360.0f;
        }
    }
    printf("%.4lf,%.4lf%%,%.4lf%%", H, S * 100, V * 100);
    return 0;
}
