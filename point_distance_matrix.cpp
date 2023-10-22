#include <vector>
#include <cmath>
#include <algorithm>

namespace ogxx {
    typedef double Float;

    template<class T>
    class St_matrix {
    public:
        virtual T get_value(int i, int j) const = 0;
        virtual int size() const = 0;
    };

    class Point_distance_matrix: public St_matrix<Float> {
    public:
        Point_distance_matrix(const std::vector<std::vector<Float>>& points)
            : points(points), metric(0) {}

        void set_points(const std::vector<std::vector<Float>>& new_points) {
            points = new_points;
        }

        void set_metric(int new_metric) {
            metric = new_metric;
        }

        Float get_value(int i, int j) const override {
            if (metric == 0) {
                return hamming_distance(points[i], points[j]);
            } else if (metric == 1) {
                return manhattan_distance(points[i], points[j]);
            } else if (metric == 2) {
                return euclidean_distance(points[i], points[j]);
            } else if (metric == 3) {
                return chebyshev_distance(points[i], points[j]);
            } else if (metric == 4) {
                return french_railway_distance(points[i], points[j]);
            }

            throw std::invalid_argument("Invalid metric");
        }

        int size() const override {
            return points.size();
        }

    private:
        std::vector<std::vector<Float>> points;
        int metric;

        Float hamming_distance(const std::vector<Float>& p1, const std::vector<Float>& p2) const {
            int mismatch_count = 0;
            for (int i = 0; i < p1.size(); i++) {
                if (p1[i] != p2[i]) {
                    mismatch_count++;
                }
            }
            return static_cast<Float>(mismatch_count);
        }

        Float manhattan_distance(const std::vector<Float>& p1, const std::vector<Float>& p2) const {
            Float distance = 0;
            for (int i = 0; i < p1.size(); i++) {
                distance += std::abs(p1[i] - p2[i]);
            }
            return distance;
        }

        Float euclidean_distance(const std::vector<Float>& p1, const std::vector<Float>& p2) const {
            Float distance = 0;
            for (int i = 0; i < p1.size(); i++) {
                distance += std::pow(p1[i] - p2[i], 2);
            }
            return std::sqrt(distance);
        }

        Float chebyshev_distance(const std::vector<Float>& p1, const std::vector<Float>& p2) const {
            Float distance = 0;
            for (int i = 0; i < p1.size(); i++) {
                distance = std::max(distance, std::abs(p1[i] - p2[i]));
            }
            return distance;
        }

        Float french_railway_distance(const std::vector<Float>& p1, const std::vector<Float>& p2) const {
            Float distance1 = euclidean_distance({0, 0, 0}, p1);
            Float distance2 = euclidean_distance({0, 0, 0}, p2);
            return distance1 + distance2;
        }
    };
}
