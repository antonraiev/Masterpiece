#include <Granule.h>

namespace CoreWrapper
{
    public ref class Granule
    {
    public:

        Granule(double lowerBound, double upperBound, double fuzzyFactor)
        {
            granule = new Core::Granule(lowerBound, upperBound, fuzzyFactor);
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

        property double FuzzyFactor
        {
            double get()
            {
                return granule->fuzzyFactor;
            }
            void set(double fuzzyFactor)
            {
                granule->fuzzyFactor = fuzzyFactor;
            }
        }

    private:
        Core::Granule *granule;
    };
}
