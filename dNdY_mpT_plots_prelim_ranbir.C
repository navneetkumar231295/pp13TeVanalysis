void dNdY_mpT_plots_prelim_ranbir()
{
  const Int_t m=9;//v0m
  const Int_t mm=9;//refMult
   const Int_t m1=9;//v0m
  //=======================// V0M //===================================//
  Double_t dndy[m], dndy_err_stat[m], dndy_err_syst[m],  dndy_err_uncorr_syst[m];
  Double_t mNch[m],  mNchErr[m],mNch3[m],mNchErr3[m];

  Double_t dndy1[m], dndy_err_stat1[m], dndy_err_syst1[m],  dndy_err_uncorr_syst1[m];
  Double_t mNch1[m],  mNchErr1[m];
  
  Double_t dndy2[m], dndy_err_stat2[m], dndy_err_syst2[m],  dndy_err_uncorr_syst2[m];
  Double_t mNch2[m],  mNchErr2[m];

  Double_t  dndy3[m], dndy_err_stat3[m],dndy_err_syst3[m],dndy_err_uncorr_syst3[m];

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

  TGraphErrors *gdNdy_4 = new TGraphErrors();
  TGraphErrors *gdNdy_44 = new TGraphErrors();
  TGraphErrors *gdNdy_444 = new TGraphErrors();

 

  //===========// pp@5.02 TeV///==============//
  TGraphErrors *gdNdy_pp5TeV_1 = new TGraphErrors(10);
  //=========================================//



  

  gdNdy_1->SetLineWidth(2);
  gdNdy_11->SetLineWidth(2);
  gdNdy_11->SetLineColor(kBlue);

     /*********************8 Tev******************/
  gdNdy_4->SetLineWidth(2);
  gdNdy_44->SetLineWidth(2);
  gdNdy_44->SetLineColor(9);

  gdNdy_pp5TeV_1->SetMarkerSize(1.4);
  gdNdy_pp5TeV_1->SetMarkerColor(kRed);
  gdNdy_pp5TeV_1->SetLineColor(kRed);
  gdNdy_pp5TeV_1->SetMarkerSize(1.4);
  gdNdy_pp5TeV_1->SetMarkerStyle(21);

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
 

    }

      
    
  //-----------// pp@5 TeV //-------------------//
  for (Int_t i=0; i<10; i++)
    {
      gdNdy_pp5TeV_1->SetPoint(i, MNch_pp5TeV[i], dNdY_pp5TeV[i]);
      gdNdy_pp5TeV_1->SetPointError(i, MNchErr_pp5TeV[i], dNdY_Err_Stat_pp5TeV[i]);
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

 

    gdNdy_1->Draw("PSAMEA");
//   gdNdy_111->Draw("2SAME");          
   gdNdy_11->Draw("5SAME");
//   gdNdy_1->Draw("PSAMEZ");
  
  

  
//   gdNdy_444->Draw("2SAME");                                                                                              
//    gdNdy_44->Draw("5SAME");
//      gdNdy_4->Draw("PSAMEZ");

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

