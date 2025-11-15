#include <algorithm>
#include <cmath>
#include <vector>
#include <optional>

constexpr double eps = 1e-10;
constexpr int sign(double x) { return x < -eps ? -1 : (x > eps ? 1 : 0); }
constexpr double sqr_diff(double a, double b) { return (a + b) * (a - b); }

struct Point {
    double x = 0, y = 0;
    Point() = default;
    Point(double x, double y) : x(x), y(y){};
    auto len2() const { return x * x + y * y; }
    auto len() const { return std::hypot(x, y); }
    Point operator-() const { return {-x, -y}; }
    Point operator*(double k) const { return {x * k, y * k}; }
    Point operator/(double k) const { return {x / k, y / k}; }
    Point unit() const { return *this / len(); }
    Point normal() const { return {-y, x}; }
    auto angle() const { return std::atan2(y, x); }
};

using Vector = Point;
using Line = std::pair<Point, Point>;
using Segment = Line;
using Circle = std::pair<Point, double>;
using Polygon = std::vector<Point>;
using Triangle = std::tuple<Point, Point, Point>;

Vector operator+(const Vector &a, const Vector &b) { return {a.x + b.x, a.y + b.y}; }
Vector operator-(const Vector &a, const Vector &b) { return {a.x - b.x, a.y - b.y}; }
Vector operator*(double k, const Vector &a) { return {a.x * k, a.y * k}; }
auto operator==(const Point &A, const Point &B) { return sign((A - B).len()) == 0; }
auto dot(const Vector &a, const Vector &b) { return a.x * b.x + a.y * b.y; }
auto det(const Vector &a, const Vector &b) { return a.x * b.y - a.y * b.x; }
auto middle(const Point &A, const Point &B) { return 0.5 * (A + B); }
auto vec(const Line &l) { return l.second - l.first; }
auto len(const Segment &s) { return vec(s).len(); }
auto len2(const Segment &s) { return vec(s).len2(); }
auto angle(const Vector &a, const Vector &b) {
    auto tmp = a.len() * b.len();
    return sign(sqrt(tmp)) == 0 ? 0 : acos(dot(a, b) / tmp);
}
enum class Side : int { left = -1, on = 0, right = 1 };
auto side_of_line(const Point &P, const Line &l) {
    const auto &[A, B] = l;
    return Side(sign(det(P - A, B - A)));
}
auto projection(const Point &P, const Line &l) {
    const auto &[A, B] = l;
    Vector v = B - A;
    return A + dot(v, P - A) * v / v.len2();
}
auto symmetry(const Point &P, const Line &l) { return 2 * projection(P, l) - P; }
auto point_line_distance(const Point &P, const Line &l) {
    const auto &[A, B] = l;
    Vector v1 = B - A, v2 = P - A;
    return std::fabs(det(v1, v2) / v1.len());
}
auto point_on_segment(const Point &P, const Segment &s) {
    const auto &[A, B] = s;
    return side_of_line(P, {A, B}) == Side::on && sign(dot(A - P, B - P)) <= 0;
}
auto point_segment_distance(const Point &P, const Segment &s) {
    const auto &[A, B] = s;
    auto v1 = B - A, v2 = P - A, v3 = P - B;
    if (sign(dot(v1, v2)) < 0) { return v2.len(); }
    if (sign(dot(v1, v3)) > 0) { return v3.len(); }
    return det(v1, v2) / v1.len();
}
auto parallel(const Line &l1, const Line &l2) { return sign(det(vec(l1), vec(l2))) == 0; }
enum class LineLineRelation { parallel, identical, intersecting };
auto line_intersection(const Line &l1, const Line &l2) -> std::pair<LineLineRelation, std::optional<Point>> {
    const auto &[A, B] = l1;
    const auto &[C, D] = l2;
    if (parallel(l1, l2)) {
        if (side_of_line(A, l2) == Side::on) { return {LineLineRelation::identical, std::nullopt}; }
        return {LineLineRelation::parallel, std::nullopt};
    }
    double s1 = det(D - A, C - A);
    double s2 = det(C - B, D - B);
    return {LineLineRelation::intersecting, A + (B - A) * (s1 / (s1 + s2))};
}
auto triangle_area(const Triangle &t) {
    const auto &[A, B, C] = t;
    return det(B - A, C - A) * 0.5;
}