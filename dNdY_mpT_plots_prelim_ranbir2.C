void dNdY_mpT_plots_prelim_ranbir()
{
  
  const Int_t m=9;//v0m
  const Int_t mm=9;//refMult
   const Int_t m1=9;//v0m
  //=======================// V0M //===================================//
  Double_t dndy[m], dndy_err_stat[m], dndy_err_syst[m],  dndy_err_uncorr_syst[m];
  Double_t meanpT[m], meanpT_err_stat[m], meanpT_err_syst[m],  meanpT_err_uncorr_syst[m];
  Double_t mNch[m],  mNchErr[m],mNch3[m],mNchErr3[m];

  Double_t dndy1[m], dndy_err_stat1[m], dndy_err_syst1[m],  dndy_err_uncorr_syst1[m];
  Double_t meanpT1[m], meanpT_err_stat1[m], meanpT_err_syst1[m],  meanpT_err_uncorr_syst1[m];
  Double_t mNch1[m],  mNchErr1[m];
  
  Double_t dndy2[m], dndy_err_stat2[m], dndy_err_syst2[m],  dndy_err_uncorr_syst2[m];
  Double_t meanpT2[m], meanpT_err_stat2[m], meanpT_err_syst2[m],  meanpT_err_uncorr_syst2[m];
  Double_t mNch2[m],  mNchErr2[m];

  Double_t meanpT3[m], meanpT_err_stat3[m], meanpT_err_syst3[m],  meanpT_err_uncorr_syst3[m]; //p-Pb 8.16 TeVs
  Double_t  dndy3[m], dndy_err_stat3[m],dndy_err_syst3[m],dndy_err_uncorr_syst3[m],dNdY_err_AllSyst8[m];

  //=======================// for pT:0-10 //================================
  // common cent :    0-1      1-5                                                             70-100
  Double_t dNdY7[m]={0.347805,0.27295,0.234799,0.194971,0.156801,0.131264,0.108082,0.0808764,0.0510472};//Prelim
  Double_t dNdY_Err_Stat7[m]={0.018524,0.0078071,0.0058003,0.0045024,0.00274,0.00326,0.002532,0.0013447,0.0007303};//TOFVeto final
  Double_t dNdY_err_AllSyst7[m]={0.0404492,0.0327791,0.0292543,0.0230417,0.0196934,0.0157085,0.012865,0.0107036,0.0074112};
  Double_t dNdY_err_Uncorr_Syst7[m]={0.0229693,0.0183245,0.019052,0.0125168,0.0110647,0.00927558,0.00709954,0.00531366,0.00391748};//new code

  Double_t dNdY13[m]={0.475037, 0.36723, 0.306714,0.246756,0.19046,0.158325,0.126622,0.0918896,0.0600987};
  Double_t dNdY_Err_Stat13[m]={0.0243471, 0.0097, 0.00862482,0.0052017,0.00445075,0.00395636,0.00322557,0.00188092,0.00111314};
  Double_t dNdY_err_AllSyst13[m]={0.042471, 0.0317, 0.0268035,0.0214209,0.0167011,0.0138437,0.0111459,0.00812942,0.0054407};
  Double_t dNdY_err_Uncorr_Syst13[m]={0.0252584, 0.019,0.0158201,0.0104554,0.0102944,0.00691163,0.00598276,0.00387925,0.00241232};

  Double_t dNdY5[m1]={0.6162, 0.4263, 0.3016,0.1852,0.0832};
  Double_t dNdY_Err_Stat5[m1]={0.0078,0.0056 , 0.0039, 0.0026 , 0.0013 };
  Double_t dNdY_err_Uncorr_Syst5[m1]={0.0371,0.0261,0.0194,0.0126,0.0054};
  Double_t dNdY_err_corr_Syst5[m1]={0.0370,0.0256,0.0181,0.0111,0.0050};
  Double_t dNdY_err_AllSyst5[m1]={0.0};

  //pp@5.02 TeV
  //Double_t dNdY_pp5TeV[]={0.36933, 0.274905, 0.23086, 0.207895, 0.176386, 0.153655, 0.12731, 0.108057, 0.0830711, 0.0579436};
  Double_t dNdY_pp5TeV[]={0.35917, 0.274905, 0.23086, 0.207895, 0.176386, 0.153655, 0.12731, 0.108057, 0.0830711, 0.0579436};
  Double_t dNdY_Err_Stat_pp5TeV[]={0.01192, 0.004718, 0.00349, 0.0032, 0.00293, 0.00174, 0.001538, 0.00131, 0.0007671, 0.0004068 };
  Double_t dNdy_err_AllSyst_pp5TeV[] = {0.030671,0.02284,0.01957,0.01697,0.01572,0.012219,0.010317,0.009012,0.006805,0.00494466};
  

  for(int i=0;i<5;i++)
    {
      dNdY_err_AllSyst5[i]=TMath::Sqrt(TMath::Power(dNdY_err_Uncorr_Syst5[i],2.0)+TMath::Power(dNdY_err_corr_Syst5[i],2.0));
    }

   Double_t dNdY8[m]={0.918,0.783,0.644,0.4893,0.344,0.22,0.092};
   Double_t dNdY_Err_Stat8[m]={0.030,0.025,0.017,0.009,0.0058,0.004,0.002};
   //   Double_t dNdY_err_AllSyst8[m]={0.08,0.07,0.064,0.047,0.033,0.021,0.011};
   
   //  Double_t dNdY_err_AllSyst8[m]={0.088,0.076,0.052,0.047,0.033,0.021,0.011};  // final with systmatic plot, new
     Double_t dNdY_err_AllSyst8[m]={0.086,0.074,0.060,0.045,0.032,0.020,0.008};  // final with systmatic plot, new 

   Double_t dNdY_err_Uncorr_Syst8[m]={0.047,0.05,0.047,0.028,0.0187,0.016,0.006};
   //Double_t dNdY_err_corr_Syst8[m]={0.0,0.0,0.0,0.0,0.0,0.0,0.0};
   // Double_t dNdY_err_corr_Syst8[m]={0.08,0.07,0.064,0.047,0.033,0.021,0.011};

   //for(int i=0;i<7;i++)
   // {
      //    dNdY_err_AllSyst8[i]=TMath::Sqrt(TMath::Power(dNdY_err_Uncorr_Syst8[i],2.0)+TMath::Power(dNdY_err_corr_Syst8[i],2.0));
   // }
   
  
//Double_t dNdY_err_Uncorr_Syst8[m]={0.08,0.07,0.064,0.047,0.033,0.021,0.011};
//Double_t dNdY_err_corr_Syst8[m]={0.11,0.10,0.083,0.06,0.04,0.026,0.013};
// Double_t dNdY_err_AllSyst8[m1]={0.00,0.00,0.0,0.0,0.0,0.0,0.0};
  //Double_t dNdY_err_AllSyst8[m]={0.04,0.04,0.032,0.019,0.0116,0.004,0.005};
  
  //Double_t MeanPT_pp5TeV[]={1.3373, 1.27398, 1.21527, 1.1569, 1.14254, 1.09535, 1.03131, 0.981254, 0.91439, 0.768355};
  Double_t MeanPT_pp5TeV[]={1.34394, 1.27398, 1.21527, 1.1569, 1.14254, 1.09535, 1.03131, 0.981254, 0.91439, 0.768355};
  Double_t MeanPT_Err_Stat_pp5TeV[]={0.024995, 0.013094, 0.011467, 0.01083, 0.01101, 0.00798, 0.007421, 0.007183, 0.005303, 0.00335754};
  Double_t MeanPT_err_AllSyst_pp5TeV[] = {0.026375, 0.026726, 0.026222, 0.02483, 0.025555, 0.02373, 0.02251, 0.022034, 0.02146, 0.0186467};

  Double_t MeanPT7[m]={1.30745,1.29523,1.21093,1.15007,1.06396,1.01403,0.955683,0.865553,0.718472};//Prelim
  Double_t MeanPT_Err7[m]={0.038,0.022284,0.018369,0.015936,0.011144,0.015074,0.013498,0.0088223,0.00579};//TOFVeto final
  Double_t MeanpT_err_Syst7[m]={0.0432,0.0350,0.036665,0.03454,0.0325682,0.0310432,0.0291503,0.0283119,0.0244902};//All cuts max
  Double_t MeanpT_err_Uncorr_Syst7[m] ={0.0236,0.0207958,0.021921,0.0188344,0.0198069,0.017235,0.0151107,0.0138167,0.0135864};

  Double_t MeanPT13[m]={1.43964,1.383,1.31609,1.25389,1.1917,1.12303,1.04486,0.961482,0.777812,};
  Double_t MeanPT_Err13[m]={0.051066, 0.024,0.0236348,0.0169474,0.0172009,0.017239,0.0160664,0.0117323,0.00822886};
  Double_t MeanpT_err_Syst13[m]={0.0377687, 0.0327,0.0345717,0.0319632,0.0315482,0.0293938,0.0274291,0.0259624,0.0214443};
  Double_t MeanpT_err_Uncorr_Syst13[m] ={0.0243678, 0.021,0.0198272,0.0155941,0.0172001,0.0134475,0.0118615,0.0131214,0.0079853};

  Double_t MeanPT5[m1]={1.379,1.2998,1.2109,1.1080,0.9433};
  Double_t MeanPT_Err5[m1]={0.011,0.0097,0.0094,0.0093,0.0092};
  Double_t MeanpT_err_Syst5[m1]={0.020,0.0186,0.0173,0.0214, 0.0164,};

 
  Double_t MeanPT8[m]={1.507,1.46,1.45,1.40,1.3,1.17,0.95};
  Double_t MeanPT_Err8[m]={0.033,0.029,0.021,0.016,0.018,0.012,0.018};

  //  Double_t MeanpT_err_Syst8[m]={0.032,0.036,0.029,0.026,0.029,0.026,0.026};
  //  Double_t MeanpT_err_Syst8[m]={0.032,0.036,0.029,0.026,0.029,0.026,0.026}; // old 

  Double_t MeanpT_err_Syst8[m]={0.028,0.03,0.028,0.0253,0.0251,0.026,0.0258}; // new 


  Double_t MeanpT_err_Uncorr_Syst8[m] ={0.018,0.021,0.020,0.017,0.0143,0.020,0.018};

  

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
  Double_t MNch7[m] = {21.294, 16.513, 13.457, 10.793, 8.447, 6.724, 5.398, 3.897, 2.261};
  Double_t MNchErr7[m] = {0.64012, 0.4951, 0.404, 0.324, 0.254, 0.207, 0.173, 0.143, 0.117};
 
  Double_t MNch13[m] = {26.18, 20.16, 16.4, 13.14, 10.31, 8.24, 6.62, 4.77, 2.76};
  Double_t MNchErr13[m] = {0.55, 0.41, 0.34, 0.27, 0.21, 0.17, 0.13, 0.09, 0.05};
 
  Double_t MNch5[m] = {35.55,23.2,16.1,9.8,4.16};
  Double_t MNchErr5[m] = {0.8,0.5,0.4,0.2,0.09};  

  Double_t MNch_pp5TeV[] = {18.92, 14.86, 12.23, 10.57, 9.36, 7.97, 6.53, 5.40, 4.13, 2.67};
  Double_t MNchErr_pp5TeV[] = {0.16, 0.12, 0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03};
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

  Double_t MNch8[m] = {54.23,42.40,35.49,26.89,18.39,10.97,4.47};
  Double_t MNchErr8[m]={1.49,1.19,0.99,0.75,0.51,0.31,0.12};
  
    
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
  //=============// 7 tev //====================//
  TGraphErrors *gdNdy_1 = new TGraphErrors();   
  TGraphErrors *gdNdy_11 = new TGraphErrors();
  TGraphErrors *gdNdy_111 = new TGraphErrors(); //syst_uncorr
  TGraphErrors *gmpT_1 = new TGraphErrors(); 
  TGraphErrors *gmpT_11 = new TGraphErrors();
  TGraphErrors *gmpT_111 = new TGraphErrors();
  
  //=============// 13 tev //================//
  TGraphErrors *gdNdy_2 = new TGraphErrors();  
  TGraphErrors *gdNdy_22 = new TGraphErrors(); 
  TGraphErrors *gdNdy_222 = new TGraphErrors(); 
  TGraphErrors *gmpT_2 = new TGraphErrors();  
  TGraphErrors *gmpT_22 = new TGraphErrors(); 
  TGraphErrors *gmpT_222 = new TGraphErrors(); //syst_uncorr  

  //==============// 5 tev///================//
  TGraphErrors *gdNdy_3 = new TGraphErrors();  
  TGraphErrors *gdNdy_33 = new TGraphErrors(); 
  TGraphErrors *gdNdy_333 = new TGraphErrors(); 
  TGraphErrors *gmpT_3 = new TGraphErrors();  
  TGraphErrors *gmpT_33 = new TGraphErrors(); 
  TGraphErrors *gmpT_333 = new TGraphErrors(); //syst_uncorr


  TGraphErrors *gdNdy_4 = new TGraphErrors();
  TGraphErrors *gdNdy_44 = new TGraphErrors();
  TGraphErrors *gdNdy_444 = new TGraphErrors();

  
  TGraphErrors *gmpT_4 = new TGraphErrors();
  TGraphErrors *gmpT_44 = new TGraphErrors();
  TGraphErrors *gmpT_444 = new TGraphErrors();
  

  //===========// pp@5.02 TeV///==============//
  TGraphErrors *gdNdy_pp5TeV_1 = new TGraphErrors(10);
  TGraphErrors *gdNdy_pp5TeV_2 = new TGraphErrors(10);
  TGraphErrors *gmpT_pp5TeV_1 = new TGraphErrors(10);
  TGraphErrors *gmpT_pp5TeV_2 = new TGraphErrors(10);
  //=========================================//



  

  gdNdy_1->SetLineWidth(2);
  gmpT_1->SetLineWidth(2);
  gdNdy_11->SetLineWidth(2);
  gdNdy_11->SetLineColor(kBlue);
  gmpT_11->SetLineWidth(2);
  gmpT_11->SetLineColor(kBlue);

  gdNdy_2->SetLineWidth(2);
  gmpT_2->SetLineWidth(2);
  gdNdy_22->SetLineWidth(2);
  gdNdy_22->SetLineColor(kRed);
  gmpT_22->SetLineWidth(2);
  gmpT_22->SetLineColor(kRed);

  gdNdy_3->SetLineWidth(2);
  gmpT_3->SetLineWidth(2);
  gdNdy_33->SetLineWidth(2);
  gdNdy_33->SetLineColor(6);
  gmpT_33->SetLineWidth(2);
  gmpT_33->SetLineColor(6);

   /*********************8 Tev******************/
  gdNdy_4->SetLineWidth(2);
  gdNdy_44->SetLineWidth(2);
  gdNdy_44->SetLineColor(9);

  gmpT_4->SetLineWidth(2);
  gmpT_44->SetLineWidth(2);
  gmpT_44->SetLineColor(9);
  /**************************************/

  gdNdy_pp5TeV_1->SetMarkerSize(1.4);
  gdNdy_pp5TeV_1->SetMarkerColor(kRed);
  gdNdy_pp5TeV_1->SetLineColor(kRed);
  gdNdy_pp5TeV_1->SetMarkerSize(1.4);
  gdNdy_pp5TeV_1->SetMarkerStyle(21);

  gdNdy_pp5TeV_2->SetLineColor(kRed);
  gdNdy_pp5TeV_2->SetFillStyle(3000);
  gdNdy_pp5TeV_2->SetFillColor(0);

  gmpT_pp5TeV_1->SetMarkerSize(1.4);
  gmpT_pp5TeV_1->SetMarkerColor(kRed);
  gmpT_pp5TeV_1->SetLineColor(kRed);
  gmpT_pp5TeV_1->SetMarkerSize(1.4);
  gmpT_pp5TeV_1->SetMarkerStyle(21);

  gmpT_pp5TeV_2->SetLineColor(kRed);
  gmpT_pp5TeV_2->SetFillStyle(3000);
  gmpT_pp5TeV_2->SetFillColor(0);

  
  //=================// V0M //==============//
  for (Int_t i=0; i<9; i++)
    {     
      dndy[i] = dNdY7[i];
      dndy_err_stat[i] = dNdY_Err_Stat7[i];
      dndy_err_syst[i] = dNdY_err_AllSyst7[i];
      dndy_err_uncorr_syst[i] = dNdY_err_Uncorr_Syst7[i];
            
      dndy1[i] = dNdY13[i];
      dndy_err_stat1[i] = dNdY_Err_Stat13[i];
      dndy_err_syst1[i] = dNdY_err_AllSyst13[i];
      dndy_err_uncorr_syst1[i] = dNdY_err_Uncorr_Syst13[i];
      
      if(i<5)
	{
	  dndy2[i] = dNdY5[i];
	  dndy_err_stat2[i] = dNdY_Err_Stat5[i];
	  dndy_err_syst2[i] = dNdY_err_AllSyst5[i];
	  dndy_err_uncorr_syst2[i] = dNdY_err_Uncorr_Syst5[i];
	}

       if(i< 7)
	 {
	   dndy3[i] = dNdY8[i];
	   dndy_err_stat3[i] = dNdY_Err_Stat8[i];
	   dndy_err_syst3[i] = dNdY_err_AllSyst8[i];
	   dndy_err_uncorr_syst3[i] = dNdY_err_Uncorr_Syst8[i];

	 }
      
      meanpT[i] = MeanPT7[i];
      meanpT_err_stat[i] = MeanPT_Err7[i];
      meanpT_err_syst[i] = MeanpT_err_Syst7[i];
      meanpT_err_uncorr_syst[i] = MeanpT_err_Uncorr_Syst7[i];//Mult Uncorr 
      
      meanpT1[i] = MeanPT13[i];
      meanpT_err_stat1[i] = MeanPT_Err13[i];
      meanpT_err_syst1[i] = MeanpT_err_Syst13[i];
      meanpT_err_uncorr_syst1[i] = MeanpT_err_Uncorr_Syst13[i];//Mult Uncorr 
      
      if(i<5)
	{
	  meanpT2[i] = MeanPT5[i];
	  meanpT_err_stat2[i] = MeanPT_Err5[i];
	  meanpT_err_syst2[i] = MeanpT_err_Syst5[i];
	}

      //p-Pb 8.16 TeV
       if(i< 7)
	    {
	  meanpT3[i] = MeanPT8[i];
	  meanpT_err_stat3[i] = MeanPT_Err8[i];
	  meanpT_err_syst3[i] = MeanpT_err_Syst8[i];
	  meanpT_err_uncorr_syst3[i] = MeanpT_err_Uncorr_Syst8[i];//Mult Uncorr 
	    }
  
      
      mNch[i] = MNch7[i];
      mNchErr[i] = MNchErr7[i];
      
      mNch1[i] = MNch13[i];
      mNchErr1[i] = MNchErr13[i];
      
      if(i<5)
	{
	  mNch2[i] = MNch5[i];
	  mNchErr2[i] = MNchErr5[i];
	}

      //p-Pb 8TeV
         if(i< 7)
	    {
	  mNch3[i] = MNch8[i];
	  mNchErr3[i] = MNchErr8[i];
	    }
      
      //-------------------------------------//
      //-------------------------------------//
      gdNdy_1->SetPoint(i, mNch[i], dndy[i]);
      gdNdy_1->SetPointError(i, mNchErr[i], dndy_err_stat[i]);
      
      gdNdy_11->SetPoint(i, mNch[i], dndy[i]);
      gdNdy_11->SetPointError(i, mNchErr[i], dndy_err_syst[i]);
      
      gdNdy_111->SetPoint(i, mNch[i], dndy[i]);
      gdNdy_111->SetPointError(i, mNchErr[i], dndy_err_uncorr_syst[i]);
            
      gdNdy_2->SetPoint(i, mNch1[i], dndy1[i]);
      gdNdy_2->SetPointError(i, mNchErr1[i], dndy_err_stat1[i]);
      
      gdNdy_22->SetPoint(i, mNch1[i], dndy1[i]);
      gdNdy_22->SetPointError(i, mNchErr1[i], dndy_err_syst1[i]);
      
      gdNdy_222->SetPoint(i, mNch1[i], dndy1[i]);
      gdNdy_222->SetPointError(i, mNchErr1[i], dndy_err_uncorr_syst1[i]);
      
      if(i<5)
	{
	  gdNdy_3->SetPoint(i, mNch2[i], dndy2[i]);
	  gdNdy_3->SetPointError(i, mNchErr2[i], dndy_err_stat2[i]);
	  
	  gdNdy_33->SetPoint(i, mNch2[i], dndy2[i]);
	  gdNdy_33->SetPointError(i, mNchErr2[i], dndy_err_syst2[i]);
	  
	  gdNdy_333->SetPoint(i, mNch2[i], dndy2[i]);
	  gdNdy_333->SetPointError(i, mNchErr2[i], dndy_err_uncorr_syst2[i]);
	}
      
      gmpT_1->SetPoint(i, mNch[i], meanpT[i]);
      gmpT_1->SetPointError(i, mNchErr[i], meanpT_err_stat[i]);
      
      gmpT_11->SetPoint(i, mNch[i], meanpT[i]);
      gmpT_11->SetPointError(i, mNchErr[i], meanpT_err_syst[i]);      
      
      gmpT_111->SetPoint(i, mNch[i], meanpT[i]);
      gmpT_111->SetPointError(i, mNchErr[i], meanpT_err_uncorr_syst[i]);
      
      gmpT_2->SetPoint(i, mNch1[i], meanpT1[i]);
      gmpT_2->SetPointError(i, mNchErr1[i], meanpT_err_stat1[i]);
      
      gmpT_22->SetPoint(i, mNch1[i], meanpT1[i]);
      gmpT_22->SetPointError(i, mNchErr1[i], meanpT_err_syst1[i]);
      
      
      gmpT_222->SetPoint(i, mNch1[i], meanpT1[i]);
      gmpT_222->SetPointError(i, mNchErr1[i], meanpT_err_uncorr_syst1[i]);
      
      if(i<5)
	{
	  gmpT_3->SetPoint(i, mNch2[i], meanpT2[i]);
	  gmpT_3->SetPointError(i, mNchErr2[i], meanpT_err_stat2[i]);
	  
	  gmpT_33->SetPoint(i, mNch2[i], meanpT2[i]);
	  gmpT_33->SetPointError(i, mNchErr2[i], meanpT_err_syst2[i]);
	}

//--------------------pPb8TeV//--------------------------//
         if(i<7)
	    {
	  gdNdy_4->SetPoint(i, mNch3[i], dndy3[i]);
	  gdNdy_4->SetPointError(i, mNchErr3[i], dndy_err_stat3[i]);
	  
	  gdNdy_44->SetPoint(i, mNch3[i], dndy3[i]);
	  gdNdy_44->SetPointError(i, mNchErr3[i], dndy_err_syst3[i]);
	  
	  gdNdy_444->SetPoint(i, mNch3[i], dndy3[i]);
	  gdNdy_444->SetPointError(i, mNchErr3[i],dndy_err_uncorr_syst3[i]);
	    }
         if(i<7)
	    {
	      gmpT_4->SetPoint(i, mNch3[i], meanpT3[i]);
	      gmpT_4->SetPointError(i, mNchErr3[i], meanpT_err_stat3[i]);
	  
	      gmpT_44->SetPoint(i, mNch3[i], meanpT3[i]);
	      gmpT_44->SetPointError(i, mNchErr3[i],meanpT_err_syst3[i]);

	  gmpT_444->SetPoint(i, mNch3[i], meanpT3[i]);
	  gmpT_444->SetPointError(i, mNchErr3[i],meanpT_err_uncorr_syst3[i]);
	    }
  

    }

      
    
  //-----------// pp@5 TeV //-------------------//
  for (Int_t i=0; i<10; i++)
    {
      gdNdy_pp5TeV_1->SetPoint(i, MNch_pp5TeV[i], dNdY_pp5TeV[i]);
      gdNdy_pp5TeV_1->SetPointError(i, MNchErr_pp5TeV[i], dNdY_Err_Stat_pp5TeV[i]);
      
      gdNdy_pp5TeV_2->SetPoint(i, MNch_pp5TeV[i], dNdY_pp5TeV[i]);
      gdNdy_pp5TeV_2->SetPointError(i, MNchErr_pp5TeV[i], dNdy_err_AllSyst_pp5TeV[i]);
      
      gmpT_pp5TeV_1->SetPoint(i, MNch_pp5TeV[i], MeanPT_pp5TeV[i]);
      gmpT_pp5TeV_1->SetPointError(i, MNchErr_pp5TeV[i], MeanPT_Err_Stat_pp5TeV[i]);
      
      gmpT_pp5TeV_2->SetPoint(i, MNch_pp5TeV[i], MeanPT_pp5TeV[i]);
      gmpT_pp5TeV_2->SetPointError(i, MNchErr_pp5TeV[i], MeanPT_err_AllSyst_pp5TeV[i]);      
    }


  
  //=================// dN/dY //============================
  TCanvas *cdNdY_2 = new TCanvas("cdNdY_2","cdNdY_2",100,100,600,600);
  cdNdY_2->cd();
  cdNdY_2->SetLeftMargin(0.18);
  cdNdY_2->SetRightMargin(0.03);
  cdNdY_2->SetTopMargin(0.03);
  cdNdY_2->SetBottomMargin(0.18);
  cdNdY_2->SetTicks(1,1);
  //cdNdY_2->SetTicky(1);
  //gdNdy_2->SetTicks(1,1);
 
  gdNdy_1->GetYaxis()->SetTitleSize(0.07);
  gdNdy_1->GetYaxis()->SetLabelSize(0.05);
  gdNdy_1->GetYaxis()->SetTitleOffset(1.08);
  gdNdy_1->GetXaxis()->SetTitleSize(0.07);  
  gdNdy_1->GetXaxis()->SetLabelSize(0.05);
  gdNdy_1->GetXaxis()->SetNdivisions(508);
  gdNdy_1->GetYaxis()->SetNdivisions(508);


  gdNdy_1->SetMarkerSize(1.4);
  gdNdy_1->SetMarkerStyle(24);
  gdNdy_1->SetMarkerColor(kBlue);
  gdNdy_1->SetLineColor(kBlue);
 
  gdNdy_11->SetLineColor(kBlue);
  gdNdy_11->SetFillStyle(0);
  gdNdy_11->SetFillColor(0);

  //gdNdy_111->SetFillStyle(3001);
  //gdNdy_111->SetFillColor(kBlue-10);  
  gdNdy_111->SetFillStyle(1001);
  gdNdy_111->SetFillColorAlpha(kBlue-9, 0.4);
  gdNdy_111->SetMarkerSize(1.4);
  gdNdy_111->SetMarkerStyle(24);
  gdNdy_111->SetMarkerColor(kBlue);
  gdNdy_111->SetLineColor(kBlue);
 
  gdNdy_1->SetMinimum(-0.0);
  gdNdy_1->SetMaximum(1.2);
  gdNdy_1->GetXaxis()->SetLimits(0,60);
    
  gdNdy_2->SetMarkerSize(1.8);
  gdNdy_2->SetMarkerStyle(27);
  gdNdy_2->SetMarkerColor(kGreen);
  gdNdy_2->SetLineColor(kGreen);
 
  gdNdy_22->SetLineColor(kGreen);
  gdNdy_22->SetFillStyle(0);
  gdNdy_22->SetFillColor(0);

  gdNdy_222->SetFillStyle(1001);
   gdNdy_222->SetFillColorAlpha(kGreen-9, 0.4);
  gdNdy_222->SetMarkerSize(1.8);
  gdNdy_222->SetMarkerStyle(27);
  //gdNdy_222->SetMarkerColor(kRed);
  //gdNdy_222->SetLineColor(kRed);
  /*
  gdNdy_3->SetMarkerSize(1.4);
  gdNdy_3->SetMarkerStyle(34);
  gdNdy_3->SetMarkerColor(kBlue);
  gdNdy_3->SetLineColor(kBlue);
  
  gdNdy_33->SetLineColor(kBlue);
  gdNdy_33->SetFillStyle(0);
  gdNdy_33->SetFillColor(0);

  //gdNdy_333->SetFillStyle(3001);
  //gdNdy_333->SetFillColor(kMagenta-9);  
  gdNdy_333->SetFillStyle(1001);
  gdNdy_333->SetFillColorAlpha(kBlue, 0.4);
  gdNdy_333->SetMarkerSize(1.4);
  gdNdy_333->SetMarkerStyle(34);
  gdNdy_333->SetMarkerColor(kBlue);
  gdNdy_333->SetLineColor(kBlue);
  */
  gdNdy_3->SetMarkerSize(1.4);
  gdNdy_3->SetMarkerStyle(34);
  gdNdy_3->SetMarkerColor(kMagenta);
  gdNdy_3->SetLineColor(kMagenta);
  
  gdNdy_33->SetLineColor(kMagenta);
  gdNdy_33->SetMarkerColor(kMagenta);
  gdNdy_33->SetFillStyle(0);
  gdNdy_33->SetFillColor(0);
  
  gdNdy_333->SetFillStyle(1001);
  //gdNdy_333->SetFillColor(kMagenta-9);  
  // gdNdy_333->SetFillStyle(1001);
  //gdNdy_333->SetFillColorAlpha(kMagenta-9,0.4);

 
  gdNdy_333->SetMarkerColor(kMagenta);
  gdNdy_333->SetLineColor(kMagenta);
   
  gdNdy_333->SetMarkerSize(1.4);
  gdNdy_333->SetMarkerStyle(34);
  gdNdy_333->SetFillColorAlpha(kMagenta-9,0.9);
  // gdNdy_333->SetFillColor(kMagenta-9,0.6);

  gdNdy_4->SetMarkerSize(1.4);
  gdNdy_4->SetMarkerStyle(20);
  gdNdy_4->SetMarkerColor(kRed);
  gdNdy_4->SetLineColor(kRed);
  
  gdNdy_44->SetLineColor(kRed);
  gdNdy_44->SetMarkerColor(kRed);
  gdNdy_44->SetFillStyle(0);
  gdNdy_44->SetFillColor(0);

 
  gdNdy_444->SetMarkerSize(1.4);
  gdNdy_444->SetMarkerStyle(20);
  gdNdy_444->SetMarkerColor(kRed);
  gdNdy_444->SetLineColor(kRed);
  gdNdy_444->SetFillStyle(1001);
  gdNdy_444->SetFillColorAlpha(kRed-9,0.3);

  // gdNdy_444->SetFillColor(kRed-9,0.1);
  
  /*
  gdNdy_4->SetMarkerSize(1.4);
  gdNdy_4->SetMarkerStyle(20);
  gdNdy_4->SetMarkerColor(kBlack);
  gdNdy_4->SetLineColor(kBlack);
  
  gdNdy_44->SetLineColor(kBlack);
  gdNdy_44->SetMarkerColor(kBlack);
  gdNdy_44->SetFillStyle(0);
  gdNdy_44->SetFillColor(0);

  gdNdy_444->SetFillStyle(1001);
  gdNdy_444->SetFillColorAlpha(kGray,0.8);
  gdNdy_444->SetMarkerSize(1.4);
  gdNdy_444->SetMarkerStyle(20);
  gdNdy_444->SetMarkerColor(kGray);
  gdNdy_444->SetLineColor(kGray);
  */


  
 
  //
  gdNdy_1->Draw("PSAMEA");
  gdNdy_111->Draw("2SAME");                                                                     gdNdy_11->Draw("5SAME");
  gdNdy_1->Draw("PSAMEZ");
  
  

   gdNdy_222->Draw("2SAME");                                                                     gdNdy_22->Draw("5SAME");  
    gdNdy_2->Draw("PSAMEZ");

   gdNdy_333->Draw("2SAME");                                                                    gdNdy_33->Draw("5SAME");  
   gdNdy_3->Draw("PSAMEZ");

    // gdNdy_pp5TeV_1->Draw("PSAME");
    //gdNdy_pp5TeV_2->Draw("5SAME");
    //gdNdy_pp5TeV_1->Draw("PSAME");
  
   gdNdy_444->Draw("2SAME");                                                                                              
   gdNdy_44->Draw("5SAME");
   gdNdy_4->Draw("PSAMEZ");


  

  //  TLegend *llp1 = DrawLegend(0.22,0.70,0.40,0.95);
  //TLegend *llp1 = DrawLegend(0.22,0.68,0.40,0.93);
  TLegend *llp1 = DrawLegend(0.22,0.65,0.4,0.93);
  llp1->AddEntry(gdNdy_3,"p-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV (EPJC 76 (2016) 245)","lp");
  llp1->AddEntry((TObject*)0,"#bf{ALICE Preliminary}","");
  llp1->AddEntry(gdNdy_4,"p-Pb, #sqrt{#it{s}_{NN}} = 8.16 TeV ","lp");
  llp1->AddEntry(gdNdy_2,"pp, #sqrt{#it{s}} = 13 TeV","lp");
  llp1->AddEntry(gdNdy_1,"pp, #sqrt{#it{s}} = 7 TeV","lp");
  // llp1->AddEntry(gdNdy_pp5TeV_1,"pp, #sqrt{#it{s}} = 5.02 TeV","lp");
  llp1->AddEntry((TObject*)0,"V0 Multiplicity Event Classes","");
  llp1->Draw();

   float  lx=4.4;float ly=0.7;
   
   TLatex* tt3=new TLatex(lx,ly,"K*^{0}");
   //tt3->SetNDC();
   tt3->SetTextFont(42);
   tt3->SetTextAlign(13);
   tt3->SetTextSize(0.08);
   tt3->Draw();
        
   TLatex *tex1  = new TLatex(12.0,0.15,"Uncertainties: stat.(bars), sys.(boxes),");
   tex1->SetTextAlign(13);
   tex1->SetTextFont(42);
   tex1->SetTextSize(0.035);
   tex1->SetLineWidth(2);
   tex1->Draw();
   
   TLatex *tex2  = new TLatex(12.0,0.097,"uncor. sys. (shaded boxes) ");
   tex2->SetTextAlign(13);
   tex2->SetTextFont(42);
   tex2->SetTextSize(0.035);
   tex2->SetLineWidth(2);
   tex2->Draw();

   /*
     //TLegend *lpp1 = DrawLegend(0.5,0.21,0.65,0.43);
   TLegend *lpp1 = DrawLegend(0.20,0.55,0.38,0.92);
   lpp1->AddEntry((TObject*)0,"#bf{ALICE Preliminary}","");
   lpp1->AddEntry(gdNdy_2,"pp, #sqrt{#it{s}} = 13 TeV","lp");
   lpp1->AddEntry(gdNdy_1,"pp, #sqrt{#it{s}} = 7 TeV","lp");
   lpp1->AddEntry(gdNdy_3,"p-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV","lp");
   lpp1->AddEntry((TObject*)0,"K*^{0}(#bar{K}*^{0}) #rightarrow #pi^{-}K^{+}(#pi^{+}K^{-})","");
   lpp1->AddEntry((TObject*)0,"|#it{y}|<0.5","");
   lpp1->Draw();
   
   TLatex *tex = new TLatex(13.0,0.17,"V0M Multiplicity Event Classes");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.035);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLatex *tex1  = new TLatex(13.0,0.13,"Uncertainties: stat.(bars), sys.(boxes) ");
   tex1->SetTextAlign(13);
   tex1->SetTextFont(42);
   tex1->SetTextSize(0.035);
   tex1->SetLineWidth(2);
   tex1->Draw();
     
   TLatex *tex2  = new TLatex(13.0,0.09,"uncor. sys. (shaded boxes) ");
   tex2->SetTextAlign(13);
   tex2->SetTextFont(42);
   tex2->SetTextSize(0.035);
   tex2->SetLineWidth(2);
   tex2->Draw();
   */
   
   //=================// RefMult //====================================//
   //----------------// mean pT //------------------------------------//
   TCanvas *cmpT_2 = new TCanvas("cmpT_2","cmpT_2",700,100,600,600);
   cmpT_2->cd();
   cmpT_2->SetLeftMargin(0.185);
   cmpT_2->SetRightMargin(0.025);
   cmpT_2->SetTopMargin(0.02067);
   cmpT_2->SetBottomMargin(0.17);
   cmpT_2->SetTicks(1,1);

  
     TLatex *tex1  = new TLatex(28.3,0.47,"Uncertainties: stat.(bars), sys.(boxes), ");
     tex1->SetTextAlign(33);
     tex1->SetTextFont(42);
     tex1->SetTextSize(0.045);
     tex1->SetLineWidth(2);
     tex1->Draw();
     
     TLatex *tex2  = new TLatex(20.9,0.43,"uncor. sys. (shaded boxes) ");
     tex2->SetTextAlign(33);
     tex2->SetTextFont(42);
     tex2->SetTextSize(0.045);
     tex2->SetLineWidth(2);
     tex2->Draw();

  
   //=================// RefMult //====================================//
   //----------------// mean pT //------------------------------------//
   TCanvas *cmpT_2 = new TCanvas("cmpT_2","cmpT_2",700,100,600,600);
   cmpT_2->cd();
   cmpT_2->SetLeftMargin(0.185);
   cmpT_2->SetRightMargin(0.025);
   cmpT_2->SetTopMargin(0.02067);
   cmpT_2->SetBottomMargin(0.17);
   cmpT_2->SetTicks(1,1);  

   gmpT_1->GetYaxis()->SetTitleSize(0.07);
   gmpT_1->GetYaxis()->SetLabelSize(0.05);
   gmpT_1->GetYaxis()->SetTitleOffset(1.08);
   gmpT_1->GetXaxis()->SetTitleSize(0.07);  
   gmpT_1->GetXaxis()->SetLabelSize(0.05);
   gmpT_1->GetXaxis()->SetNdivisions(508);
   gmpT_1->GetYaxis()->SetNdivisions(508);
   gmpT_1->SetMarkerSize(1.2);
   gmpT_1->SetMarkerStyle(24);
   gmpT_1->SetMarkerColor(kBlue);
   gmpT_1->SetLineColor(kBlue);
   
   gmpT_11->SetLineColor(kBlue);
   gmpT_11->SetFillStyle(0);
   gmpT_11->SetFillColor(0);
   
   // gmpT_111->SetFillStyle(3001);
   //gmpT_111->SetFillColor(kBlue-9);  
   gmpT_111->SetFillStyle(1001);
   gmpT_111->SetFillColorAlpha(kBlue-9, 0.4);
   gmpT_111->SetMarkerSize(1.2);
   gmpT_111->SetMarkerStyle(24);
   gmpT_111->SetMarkerColor(kBlue);
   gmpT_111->SetLineColor(kBlue);
   
   gmpT_1->SetMinimum(0.65);
   gmpT_1->SetMaximum(1.97);
   gmpT_1->GetXaxis()->SetLimits(0.0,60);
   
   gmpT_2->SetMarkerSize(1.8);
   gmpT_2->SetMarkerStyle(27);
   gmpT_2->SetMarkerColor(kGreen);
   gmpT_2->SetLineColor(kGreen);
   
   gmpT_22->SetLineColor(kGreen);
   gmpT_22->SetFillStyle(0);
   gmpT_22->SetFillColor(0);
   
   gmpT_222->SetFillStyle(1001);
   gmpT_222->SetFillColorAlpha(kGreen-9, 0.4);
      
   gmpT_3->SetMarkerSize(1.2);
   gmpT_3->SetMarkerStyle(34);
   gmpT_3->SetMarkerColor(kMagenta);
   gmpT_3->SetLineColor(kMagenta);
   
   gmpT_33->SetLineColor(kMagenta);
   gmpT_33->SetFillStyle(0);
   gmpT_33->SetFillColor(0);
   
   gmpT_333->SetFillStyle(1001);
   gmpT_333->SetFillColor(kMagenta-9);  
   gmpT_333->SetMarkerSize(1.2);
   gmpT_333->SetMarkerStyle(34);
   gmpT_333->SetMarkerColor(kMagenta);
   gmpT_333->SetLineColor(kMagenta);


   gmpT_4->SetMarkerSize(1.2);
   gmpT_4->SetMarkerStyle(20);
   gmpT_4->SetMarkerColor(kRed);
   gmpT_4->SetLineColor(kRed);
   
   gmpT_44->SetLineColor(kRed);
   gmpT_44->SetFillStyle(0);
   gmpT_44->SetFillColor(0);
   gmpT_444->SetFillStyle(1001);
   // gmpT_444->SetFillColor(kBlack);  
   gmpT_444->SetFillColorAlpha(kRed-9, 0.4);
    gmpT_444->SetMarkerSize(1.2);
   gmpT_444->SetMarkerStyle(20);
   gmpT_444->SetMarkerColor(kRed);
   gmpT_444->SetLineColor(kRed);


   gmpT_1->Draw("PSAMEZA");
   gmpT_111->Draw("2SAME");                                                                                                            
   gmpT_11->Draw("5SAME");
   gmpT_1->Draw("PSAMEZ"); 
   
   gmpT_333->Draw("2SAME");                                                                                                            
   gmpT_33->Draw("5SAME");  
   gmpT_3->Draw("PSAMEZ");
   
   gmpT_222->Draw("2SAME");
   gmpT_22->Draw("5SAME");  
   gmpT_2->Draw("PSAMEZ");  
   
   // gmpT_pp5TeV_1->Draw("PSAME");
   //gmpT_pp5TeV_2->Draw("5SAME");
   //gmpT_pp5TeV_1->Draw("PSAME");

   gmpT_444->Draw("2SAME");
   //gmpT_44->Draw("5SAME");  
   gmpT_44->Draw("5SAME");
   // gmpT_44->Draw("EX0SAME");
  
   gmpT_4->Draw("PSAMEZ");


   gdNdy_1->GetXaxis()->SetTitle("#LTd#it{N}_{ch}/d#it{#eta}#GT_{|#it{#eta}_{lab}| < 0.5}"); 
   gmpT_1->GetXaxis()->SetTitle("#LTd#it{N}_{ch}/d#it{#eta}#GT_{|#it{#eta}_{lab}| < 0.5}"); 

   gdNdy_2->GetYaxis()->SetTitle("d#it{N}/d#it{y}");
   gmpT_2->GetYaxis()->SetTitle("#LT#it{p}_{T}#GT (GeV/#it{c})");
   
   gdNdy_1->GetYaxis()->SetTitle("d#it{N}/d#it{y}");
   gmpT_1->GetYaxis()->SetTitle("#LT#it{p}_{T}#GT (GeV/#it{c})");
   
   gmpT_2->GetXaxis()->SetTitle("#LTd#it{N}_{ch}/d#it{#it{#eta}_{lab}}#GT");
   gdNdy_2->GetXaxis()->SetTitle("#LTd#it{N}_{ch}/d#it{#it{#eta}_{lab}}#GT");
   
  
  
   
   
  /*  
      TLegend *lp1 = DrawLegend(0.5719064,0.3537653,0.7525084,0.7232925);
      lp1->AddEntry((TObject*)0,"#bf{ALICE Preliminary}","");
      lp1->AddEntry(gmpT_2,"pp, #sqrt{#it{s}} = 13 TeV","lp");
      lp1->AddEntry(gmpT_1,"pp, #sqrt{#it{s}} = 7 TeV","lp");
      lp1->AddEntry(gmpT_3,"p-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV","lp");
      lp1->AddEntry((TObject*)0,"K*^{0}(#bar{K}*^{0}) #rightarrow #pi^{-}K^{+}(#pi^{+}K^{-})","");
      lp1->AddEntry((TObject*)0,"|#it{y}|<0.5","");
      lp1->Draw();
  */     
   
    TLegend *lp1 = DrawLegend(0.22,0.68,0.40,0.95);
   lp1->AddEntry(gmpT_3,"p-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV (EPJC 76 (2016) 245)","lp");
    lp1->AddEntry((TObject*)0,"#bf{ALICE Preliminary}","");
    lp1->AddEntry(gmpT_4,"p-Pb, #sqrt{#it{s}_{NN}} = 8.16 TeV ","lp");
     lp1->AddEntry(gmpT_2,"pp, #sqrt{#it{s}} = 13 TeV","lp");
    lp1->AddEntry(gmpT_1,"pp, #sqrt{#it{s}} = 7 TeV","lp");
    //lp1->AddEntry(gmpT_pp5TeV_1,"pp, #sqrt{#it{s}} = 5.02 TeV","lp");
    lp1->AddEntry((TObject*)0,"V0 Multiplicity Event Classes","");
    lp1->Draw();

    float  lx=4.24; float ly=1.45;
    TLatex* t3=new TLatex(lx,ly,"K*^{0}");
    t3->SetTextAlign(13);
    t3->SetTextSize(0.08);
    t3->SetTextFont(42);
    t3->Draw();
    
    
    TLatex *texx = new TLatex(8.329029,0.96,"V0 Multiplicity Event Classes");
    texx->SetTextAlign(13);
    texx->SetTextFont(42);
    texx->SetTextSize(0.035);
    texx->SetLineWidth(2);
    //  texx->Draw();
    
    TLatex *tex11  = new TLatex(11.06,0.88,"Uncertainties: stat.(bars), sys.(boxes), ");
    tex11->SetTextAlign(13);
    tex11->SetTextFont(42);
    tex11->SetTextSize(0.035);
    tex11->SetLineWidth(2);
    tex11->Draw();
    
    TLatex *tex22  = new TLatex(11.06,0.8,"uncor. sys. (shaded boxes) ");
    tex22->SetTextAlign(13);
    tex22->SetTextFont(42);
    tex22->SetTextSize(0.035);
    tex22->SetLineWidth(2);
    tex22->Draw();

     cdNdY_2->SaveAs("dNdy_pPb8TeV_kstar.gif");
   cdNdY_2->Print("dNdy_pPb8TeV_kstar.eps");
   cdNdY_2->Print("dNdy_pPb8TeV_kstar.png");
   cdNdY_2->Print("dNdy_pPb8TeV_kstar.root");
   cdNdY_2->Print("dndy.pdf");

     
   

   cmpT_2->SaveAs("meanpT_pPb8TeV_kstar.gif");
   cmpT_2->Print("meanpT_pPb8TeV_kstar.eps");
   cmpT_2->Print("meanpT_pPb8TeV_kstar.png");
   cmpT_2->Print("meanpT_pPb8TeV_kstar.root");
   cmpT_2->Print("meanpT.pdf");


    
    
}

//==================================================================//
TLegend *DrawLegend(Double_t x1,Double_t y1,Double_t x2,Double_t y2)
{
  TLegend *legend = new TLegend(x1,y1,x2,y2);
  legend->SetTextFont(42);
  legend->SetFillColor(0);
  legend->SetTextSize(0.035);
  legend->SetLineColor(0);
  legend->SetShadowColor(0);
  //legend->AddEntry(gr1,"(0 - 100) %","p");                                                                                                  
  return legend;
}

