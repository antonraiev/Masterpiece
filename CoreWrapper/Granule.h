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
                return granule->getLowerBound();
            }
        }

        property double UpperBound
        {
            double get()
            {
                return granule->getUpperBound();
            }
        }

        property double Alpha
        {
            double get()
            {
                return granule->getAlpha();
            }
            void set(double fuzzyFactor)
            {
                granule->setAlpha(fuzzyFactor);
            }
        }

        property double Beta
        {
            double get()
            {
                return granule->getBeta();
            }
            void set(double beta)
            {
                granule->setBeta(beta);
            }
        }

    private:
        Core::Granule *granule;
    };
}
