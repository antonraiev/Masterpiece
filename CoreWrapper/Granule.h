#include <Granule.h>

namespace CoreWrapper
{
    public ref class Granule
    {
    public:

        Granule(double lowerBound, double upperBound, double alpha, double beta)
        {
            granule = new Core::Granule(lowerBound, upperBound, alpha, beta);
        }

        Granule(double alpha, double beta)
        {
            granule = new Core::Granule(alpha, beta);
        }

        Granule()
        {
            granule = new Core::Granule();
        }

        ~Granule()
        {
            delete granule;
        }

        property double LowerBound
        {
            double get()
            {
                return granule->lowerBound;
            }
            void set(double lowerBound)
            {
                granule->lowerBound = lowerBound;
            }
        }

        property double UpperBound
        {
            double get()
            {
                return granule->upperBound;
            }
            void set(double upperBound)
            {
                granule->upperBound = upperBound;
            }
        }

        property double Alpha
        {
            double get()
            {
                return granule->alpha;
            }
            void set(double fuzzyFactor)
            {
                granule->alpha = fuzzyFactor;
            }
        }

        property double Beta
        {
            double get()
            {
                return granule->beta;
            }
            void set(double beta)
            {
                granule->beta = beta;
            }
        }

    private:
        Core::Granule *granule;
    };
}
