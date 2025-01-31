#include "arx.h"

ARX::ARX(vector<double> wektorA, vector<double> wektorB, int opoznienie)
{
    setOpoznienie(opoznienie);
    setWektory(wektorA, wektorB);
    inicjalizujBufory();
}

void ARX::setOpoznienie(int i_opoznienie)
{
    if (i_opoznienie < 0) opoznienie = 0;
    else opoznienie = i_opoznienie;
    inicjalizujBufory();

}

void ARX::setWektory(vector<double> A, vector<double> B)
{
    wektorA.clear();
    wektorB.clear();
    wektorA = A;
    wektorB = B;
}

void ARX::inicjalizujBufory()
{
    /*historiaY.clear();
    historiaU.clear();*/
    opoznienieTransportowe.clear();
    opoznienieTransportowe.assign(opoznienie,0.0f);

    historiaU.resize(wektorB.size());
    historiaY.resize(wektorA.size());
}

double ARX::Oblicz(double u)
{
    double mean = 0, stdev = 0.01;

    random_device gen_los;
    mt19937 gen_plos;
    gen_plos.seed(gen_los());

    normal_distribution<double> rozkladGausa(mean, stdev);
    double zaklocenia = rozkladGausa(gen_plos);

    double wyjscie = 0.0f;



    opoznienieTransportowe.push_back(u);


        double opoznione_u = opoznienieTransportowe.front();
        opoznienieTransportowe.pop_front();

        historiaU.push_front(opoznione_u);

            historiaU.pop_back();




    for (int i = 0; i < wektorA.size(); i++)
        wyjscie -= wektorA[i] * historiaY[i];
    for (int j = 0; j < wektorB.size(); j++)
        wyjscie += wektorB[j] * historiaU[j];

    historiaY.push_front(wyjscie);
    if (historiaY.size() > wektorA.size())
        historiaY.pop_back();

    return wyjscie + zaklocenia;
}
void ARX::reset()
{
    opoznienie = 0.0f;
    inicjalizujBufory();
}

