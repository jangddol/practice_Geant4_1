double Energy_to_b2(double E)
{
    double m = 938.272029;
    return 1 - 1 / ( TMath::Power((E / m) + 1, 2) );
}


double KSI_e6(double b2)
{
    double K = 0.307075;
    double Z = 6;
    double A = 12.011;
    double rho = 2;
    double s = 1000;
    s = s * 100;
    double x = rho * s;
    double z = 1;
    return K * Z * z * z * x / 2 / A / b2;
}


double Density_Eff(double b2)
{
    double lorentz = 1 / TMath::Sqrt(1 - b2);
    double X = TMath::Log10(TMath::Sqrt(b2) * lorentz);
    double X_1 = 2.486;
    double m = 3.00;
    double a = 0.2024;
    double C = -2.99;
    return 4.6052 * X + C + a * TMath::Power(X_1 - X, m);
}


double LAMBDA_L(double E, double E_p=100, double MEP=81)
{
    double b2 = Energy_to_b2(E_p);
    double ksi_e6 = KSI_e6(b2);
    double II_e6 = MEP * MEP * 0.000001;
    double m_ecc = 0.51099895000;
    double inside_log = 2 * m_ecc * b2 * ksi_e6 / II_e6 / (1 - b2);
    double E_mp = ksi_e6 / 1e6 * (TMath::Log(inside_log) - b2 + 1 - 0.5772156649 - Density_Eff(b2));
    return (E - E_mp) / ksi_e6 * 1e6;
}


double KAPPA(double b2)
{
    double m_ecc = 0.51099895000;
    double lorentz = 1 / TMath::Sqrt(1 - b2);
    double eta = b2 * lorentz;
    double m = 938.272029;
    double s = m_ecc / m;
    double temp1 = 2 * m_ecc * eta * eta;
    double temp2 = 1 + 2 * s * TMath::Sqrt(1 + eta * eta) + s * s;
    double W_max = temp1 / temp2;
    return KSI_e6(b2) / W_max / 1e6;
}


double LAMBDA_V(double E, double E_p=100, double MEP=81)
{
    double lambda_l = LAMBDA_L(E, E_p, MEP);
    double b2 = Energy_to_b2(E_p);
    double kappa = KAPPA(b2);
    // return kappa * lambda_l + kappa * TMath::Log(kappa);
    return lambda_l / kappa - TMath::Log(kappa);
}


void Draw_Vavilov()
{
    double E_p = 100.;
    double beta2 = Energy_to_b2(E_p);
    Double_t kappa = KAPPA(beta2);
    double MEP = 81.;
    
    std::cout << "KSI : " << KSI_e6(beta2) / 1e6 << std::endl;
    std::cout << "kappa : " << kappa << std::endl;
    
    auto vavilov = ROOT::Math::VavilovAccurate();

    auto gr = new TGraph();
    for (int i=-20; i<100; i++)
    {
        std::cout << " at x = " << 1 + i*0.01 << " , f(x) = " << vavilov.Pdf(LAMBDA_L(1+i*0.01, E_p, MEP), kappa, beta2) << std::endl;
        gr->AddPoint(1+i*0.01, vavilov.Pdf(LAMBDA_L(1+i*0.01, E_p, MEP), kappa, beta2));
    }
    gr->Draw();
}
