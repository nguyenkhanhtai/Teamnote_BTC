#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;
struct Vector2D {
  int64_t x, y;
  Vector2D(int64_t x, int64_t y) : x(x), y(y) {}
  Vector2D() : x(0), y(0) {}
};

struct Parallelogram {
  Vector2D a, b;
  int64_t area() const { return abs(a.x * b.y - a.y * b.x); }
};

int64_t gcd(int64_t a, int64_t b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

// gcd for colinear 2d vectors
Vector2D gcd(const Vector2D a, const Vector2D b) {
  return {gcd(a.x, b.x), gcd(a.y, b.y)};
}

bool colinear(Vector2D a, Vector2D b) {
  return Parallelogram{a, b}.area() == 0;
}

Vector2D operator*(const int64_t scalar, const Vector2D &p) {
  return Vector2D(scalar * p.x, scalar * p.y);
}

Vector2D operator-(const Vector2D &p1, const Vector2D &p2) {
  return Vector2D(p1.x - p2.x, p1.y - p2.y);
}

Parallelogram gcd(Parallelogram p, Vector2D q) {
  if (colinear(p.a, p.b)) {
    p.a = gcd(p.a, p.b);
    p.b = q;
    return p;
  }
  if (colinear(p.a, q)) {
    p.a = gcd(p.a, q);
    return p;
  }
  if (colinear(p.b, q)) {
    p.b = gcd(p.b, q);
    return p;
  }
  // We want to find k and l such that
  // q = k * p.a + l * p.b + remainder
  // The remainder should be inside p
  // q, p.a, p.b are not colinear and 2d vectors as we checked that before
  int64_t denominator = p.a.x * p.b.y - p.a.y * p.b.x;
  int64_t k = (q.x * p.b.y - q.y * p.b.x) / denominator;
  int64_t l = (p.a.x * q.y - p.a.y * q.x) / denominator;
  Vector2D remainder = q - k * p.a - l * p.b;
  Parallelogram new_p = {p.a, remainder};
  if (p.area() <= new_p.area()) {
    throw runtime_error("The parallelogram did not decrease in size. This "
                        "should never happen.");
  }
  return gcd(new_p, p.b);
}

int main() {
  size_t N;
  cin >> N;
  if (N <= 2) {
    cout << -1 << endl;
    return 0;
  }
  vector<Vector2D> portals(N);
  for (size_t i = 0; i < N; i++) {
    cin >> portals[i].x >> portals[i].y;
  }

  for (size_t i = 0; i < portals.size(); i++) {
    portals[i].x -= portals[N - 1].x;
    portals[i].y -= portals[N - 1].y;
  }
  portals.pop_back();

  // Try to form a parallelegram with non-0 area
  Parallelogram p;
  p.a = portals[0];
  for (size_t i = 1; i < portals.size(); i++) {
    swap(portals[1], portals[i]);
    p.b = portals[1];
    if (p.area() != 0) {
      break;
    }
  }
  if (p.area() == 0) {
    // All portals are colinear, so we can use infinitely many colours
    cout << -1 << endl;
    return 0;
  }
  for (size_t i = 2; i < N; i++) {
    // Compute the gcd of all portal
    p = gcd(p, portals[i]);
  }
  // The solution is the area of the gcd parallelogram
  cout << p.area() << endl;
}