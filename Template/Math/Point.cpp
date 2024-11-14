#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Point {
public:
    T x, y;
    Point() : x(0), y(0) {
    }
    Point(T x, T y) : x(x), y(y) {
    }
    static Point rotate(const Point& p, T angle) {  // 逆时针旋转
        return Point(p.x * cos(angle) - p.y * sin(angle), p.x * sin(angle) + p.y * cos(angle));
    }
    static T cross(
        const Point& a, const Point& b,
        const Point& c) {  // 直线a->b和直线a->c叉积：大于0则c在a->b的左侧，小于0则c在a->b的右侧，等于0则c在a->b上
                           // || 平行四边形面积
        return (b - a) * (c - a);
    }
    static T dot(
        const Point& a, const Point& b,
        const Point&
            c) {  // 直线a->b和直线a->c点积：大于0则c在a->b的逆时针方向，小于0则c在a->b的顺时针方向，等于0则c在a->b上
                  // || 直线投影
        return (b - a) ^ (c - a);
    }
    static T dis(const Point& a, const Point& b) {  // 两点距离
        return hypot(a.x - b.x, a.y - b.y);
    }
    static bool intersect(const Point& a, const Point& b, const Point& c, const Point& d) {  // 线段ab和线段cd是否有交点
        return cross(a, b, c) * cross(a, b, d) <= 0 &&
               cross(c, d, a) * cross(c, d, b) <= 0;  // 条件1：直线ab与线段cd有交点，条件2：直线cd与线段ab有交点
    }
    static Point crossPoint(const Point& a, const Point& b, const Point& c, const Point& d) {  // 直线ab和cd的交点
        T t = (a - c) * d / (b * d);
        return a + c * t;
    }
    static pair<T, vector<Point>> Andrew(const vector<Point>& points) {  // 返回凸包的周长，构成凸包的点
        vector<Point> _points = points;
        int n = _points.size();
        sort(_points.begin(), _points.end());
        deque<Point> q;
        for (int i = 0; i < n; i++) {  // 求下凸包
            while (q.size() >= 2 && cross(q[q.size() - 2], q[q.size() - 1], points[i]) <= 0) q.pop_back();
            q.push_back(_points[i]);
        }
        int t = q.size();
        for (int i = n - 2; i >= 0; i--) {  // 求上凸包
            while (q.size() >= t + 1 && cross(q[q.size() - 2], q[q.size() - 1], points[i]) <= 0) q.pop_back();
            q.push_back(_points[i]);
        }
        T res = 0;
        for (int i = 1; i < q.size(); i++) res += dis(q[i], q[i - 1]);
        vector<Point> ans;
        for (int i = 0; i < q.size() - 1; i++) ans.push_back(q[i]);  // touhewei
        return {res, ans};
    }
    static T rotating_calipers(const vector<Point>& points) {  // 旋转卡壳：求凸包直径(传入凸包上的点)
        int n = points.size();
        T res = 0;
        for (int i = 0, j = 1; i < n; i++) {
            while (cross(points[i], points[(i + 1) % n], points[j]) <
                   cross(points[i], points[(i + 1) % n], points[(j + 1) % n]))
                j = (j + 1) % n;
            res = max(res, max(dis(points[i], points[j]), dis(points[(i + 1) % n], points[j])));
        }
        return res;
    }
    inline Point operator*(T k) const {  // 乘以一个常数
        return Point(this->x * k, this->y * k);
    }
    inline T operator*(const Point& other) const {  // 叉积  a x b = |a|*|b|*sin(a,b)
        return this->x * other.y - this->y * other.x;
    }
    inline T operator^(const Point& other) const {  // 点积  a . b = |a|*|b|*cos(a,b)
        return this->x * other.x + this->y * other.y;
    }
    inline Point operator-(const Point& other) const {  // 减
        return Point(this->x - other.x, this->y - other.y);
    }
    inline Point operator+(const Point& other) const {  // 加
        return Point(this->x + other.x, this->y + other.y);
    }
    inline Point& operator+=(const Point& other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }
    inline Point& operator-=(const Point& other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }
    inline bool operator==(const Point& other) const {
        return this->x == other.x && this->y == other.y;
    }
    inline bool operator<(const Point& other) const {
        return this->x == other.x ? this->y < other.y : this->x < other.x;
    }
};