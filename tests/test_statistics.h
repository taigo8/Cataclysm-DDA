#ifndef TEST_STATISTICS_H
#define TEST_STATISTICS_H

#include <limits>
#include <vector>

class statistics
{
    private:
        int _types;
        int _n;
        int _sum;
        int _max;
        int _min;
        std::vector<int> samples;

    public:
        statistics() : _types( 0 ), _n( 0 ), _sum( 0 ), _max( std::numeric_limits<int>::min() ),
            _min( std::numeric_limits<int>::max() ) {}

        void new_type() {
            _types++;
        }
        void add( int new_val ) {
            _n++;
            _sum += new_val;
            _max = std::max( _max, new_val );
            _min = std::min( _min, new_val );
            samples.push_back( new_val );
        }
        float adj_wald_error() {
            // Z-value for 99.9% confidence interval.
            constexpr float Z = 3.291;
            constexpr float Zsq = Z * Z;
            // Implementation of outline from https://measuringu.com/ci-five-steps/
            float adj_numerator = ( Zsq / 2 ) + sum();
            float adj_denominator = Zsq + n();
            float adj_proportion = adj_numerator / adj_denominator;
            float a = adj_proportion * ( 1.0 - adj_proportion );
            float b = a / adj_denominator;
            float c = sqrt( b );
            return c * Z;
        }
        int types() const {
            return _types;
        }
        int sum() const {
            return _sum;
        }
        int max() const {
            return _max;
        }
        int min() const {
            return _min;
        }
        float avg() const {
            return ( float )_sum / ( float )_n;
        }
        int n() const {
            return _n;
        }
        std::vector<int> get_samples() {
            return samples;
        }
};

#endif
