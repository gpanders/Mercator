#include <boost/program_options.hpp>
#include <iostream>

#include "mercator.h"
#include "util/colmap.h"

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const std::string fname = argv[1];

    std::vector<mercator::Point> points;
    if (mercator::ReadCOLMAP(fname, &points))
    {
        std::cout << "This file has " << points.size() << " points." << std::endl;

        std::vector<double> uncertainty(points.size());
        std::transform(points.begin(), points.end(), uncertainty.begin(),
                [](const mercator::Point& p) { return p.Uncertainty(); });

        auto sum = std::accumulate(uncertainty.begin(), uncertainty.end(), 0.0);
        auto avg = sum / uncertainty.size();

        auto minmax = std::minmax_element(uncertainty.begin(), uncertainty.end());

        std::cout << "The average uncertainty is " << avg << std::endl;
        std::cout << "The min uncertainty is " << *minmax.first << std::endl;
        std::cout << "The max uncertainty is " << *minmax.second << std::endl;
    }
    else
    {
        std::cout << "Something went wrong." << std::endl;
        return 1;
    }

    return 0;
}
