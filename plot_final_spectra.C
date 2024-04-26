void plot_final_spectra()
{
  TCanvas *c1 = new TCanvas("c1", "c1");
  c1->SetTickx(1);
  c1->SetTicky(1); 
  //  gStyle->SetPadTicksy(1);
  gStyle->SetOptFit(1); // Removing Stat table 
  gStyle->SetOptStat(0);
  gStyle->SetLineWidth(2);
  //c1->Range(389.1538,-1.262158,814.5897,3.273017);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetLeftMargin(0.1482787);
  c1->SetBottomMargin(0.1607143);

// ***************************************************** pp13TeV 2020 ***************************************************




  TFile *pp13TeV2020=new TFile("/home/navneet/Music/TGraph/pp13TeV/HEPData-ins1784041-v1-Table_17.root","READ");

  TDirectoryFile *dire_2020;

  dire_2020=  (TDirectoryFile*)pp13TeV2020->Get(Form("Table %i",17));
  dire_2020->ls();

  TH1F * data; TH1F * hstat; TH1F * hsyst;

  data = (TH1F*)dire_2020->Get("Hist1D_y2;1");
  hstat = (TH1F*)dire_2020->Get("Hist1D_y2_e1");
  hsyst = (TH1F*)dire_2020->Get("Hist1D_y2_e2");

  int n = data->GetNbinsX() +1,j=0;
  //Int_t n = 10, j=0;
  double x[10]={26.02,20.02,16.17,13.77,12.04,10.02,7.94,6.32,4.50,2.55}, y[10],errx[10]={0.35,0.27,0.22,0.19,0.17,0.14,0.11,0.09,0.07,0.04},err2[10],err1[10];
  while (n >0){n--;
	if (data->GetBinContent(n) ==0){continue;}
		y[j]=data->GetBinContent(n);
		err1[j]= hstat->GetBinContent(n);
		err2[j]= hsyst->GetBinContent(n);
	
		j++;
		//errx[j]=0.0;
		//cout<<y[j]<<" +-"<<err1[j] <<endl;
  }
TGraphErrors *gr = new TGraphErrors();
TGraphErrors *grsys = new TGraphErrors();

  for (int i =0; i< 10; i++){
       	gr->SetPoint(i,x[i],y[i]);
	gr->SetPointError(i,errx[i],err1[i]);
	grsys->SetPoint(i,x[i],y[i]);
	grsys->SetPointError(i,errx[i],err2[i]);	
  }

//Error
c1->SetLogx();
gr->SetMarkerStyle(8);
gr->SetMarkerColor(41);
gr->SetLineColor(41);
gr->SetMarkerSize(1.4);

  gr->GetYaxis()->SetTitleSize(0.06);
  gr->GetYaxis()->SetLabelSize(0.05);
  gr->GetYaxis()->SetTitleOffset(0.85);
  gr->GetXaxis()->SetTitleSize(0.06);  
  gr->GetXaxis()->SetLabelSize(0.05);
  gr->GetXaxis()->SetNdivisions(508);
  gr->GetYaxis()->SetNdivisions(508);
  gr->GetYaxis()->SetTitle("p + #bar{p}");
  gr->GetXaxis()->SetTitle("<dN_{ch}/d#eta>_{|#eta|<0.5}");

  gr->SetMarkerSize(1.4);
  gr->SetMarkerStyle(8);
  gr->SetMarkerColor(41);
  gr->SetLineColor(41);
 
  grsys->SetLineColor(41);
  grsys->SetFillStyle(0);
  grsys->SetFillColor(0);
  grsys->SetLineWidth(2);
  

  gr->SetMinimum(0.0);
  gr->SetMaximum(0.1);
  gr->GetXaxis()->SetLimits(0.5,3000);
//  gr->GetYaxis()->SetLimits(0,2);


  c1->cd();

//***************************************** pp7TeV ***************************************************

  TFile *pp7TeV2019=new TFile("/home/navneet/Music/TGraph/pp7TeV/HEPData-ins1684320-v1-Table_93.root","READ");
  TDirectoryFile *dire_2019;

  dire_2019=  (TDirectoryFile*)pp7TeV2019->Get(Form("Table %i",93));

//  dire_2019->ls();
  TH1F * data2019; TH1F * hstat2019; TH1F * hsyst2019;

  data2019 = (TH1F*)dire_2019->Get("Hist1D_y1;1");
  hstat2019 = (TH1F*)dire_2019->Get("Hist1D_y1_e1");
  hsyst2019 = (TH1F*)dire_2019->Get("Hist1D_y1_e2");

  int n2019 = data2019->GetNbinsX() +1,j2019=0;
  //Int_t n = 10, j=0;
  double x2019[10]={21.03,16.5,13.5,11.5,10.1,8.45,6.72,5.40,3.90,2.26}, y2019[10],errx2019[10]={0.6,0.5,0.4,0.3,0.3,0.25,0.21,0.17,0.14,0.12},err22019[10],err12019[10];
  while( n2019>0){n2019--;
	if (data2019->GetBinContent(n2019) ==0){continue;}
		y2019[j2019]=data2019->GetBinContent(n2019);
		err12019[j2019]= hstat2019->GetBinContent(n2019);
		err22019[j2019]= hsyst2019->GetBinContent(n2019);

		j2019++;
		//errx[j]=0.0;
		//cout<<y[j]<<" +-"<<err1[j] <<endl;
  }
TGraphErrors *gr2019 = new TGraphErrors();
TGraphErrors *grsys2019 = new TGraphErrors();

  for (int i =0; i< 10; i++){
       	gr2019->SetPoint(i,x2019[i],y2019[i]);
	gr2019->SetPointError(i,errx2019[i],err12019[i]);
	grsys2019->SetPoint(i,x2019[i],y2019[i]);
	grsys2019->SetPointError(i,errx2019[i],err22019[i]);	
  }


//Error
gr2019->SetMarkerStyle(8);
gr2019->SetMarkerColor(kBlue);
gr2019->SetLineColor(kBlue);
gr2019->SetMarkerSize(1.4);

  gr2019->GetYaxis()->SetTitleSize(0.06);
  gr2019->GetYaxis()->SetLabelSize(0.05);
  gr2019->GetYaxis()->SetTitleOffset(0.85);
  gr2019->GetXaxis()->SetTitleSize(0.06);  
  gr2019->GetXaxis()->SetLabelSize(0.05);
  gr2019->GetXaxis()->SetNdivisions(508);
  gr2019->GetYaxis()->SetNdivisions(508);

  gr2019->SetMarkerSize(1.4);
  gr2019->SetMarkerStyle(8);
  gr2019->SetMarkerColor(kBlue);
  gr2019->SetLineColor(kBlue);
 
  grsys2019->SetLineColor(kBlue);
  grsys2019->SetFillStyle(0);
  grsys2019->SetFillColor(0);
  grsys2019->SetLineWidth(2);
  gr2019->SetMinimum(0.0);
  gr2019->SetMaximum(0.1);
  gr2019->GetXaxis()->SetLimits(0.5,3000);
 

//***************************************** p-Pb 5.02 TeV ***************************************************

  TFile *pPb5TeV2014=new TFile("/home/navneet/Music/TGraph/pPb5TeV/HEPData-ins1244523-v2-Table_22.root","READ");
  TDirectoryFile *dire_2014;

  dire_2014=  (TDirectoryFile*)pPb5TeV2014->Get(Form("Table %i",22));

//  dire_2014->ls();

  TH1F * data2014; TH1F * hstat2014; TH1F * hsyst2014;

  data2014 = (TH1F*)dire_2014->Get("Hist1D_y2;1");
  hstat2014 = (TH1F*)dire_2014->Get("Hist1D_y2_e1");
  hsyst2014 = (TH1F*)dire_2014->Get("Hist1D_y2_e2");

  int n2014 = data2014->GetNbinsX(),j2014=0;
  //Int_t n = 10, j=0;
  double x2014[7]={45,36.2,30.5,23.2,16.1,9.8,4.4}, y2014[7],errx2014[7]={1,0.8,0.7,0.5,0.4,0.2,0.1},err22014[7],err12014[7];
  for (int i =1; i <=n2014; i++){
	if (data2014->GetBinContent(i) ==0){continue;}
		y2014[j2014]=data2014->GetBinContent(i);
		err12014[j2014]= hstat2014->GetBinContent(i);
		err22014[j2014]= hsyst2014->GetBinContent(i);

		j2014++;
		//errx[j]=0.0;
		//cout<<y[j]<<" +-"<<err1[j] <<endl;
  }
TGraphErrors *gr2014 = new TGraphErrors();
TGraphErrors *grsys2014 = new TGraphErrors();

  for (int i =0; i< 7; i++){
       	gr2014->SetPoint(i,x2014[i],y2014[i]);
	gr2014->SetPointError(i,errx2014[i],err12014[i]);
	grsys2014->SetPoint(i,x2014[i],y2014[i]);
	grsys2014->SetPointError(i,errx2014[i],err22014[i]);	
  }
//Error
gr2014->SetMarkerStyle(8);
gr2014->SetMarkerColor(kGreen);
gr2014->SetLineColor(kGreen);
gr2014->SetMarkerSize(1.4);

  gr2014->GetYaxis()->SetTitleSize(0.06);
  gr2014->GetYaxis()->SetLabelSize(0.05);
  gr2014->GetYaxis()->SetTitleOffset(0.85);
  gr2014->GetXaxis()->SetTitleSize(0.06);  
  gr2014->GetXaxis()->SetLabelSize(0.05);
  gr2014->GetXaxis()->SetNdivisions(508);
  gr2014->GetYaxis()->SetNdivisions(508);

  gr2014->SetMarkerSize(1.4);
  gr2014->SetMarkerStyle(8);
  gr2014->SetMarkerColor(kGreen);
  gr2014->SetLineColor(kGreen);
 
  grsys2014->SetLineColor(kGreen);
  grsys2014->SetFillStyle(0);
  grsys2014->SetFillColor(0);
  grsys2014->SetLineWidth(2);
  gr2014->SetMinimum(0.0);
  gr2014->SetMaximum(0.1);
  gr2014->GetXaxis()->SetLimits(0.5,3000);
 

//***************************************** Pb-Pb 2.76 TeV ***************************************************

  TFile *PbPb2TeV2013=new TFile("/home/navneet/Music/TGraph/PbPb2TeV/HEPData-ins1222333-v1-Table_36.root","READ");
  TDirectoryFile *dire_2013;

  dire_2013=  (TDirectoryFile*)PbPb2TeV2013->Get(Form("Table %i",36));

//  dire_2013->ls();
  TH1F * data2013; TH1F * hstat2013; TH1F * hsyst2013;

  data2013 = (TH1F*)dire_2013->Get("Hist1D_y2;1");
  hstat2013 = (TH1F*)dire_2013->Get("Hist1D_y2_e1");
  hsyst2013 = (TH1F*)dire_2013->Get("Hist1D_y2_e2");

  int n2013 = data2013->GetNbinsX(),j2013=0;
  //Int_t n = 10, j=0;
  double x2013[10]={1601,1294,966,649,426,261,149,76,35,13.4}, y2013[10],errx2013[10]={60,49,37,23,15,9,6,4,2,1.6},err22013[10],err12013[10];
  for (int i =1; i <=n2013; i++){
	if (data2013->GetBinContent(i) ==0){continue;}
		y2013[j2013]=data2013->GetBinContent(i);
		err12013[j2013]= hstat2013->GetBinContent(i);
		err22013[j2013]= hsyst2013->GetBinContent(i);
		j2013++;
		//errx[j]=0.0;
		//cout<<y[j]<<" +-"<<err1[j] <<endl;
  }
TGraphErrors *gr2013 = new TGraphErrors();
TGraphErrors *grsys2013 = new TGraphErrors();

  for (int i =0; i< 10; i++){
       	gr2013->SetPoint(i,x2013[i],y2013[i]);
	gr2013->SetPointError(i,errx2013[i],err12013[i]);
	grsys2013->SetPoint(i,x2013[i],y2013[i]);
	grsys2013->SetPointError(i,errx2013[i],err22013[i]);	
  }


//Error
gr2013->SetMarkerStyle(8);
gr2013->SetMarkerColor(kBlack);
gr2013->SetLineColor(kBlack);
gr2013->SetMarkerSize(1.4);

  gr2013->GetYaxis()->SetTitleSize(0.06);
  gr2013->GetYaxis()->SetLabelSize(0.05);
  gr2013->GetYaxis()->SetTitleOffset(0.85);
  gr2013->GetXaxis()->SetTitleSize(0.06);  
  gr2013->GetXaxis()->SetLabelSize(0.05);
  gr2013->GetXaxis()->SetNdivisions(508);
  gr2013->GetYaxis()->SetNdivisions(508);

  gr2013->SetMarkerSize(1.4);
  gr2013->SetMarkerStyle(8);
  gr2013->SetMarkerColor(kBlack);
  gr2013->SetLineColor(kBlack);
 
  grsys2013->SetLineColor(kBlack);
  grsys2013->SetFillStyle(0);
  grsys2013->SetFillColor(0);
  grsys2013->SetLineWidth(2);
  gr2013->SetMinimum(0.0);
  gr2013->SetMaximum(0.1);
  gr2013->GetXaxis()->SetLimits(0.5,3000);
 
//***************************************** Pb-Pb 5.02 TeV ***************************************************

  TFile *PbPb5TeV2020b=new TFile("/home/navneet/Music/TGraph/PbPb5TeV/HEPData-ins1759506-v1-Table_13.root","READ");
  TDirectoryFile *dire_2020b;

  dire_2020b=  (TDirectoryFile*)PbPb5TeV2020b->Get(Form("Table %i",13));

//  dire_2020b->ls();
  TH1F * data2020b; TH1F * hstat2020b; TH1F * hsyst2020b;

  data2020b = (TH1F*)dire_2020b->Get("Hist1D_y2;1");
  hstat2020b = (TH1F*)dire_2020b->Get("Hist1D_y2_e1");
  hsyst2020b = (TH1F*)dire_2020b->Get("Hist1D_y2_e2");

  int n2020b = data2020b->GetNbinsX(),j2020b=0;
  //Int_t n = 10, j=0;
  double x2020b[10]={1943,1587,1180,786,512,318,183,96.3,44.9,17.5}, y2020b[10],errx2020b[10]={56,47,31,20,15,12,8,5.8,3.4,1.8},err22020b[10],err12020b[10];
  for (int i =1; i <=n2020b; i++){
	if (data2020b->GetBinContent(i) ==0){continue;}
		y2020b[j2020b]=data2020b->GetBinContent(i);
		err12020b[j2020b]= hstat2020b->GetBinContent(i);
		err22020b[j2020b]= hsyst2020b->GetBinContent(i);
		j2020b++;
		//errx[j]=0.0;
		//cout<<y[j]<<" +-"<<err1[j] <<endl;
  }
TGraphErrors *gr2020b = new TGraphErrors();
TGraphErrors *grsys2020b = new TGraphErrors();

  for (int i =0; i< 10; i++){
       	gr2020b->SetPoint(i,x2020b[i],y2020b[i]);
	gr2020b->SetPointError(i,errx2020b[i],err12020b[i]);
	grsys2020b->SetPoint(i,x2020b[i],y2020b[i]);
	grsys2020b->SetPointError(i,errx2020b[i],err22020b[i]);	
  }


//Error
gr2020b->SetMarkerStyle(8);
gr2020b->SetMarkerColor(6);
gr2020b->SetLineColor(6);
gr2020b->SetMarkerSize(1.4);

  gr2020b->GetYaxis()->SetTitleSize(0.06);
  gr2020b->GetYaxis()->SetLabelSize(0.05);
  gr2020b->GetYaxis()->SetTitleOffset(0.85);
  gr2020b->GetXaxis()->SetTitleSize(0.06);  
  gr2020b->GetXaxis()->SetLabelSize(0.05);
  gr2020b->GetXaxis()->SetNdivisions(508);
  gr2020b->GetYaxis()->SetNdivisions(508);

  gr2020b->SetMarkerSize(1.4);
  gr2020b->SetMarkerStyle(8);
  gr2020b->SetMarkerColor(6);
  gr2020b->SetLineColor(6);
 
  grsys2020b->SetLineColor(6);
  grsys2020b->SetFillStyle(0);
  grsys2020b->SetFillColor(0);
  grsys2020b->SetLineWidth(2);
  gr2020b->SetMinimum(0.0);
  gr2020b->SetMaximum(0.1);
  gr2020b->GetXaxis()->SetLimits(0.5,3000);
 

c1->cd();

	gr->Draw("PSAMEA");
	grsys->Draw("5SAME");


	gr2014->Draw("PSAMEZ");
	grsys2014->Draw("5SAME");
	gr2013->Draw("PSAMEZ");
	grsys2013->Draw("5SAME");


	gr2020b->Draw("PSAMEZ");
	grsys2020b->Draw("5SAME");



       TLegend *legend3= new TLegend(0.2,0.2,0.8,0.4);
       legend3->SetNColumns(2);
       legend3->AddEntry(gr,"#splitline{Eur.Phys.J.C(2020)80:693}{pp, #sqrt{s}= 13 TeV}","fp");
       legend3->AddEntry(gr2019,"#splitline{Eur.Phys.J.C 99(2),024906 (2019)}{pp, #sqrt{s}= 7 TeV}","fp");
       legend3->AddEntry(gr2014,"#splitline{Phys. Let. B 728 (2014) 25}{p-Pb, #sqrt{s_{NN}}= 5.02 TeV}","fp");
       legend3->AddEntry(gr2013,"#splitline{Phys. Rev. C 88, 044910 (2013)}{Pb-Pb, #sqrt{s_{NN}}= 2.76 TeV}","fp");
       legend3->AddEntry(gr2020b,"#splitline{Phys. Rev. C 101(4), 044907 (2020)}{Pb-Pb, #sqrt{s_{NN}}= 5.02 TeV}","fp");

       legend3->SetTextFont(42);
       legend3->SetBorderSize(0);



        legend3->Draw("same");

}


