#include <vector>
#include <cmath>
#include <algorithm>
#include <memory>

namespace ogxx {
    typedef double Float;

    template<class T>
    class St_matrix {
    public:
        virtual T get_value(int i, int j) const = 0;
        virtual int size() const = 0;
    };

    class Metric_compute {
    public:
        virtual Float compute(const std::vector<Float>& p1, const std::vector<Float>& p2) const = 0;
    };

    class Hamming_distance : public Metric_compute {
    public:
        Float compute(const std::vector<Float>& p1, const std::vector<Float>& p2) const override {
            int mismatch_count = 0;
            for (int i = 0; i < p1.size(); i++) {
                if (p1[i] != p2[i]) {
                    mismatch_count++;
                }
            }
            return static_cast<Float>(mismatch_count);
        }
    };

    class Manhattan_distance : public Metric_compute {
    public:
        Float compute(const std::vector<Float>& p1, const std::vector<Float>& p2) const override {
            Float distance = 0;
            for (int i = 0; i < p1.size(); i++) {
                distance += std::abs(p1[i] - p2[i]);
            }
            return distance;
        }
    };

    class Euclidean_distance : public Metric_compute {
    public:
        Float compute(const std::vector<Float>& p1, const std::vector<Float>& p2) const override {
            Float distance = 0;
            for (int i = 0; i < p1.size(); i++) {
                distance += std::pow(p1[i] - p2[i], 2);
            }
            return std::sqrt(distance);
        }
    };

    class Chebyshev_distance : public Metric_compute {
    public:
        Float compute(const std::vector<Float>& p1, const std::vector<Float>& p2) const override {
            Float distance = 0;
            for (int i = 0; i < p1.size(); i++) {
                distance = std::max(distance, std::abs(p1[i] - p2[i]));
            }
            return distance;
        }
    };

    class French_railway_distance : public Metric_compute {
    public:
        Float compute(const std::vector<Float>& p1, const std::vector<Float>& p2) const override {
            Float distance1 = Euclidean_distance().compute({0, 0, 0}, p1);
            Float distance2 = Euclidean_distance().compute({0, 0, 0}, p2);
            return distance1 + distance2;
        }
    };

    class Point_distance_matrix: public St_matrix<Float> {
    public:
        Point_distance_matrix(const std::vector<std::vector<Float>>& points)
            : points(points), metric(nullptr) {}

        void set_points(const std::vector<std::vector<Float>>& new_points) {
            points = new_points;
        }

        void set_metric(std::unique_ptr<Metric_compute> new_metric) {
            metric = std::move(new_metric);
        }

        Float get_value(int i, int j) const override {
            if (metric) {
                return metric->compute(points[i], points[j]);
            }

            throw std::invalid_argument("Invalid metric");
        }

        int size() const override {
            return points.size();
        }

    private:
        std::vector<std::vector<Float>> points;
        std::unique_ptr<Metric_compute> metric;
    };
}
