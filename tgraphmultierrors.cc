// @(#)root/hist:$Id$
// Author: Simon Spies 18/02/19

/*************************************************************************
 * Copyright (C) 2018-2019, Simon Spies.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * Based on the ROOT class TGraphAsymmErrors                             *
 *************************************************************************/

#include "TROOT.h"
#include "TClass.h"
#include "TStyle.h"
#include "TVirtualPad.h"
#include "TEfficiency.h"
#include "Riostream.h"

#include "TObject.h"
#include "TNamed.h"
#include "TAttLine.h"
#include "TAttFill.h"
#include "TAttMarker.h"

#include "TVector.h"
#include "TH1.h"
#include "TF1.h"
#include "TMath.h"
#include "TGaxis.h"
#include "TVirtualGraphPainter.h"
#include "TGraphPainter.h"
#include "TBox.h"
#include "TArrow.h"
#include "TRegexp.h"
#include "Math/QuantFuncMathCore.h"

#include "tgraphmultierrors.h"

ClassImp(TGraphMultiErrors)

/** \class TGraphMultiErrors
 TGraph with asymmetric error bars and multiple y error dimensions.
 
 The TGraphAsymmErrors painting is currently performed by its functions TGraphMultiErrors::Paint,
 TGraphMultiErrors::PaintReverse and TGraphMultiErrors::PaintGraphMultiErrors. These are supposed to be included in
 the TGraphPainter class if this class should become part of ROOT.
 All drawing options of TGraphAsymmErrors are available.
 For more information see the function TGraphMultiErrors::PaintGraphMultiErrors.
*/


///////////////////////////////////////////////////////////////////////////////
/// TGraphMultiErrors default constructor.

TGraphMultiErrors::TGraphMultiErrors() : TGraph(), fNErrorDimensions(0), fExL(NULL), fExH(NULL), fEyL(NULL), fEyH(NULL), fEyLSum(NULL), fEyHSum(NULL), fSumErrorsMode(TGraphMultiErrors::kOnlyFirst), fAttFill(NULL), fAttLine(NULL) {}

////////////////////////////////////////////////////////////////////////////////
/// TGraphMultiErrors normal constructor.
///
/// the arrays are preset to zero

TGraphMultiErrors::TGraphMultiErrors(Int_t n, Int_t dim) : TGraph(n), fNErrorDimensions(dim), fSumErrorsMode(TGraphMultiErrors::kOnlyFirst) {
    if (!CtorAllocate())
	return;

    FillZero(0, fNpoints);

    fAttFill = new TAttFill[fNErrorDimensions];
    fAttLine = new TAttLine[fNErrorDimensions];
}

////////////////////////////////////////////////////////////////////////////////
/// TGraphMultiErrors normal constructor with a single y error dimension.
///
/// if exL,H or eyL,H are null, the corresponding arrays are preset to zero

TGraphMultiErrors::TGraphMultiErrors(Int_t n, const Float_t* x, const Float_t* y, const Float_t* exL, const Float_t* exH, const Float_t* eyL, const Float_t* eyH, Int_t m) : TGraph(n, x, y), fNErrorDimensions(1), fEyLSum(NULL), fEyHSum(NULL), fSumErrorsMode(m) {
    if(!CtorAllocate())
	return;

    for (Int_t i = 0; i < n; i++) {
	if (exL) fExL[i] = exL[i];
	else     fExL[i] = 0.;

	if (exH) fExH[i] = exH[i];
	else     fExH[i] = 0.;

	if (eyL) fEyL[0][i] = eyL[i];
	else     fEyL[0][i] = 0.;

	if (eyH) fEyH[0][i] = eyH[i];
	else     fEyH[0][i] = 0.;
    }

    CalcYErrorSum();

    fAttFill = new TAttFill[fNErrorDimensions];
    fAttLine = new TAttLine[fNErrorDimensions];
}

////////////////////////////////////////////////////////////////////////////////
/// TGraphMultiErrors normal constructor with a single y error dimension.
///
/// if exL,H or eyL,H are null, the corresponding arrays are preset to zero

TGraphMultiErrors::TGraphMultiErrors(Int_t n, const Double_t* x, const Double_t* y, const Double_t* exL, const Double_t* exH, const Double_t* eyL, const Double_t* eyH, Int_t m) : TGraph(n, x, y), fNErrorDimensions(1), fEyLSum(NULL), fEyHSum(NULL), fSumErrorsMode(m) {
    if (!CtorAllocate())
	return;

    n = fNpoints * sizeof(Double_t);

    if (exL) memcpy(fExL, exL, n);
    else     memset(fExL,   0, n);

    if (exH) memcpy(fExH, exH, n);
    else     memset(fExH,   0, n);

    if (eyL) memcpy(fEyL[0], eyL, n);
    else     memset(fEyL[0],   0, n);

    if (eyH) memcpy(fEyH[0], eyH, n);
    else     memset(fEyH[0],   0, n);

    CalcYErrorSum();

    fAttFill = new TAttFill[fNErrorDimensions];
    fAttLine = new TAttLine[fNErrorDimensions];
}

////////////////////////////////////////////////////////////////////////////////
/// TGraphMultiErrors normal constructor with a multiple y error dimensions.
///
/// if exL,H or eyL,H are null, the corresponding arrays are preset to zero

TGraphMultiErrors::TGraphMultiErrors(Int_t n, Int_t dim, const Float_t* x, const Float_t* y, const Float_t* exL, const Float_t* exH, Float_t** eyL, Float_t** eyH, Int_t m) : TGraph(n, x, y), fNErrorDimensions(dim), fEyLSum(NULL), fEyHSum(NULL), fSumErrorsMode(m) {
    if(!CtorAllocate())
	return;

    for (Int_t i = 0; i < n; i++) {
	if (exL) fExL[i] = exL[i];
	else     fExL[i] = 0.;

	if (exH) fExH[i] = exH[i];
	else     fExH[i] = 0.;

	for (Int_t j = 0; j < dim; j++) {
	    if (eyL) fEyL[j][i] = eyL[j][i];
	    else     fEyL[j][i] = 0.;

	    if (eyH) fEyH[j][i] = eyH[j][i];
	    else     fEyH[j][i] = 0.;
	}
    }

    CalcYErrorSum();

    fAttFill = new TAttFill[fNErrorDimensions];
    fAttLine = new TAttLine[fNErrorDimensions];
}

////////////////////////////////////////////////////////////////////////////////
/// TGraphMultiErrors normal constructor with a multiple y error dimensions.
///
/// if exL,H or eyL,H are null, the corresponding arrays are preset to zero

TGraphMultiErrors::TGraphMultiErrors(Int_t n, Int_t dim, const Double_t* x, const Double_t* y, const Double_t* exL, const Double_t* exH, Double_t** eyL, Double_t** eyH, Int_t m) : TGraph(n, x, y), fNErrorDimensions(dim), fEyLSum(NULL), fEyHSum(NULL), fSumErrorsMode(m) {
    if (!CtorAllocate())
	return;

    n = fNpoints * sizeof(Double_t);

    if (exL) memcpy(fExL, exL, n);
    else     memset(fExL,   0, n);

    if (exH) memcpy(fExH, exH, n);
    else     memset(fExH,   0, n);

    for (Int_t j = 0; j < fNErrorDimensions; j++) {
	if (eyL) memcpy(fEyL[j], eyL[j], n);
	else     memset(fEyL[j],      0, n);

	if (eyH) memcpy(fEyH[j], eyH[j], n);
	else     memset(fEyH[j],      0, n);
    }

    CalcYErrorSum();

    fAttFill = new TAttFill[fNErrorDimensions];
    fAttLine = new TAttLine[fNErrorDimensions];
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor with six vectors of floats in input and a single y error dimension
/// A grapherrors is built with the X coordinates taken from tvX and Y coord from tvY
/// and the errors from vectors tvExL/H and tvEyL/H.
/// The number of points in the graph is the minimum of number of points
/// in tvX and tvY.

TGraphMultiErrors::TGraphMultiErrors(const TVectorF& tvX, const TVectorF& tvY, const TVectorF& tvExL, const TVectorF& tvExH, const TVectorF& tvEyL, const TVectorF& tvEyH, Int_t m) : TGraph(), fNErrorDimensions(1), fEyLSum(NULL), fEyHSum(NULL), fSumErrorsMode(m) {
    fNpoints = TMath::Min(tvX.GetNrows(), tvY.GetNrows());

    if (!TGraph::CtorAllocate())
	return;

    if (!CtorAllocate())
	return;

    Int_t itvXL   = tvX.GetLwb();
    Int_t itvYL   = tvY.GetLwb();
    Int_t itvExLL = tvExL.GetLwb();
    Int_t itvExHL = tvExH.GetLwb();
    Int_t itvEyLL = tvEyL.GetLwb();
    Int_t itvEyHL = tvEyH.GetLwb();

    for (Int_t i = 0; i < fNpoints; i++) {
	fX[i]      = tvX(i + itvXL);
	fY[i]      = tvY(i + itvYL);
        fExL[i]    = tvExL(i + itvExLL);
	fExH[i]    = tvExH(i + itvExHL);
	fEyL[0][i] = tvEyL(i + itvEyLL);
	fEyH[0][i] = tvEyH(i + itvEyHL);
    }

    CalcYErrorSum();

    fAttFill = new TAttFill[fNErrorDimensions];
    fAttLine = new TAttLine[fNErrorDimensions];
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor with six vectors of doubles in input and a single y error dimension
/// A grapherrors is built with the X coordinates taken from tvX and Y coord from tvY
/// and the errors from vectors tvExL/H and tvEyL/H.
/// The number of points in the graph is the minimum of number of points
/// in tvX and tvY.

TGraphMultiErrors::TGraphMultiErrors(const TVectorD& tvX, const TVectorD& tvY, const TVectorD& tvExL, const TVectorD& tvExH, const TVectorD& tvEyL, const TVectorD& tvEyH, Int_t m) : TGraph(), fNErrorDimensions(1), fEyLSum(NULL), fEyHSum(NULL), fSumErrorsMode(m) {
    fNpoints = TMath::Min(tvX.GetNrows(), tvY.GetNrows());

    if (!TGraph::CtorAllocate())
	return;

    if (!CtorAllocate())
	return;

    Int_t itvXL   = tvX.GetLwb();
    Int_t itvYL   = tvY.GetLwb();
    Int_t itvExLL = tvExL.GetLwb();
    Int_t itvExHL = tvExH.GetLwb();
    Int_t itvEyLL = tvEyL.GetLwb();
    Int_t itvEyHL = tvEyH.GetLwb();

    for (Int_t i = 0; i < fNpoints; i++) {
	fX[i]      = tvX(i + itvXL);
	fY[i]      = tvY(i + itvYL);
        fExL[i]    = tvExL(i + itvExLL);
	fExH[i]    = tvExH(i + itvExHL);
	fEyL[0][i] = tvEyL(i + itvEyLL);
	fEyH[0][i] = tvEyH(i + itvEyHL);
    }

    CalcYErrorSum();

    fAttFill = new TAttFill[fNErrorDimensions];
    fAttLine = new TAttLine[fNErrorDimensions];
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor with multiple vectors of floats in input and multiple y error dimensions
/// A grapherrors is built with the X coordinates taken from tvX and Y coord from tvY
/// and the errors from vectors tvExL/H and tvEyL/H[yErrorDimension].
/// The number of points in the graph is the minimum of number of points
/// in tvX and tvY.

TGraphMultiErrors::TGraphMultiErrors(Int_t dim, const TVectorF& tvX, const TVectorF& tvY, const TVectorF& tvExL, const TVectorF& tvExH, const TVectorF* tvEyL, const TVectorF* tvEyH, Int_t m) : TGraph(), fNErrorDimensions(dim), fEyLSum(NULL), fEyHSum(NULL), fSumErrorsMode(m) {
    fNpoints = TMath::Min(tvX.GetNrows(), tvY.GetNrows());

    if (!TGraph::CtorAllocate())
	return;

    if (!CtorAllocate())
	return;

    Int_t itvXL   = tvX.GetLwb();
    Int_t itvYL   = tvY.GetLwb();
    Int_t itvExLL = tvExL.GetLwb();
    Int_t itvExHL = tvExH.GetLwb();

    for (Int_t i = 0; i < fNpoints; i++) {
	fX[i]      = tvX(i + itvXL);
	fY[i]      = tvY(i + itvYL);
        fExL[i]    = tvExL(i + itvExLL);
	fExH[i]    = tvExH(i + itvExHL);

        for (Int_t j = 0; j < dim; j++) {
	    fEyL[j][i] = tvEyL[j](i + tvEyL[j].GetLwb());
	    fEyH[j][i] = tvEyH[j](i + tvEyH[j].GetLwb());
	}
    }

    CalcYErrorSum();

    fAttFill = new TAttFill[fNErrorDimensions];
    fAttLine = new TAttLine[fNErrorDimensions];
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor with multiple vectors of doubles in input and multiple y error dimensions
/// A grapherrors is built with the X coordinates taken from tvX and Y coord from tvY
/// and the errors from vectors tvExL/H and tvEyL/H[yErrorDimension].
/// The number of points in the graph is the minimum of number of points
/// in tvX and tvY.

TGraphMultiErrors::TGraphMultiErrors(Int_t dim, const TVectorD& tvX, const TVectorD& tvY, const TVectorD& tvExL, const TVectorD& tvExH, const TVectorD* tvEyL, const TVectorD* tvEyH, Int_t m) : TGraph(), fNErrorDimensions(dim), fEyLSum(NULL), fEyHSum(NULL), fSumErrorsMode(m) {
    fNpoints = TMath::Min(tvX.GetNrows(), tvY.GetNrows());

    if (!TGraph::CtorAllocate())
	return;

    if (!CtorAllocate())
	return;

    Int_t itvXL   = tvX.GetLwb();
    Int_t itvYL   = tvY.GetLwb();
    Int_t itvExLL = tvExL.GetLwb();
    Int_t itvExHL = tvExH.GetLwb();

    for (Int_t i = 0; i < fNpoints; i++) {
	fX[i]      = tvX(i + itvXL);
	fY[i]      = tvY(i + itvYL);
        fExL[i]    = tvExL(i + itvExLL);
	fExH[i]    = tvExH(i + itvExHL);

        for (Int_t j = 0; j < dim; j++) {
	    fEyL[j][i] = tvEyL[j](i + tvEyL[j].GetLwb());
	    fEyH[j][i] = tvEyH[j](i + tvEyH[j].GetLwb());
	}
    }

    CalcYErrorSum();

    fAttFill = new TAttFill[fNErrorDimensions];
    fAttLine = new TAttLine[fNErrorDimensions];
}

////////////////////////////////////////////////////////////////////////////////
/// TGraphMultiErrors copy constructor

TGraphMultiErrors::TGraphMultiErrors(const TGraphMultiErrors& tgme) : TGraph(tgme), fEyLSum(NULL), fEyHSum(NULL) {
    fNErrorDimensions = tgme.fNErrorDimensions;
    fSumErrorsMode    = tgme.fSumErrorsMode;

    if (!CtorAllocate())
	return;

    Int_t n = fNpoints * sizeof(Double_t);
    memcpy(fExL, tgme.fExL, n);
    memcpy(fExH, tgme.fExH, n);

    for (Int_t j = 0; j < fNErrorDimensions; j++) {
	memcpy(fEyL[j], tgme.fEyL[j], n);
	memcpy(fEyH[j], tgme.fEyH[j], n);
    }

    CalcYErrorSum();

    fAttFill = new TAttFill[fNErrorDimensions];
    fAttLine = new TAttLine[fNErrorDimensions];

    for (Int_t j = 0; j < fNErrorDimensions; j++) {
        tgme.GetAttFill(j)->Copy(fAttFill[j]);
	tgme.GetAttLine(j)->Copy(fAttLine[j]);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// TGraphMultiErrors assignment operator

TGraphMultiErrors& TGraphMultiErrors::operator = (const TGraphMultiErrors& tgme) {
    if (this != &tgme) {
	TGraph::operator = (tgme);
	// delete arrays
	if (fExL) delete [] fExL;
	if (fExH) delete [] fExH;

	if (fEyL) {
            for (Int_t j = 0; j < fNErrorDimensions; j++)
		delete [] fEyL[j];
	    delete [] fEyL;
	}
        if (fEyH) {
            for (Int_t j = 0; j < fNErrorDimensions; j++)
		delete [] fEyH[j];
	    delete [] fEyH;
	}

        if (fAttFill) delete [] fAttFill;
	if (fAttLine) delete [] fAttLine;

        fNErrorDimensions = tgme.fNErrorDimensions;
	fSumErrorsMode    = tgme.fSumErrorsMode;

	if (!CtorAllocate())
	    return *this;

        Int_t n = fNpoints * sizeof(Double_t);
	memcpy(fExL, tgme.fExL, n);
	memcpy(fExH, tgme.fExH, n);

        for (Int_t j = 0; j < fNErrorDimensions; j++) {
	    memcpy(fEyL[j], tgme.fEyL[j], n);
	    memcpy(fEyH[j], tgme.fEyH[j], n);
	}

	CalcYErrorSum();

        fAttFill = new TAttFill[fNErrorDimensions];
	fAttLine = new TAttLine[fNErrorDimensions];

	for (Int_t j = 0; j < fNErrorDimensions; j++) {
	    tgme.GetAttFill(j)->Copy(fAttFill[j]);
	    tgme.GetAttLine(j)->Copy(fAttLine[j]);
	}
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// TGraphMultiErrors constructor importing its parameters from the TH1 object passed as argument
/// the low and high errors are set to the bin error of the histogram.

TGraphMultiErrors::TGraphMultiErrors(const TH1* h, Int_t dim) : TGraph(h), fNErrorDimensions(dim), fEyLSum(NULL), fEyHSum(NULL), fSumErrorsMode(TGraphMultiErrors::kOnlyFirst) {
    if (!CtorAllocate())
	return;

    for (Int_t i = 0; i < fNpoints; i++) {
	fExL[i]    = h->GetBinWidth(i + 1) * gStyle->GetErrorX();
	fExH[i]    = h->GetBinWidth(i + 1) * gStyle->GetErrorX();
	fEyL[0][i] = h->GetBinError(i + 1);
	fEyH[0][i] = h->GetBinError(i + 1);

	for (Int_t j = 1; j < fNErrorDimensions; j++) {
            fEyL[j][i] = 0.;
	    fEyH[j][i] = 0.;
	}
    }

    CalcYErrorSum();

    fAttFill = new TAttFill[fNErrorDimensions];
    fAttLine = new TAttLine[fNErrorDimensions];

    TAttFill::Copy(fAttFill[0]);
    TAttLine::Copy(fAttLine[0]);
}

////////////////////////////////////////////////////////////////////////////////
/// Creates a TGraphMultiErrors by dividing two input TH1 histograms:
/// pass/total. (see TGraphMultiErrors::Divide)

TGraphMultiErrors::TGraphMultiErrors(const TH1* pass, const TH1* total, Int_t dim, Option_t *option) : TGraph(pass ? pass->GetNbinsX() : 0), fNErrorDimensions(dim), fEyLSum(NULL), fEyHSum(NULL), fSumErrorsMode(TGraphMultiErrors::kOnlyFirst) {
    if (!pass || !total) {
	Error("TGraphMultiErrors", "Invalid histogram pointers");
	return;
    }

    if (!CtorAllocate())
	return;

    std::string sname = "divide_" + std::string(pass->GetName()) + "_by_" + std::string(total->GetName());
    SetName(sname.c_str());
    SetTitle(pass->GetTitle());

    //copy style from pass
    pass->TAttLine::Copy(*this);
    pass->TAttFill::Copy(*this);
    pass->TAttMarker::Copy(*this);

    Divide(pass, total, option);
    CalcYErrorSum();

    fAttFill = new TAttFill[fNErrorDimensions];
    fAttLine = new TAttLine[fNErrorDimensions];

    TAttFill::Copy(fAttFill[0]);
    TAttLine::Copy(fAttLine[0]);
}

////////////////////////////////////////////////////////////////////////////////
/// TGraphMultiErrors default destructor.

TGraphMultiErrors::~TGraphMultiErrors() {
    if (fExL) delete [] fExL;
    if (fExH) delete [] fExH;

    if (fEyL) {
	for (Int_t j = 0; j < fNErrorDimensions; j++)
	    delete [] fEyL[j];
	delete [] fEyL;
    }
    if (fEyH) {
	for (Int_t j = 0; j < fNErrorDimensions; j++)
	    delete [] fEyH[j];
	delete [] fEyH;
    }

    if (fEyLSum) delete [] fEyLSum;
    if (fEyHSum) delete [] fEyHSum;

    if (fAttFill) delete [] fAttFill;
    if (fAttLine) delete [] fAttLine;
}

////////////////////////////////////////////////////////////////////////////////
/// Apply a function to all data points `y = f(x,y)`
///
/// Errors are calculated as `eyh = f(x,y+eyh)-f(x,y)` and
/// `eyl = f(x,y)-f(x,y-eyl)`
/// Only the first error dimension is affected!!!
///
/// Special treatment has to be applied for the functions where the
/// role of "up" and "down" is reversed.
/// function suggested/implemented by Miroslav Helbich <helbich@mail.desy.de>

void TGraphMultiErrors::Apply(TF1* f) {
    Double_t x, y, eyL, eyH, eyLNew, eyHNew, fxy;

    if (fHistogram) {
	delete fHistogram;
	fHistogram = 0;
    }

    for (Int_t i = 0; i < fNpoints; i++) {
	GetPoint(i, x, y);
	eyL = GetErrorYlow(i, 0);
	eyH = GetErrorYhigh(i, 0);

	fxy = f->Eval(x, y);
	SetPoint(i, x, fxy);

	if (f->Eval(x, y - eyL) < f->Eval(x, y + eyH)) {
	    eyLNew = TMath::Abs(fxy - f->Eval(x, y - eyL));
	    eyHNew = TMath::Abs(f->Eval(x, y + eyH) - fxy);
	} else {
	    eyHNew = TMath::Abs(fxy - f->Eval(x, y - eyL));
	    eyLNew = TMath::Abs(f->Eval(x, y + eyH) - fxy);
	}

	//systematic errors and error on x doesn't change
        SetPointEY(i, 0, eyLNew, eyHNew);
    }

    if (gPad)
	gPad->Modified();
}

////////////////////////////////////////////////////////////////////////////////
/// This function is only kept for backward compatibility.
/// You should rather use the Divide method.
/// It calls `Divide(pass,total,"cl=0.683 b(1,1) mode")` which is equivalent to the
/// former BayesDivide method.

void TGraphMultiErrors::BayesDivide(const TH1* pass, const TH1* total, Option_t*) {
    Divide(pass, total, "cl=0.683 b(1,1) mode");
}

////////////////////////////////////////////////////////////////////////////////
/// This function was adapted from the TGraphAsymmErrors class.
/// See TGraphAsymmErrors::Divide for the documentation
///
/// Only the first error dimension is affected!!!

void TGraphMultiErrors::Divide(const TH1* pass, const TH1* total, Option_t *opt) {
    //check pointers
    if(!pass || !total) {
	Error("Divide", "one of the passed pointers is zero");
	return;
    }

    //check dimension of histograms; only 1-dimensional ones are accepted
    if((pass->GetDimension() > 1) || (total->GetDimension() > 1)) {
	Error("Divide","passed histograms are not one-dimensional");
	return;
    }

    //check whether histograms are filled with weights -> use number of effective
    //entries
    Bool_t bEffective = false;
    //compare sum of weights with sum of squares of weights
    // re-compute here to be sure to get the right values
    Double_t psumw = 0;
    Double_t psumw2 = 0;
    if (pass->GetSumw2()->fN > 0) {
	for (int i = 0; i < pass->GetNbinsX(); ++i) {
	    psumw += pass->GetBinContent(i);
	    psumw2 += pass->GetSumw2()->At(i);
	}
    } else {
	psumw = pass->GetSumOfWeights();
	psumw2 = psumw;
    }
    if (TMath::Abs(psumw - psumw2) > 1e-6)
	bEffective = true;
 
    Double_t tsumw = 0;
    Double_t tsumw2 = 0;
    if (total->GetSumw2()->fN > 0) {
	for (int i = 0; i < total->GetNbinsX(); ++i) {
	    tsumw += total->GetBinContent(i);
	    tsumw2 += total->GetSumw2()->At(i);
	}
    } else {
	tsumw = total->GetSumOfWeights();
	tsumw2 = tsumw;
    }
    if (TMath::Abs(tsumw - tsumw2) > 1e-6)
	bEffective = true;



    // we do not want to ignore the weights
    // if (bEffective && (pass->GetSumw2()->fN == 0 || total->GetSumw2()->fN == 0) ) {
    //    Warning("Divide","histogram have been computed with weights but the sum of weight squares are not stored in the histogram. Error calculation is performed ignoring the weights");
    //    bEffective = false;
    // }

    //parse option
    TString option = opt;
    option.ToLower();
 
    Bool_t bVerbose = false;
    //pointer to function returning the boundaries of the confidence interval
    //(is only used in the frequentist cases.)
    //Double_t (*pBound)(Int_t,Int_t,Double_t,Bool_t) = &TEfficiency::ClopperPearson; // default method
    Double_t (*pBound)(Double_t,Double_t,Double_t,Bool_t) = &TEfficiency::ClopperPearson; // default method
    //confidence level
    Double_t conf = 0.682689492137;
    //values for bayesian statistics
    Bool_t bIsBayesian = false;
    Double_t alpha = 1;
    Double_t beta = 1;

    //verbose mode
    if(option.Contains("v")) {
	option.ReplaceAll("v", "");
	bVerbose = true;
	if (bEffective)
	    Info("Divide", "weight will be considered in the Histogram Ratio");
    }


    //confidence level
    if(option.Contains("cl=")) {
	Double_t level = -1;
	// coverity [secure_coding : FALSE]
	sscanf(strstr(option.Data(),"cl="),"cl=%lf",&level);
	if((level > 0) && (level < 1))
	    conf = level;
	else
	    Warning("Divide","given confidence level %.3lf is invalid",level);
	option.ReplaceAll("cl=","");
    }

    //normal approximation
    if(option.Contains("n")) {
	option.ReplaceAll("n","");
	pBound = &TEfficiency::Normal;
    }

    //clopper pearson interval
    if(option.Contains("cp")) {
	option.ReplaceAll("cp","");
	pBound = &TEfficiency::ClopperPearson;
    }

    //wilson interval
    if(option.Contains("w")) {
	option.ReplaceAll("w","");
	pBound = &TEfficiency::Wilson;
    }

    //agresti coull interval
    if(option.Contains("ac")) {
	option.ReplaceAll("ac","");
	pBound = &TEfficiency::AgrestiCoull;
    }
    // Feldman-Cousins interval
    if(option.Contains("fc")) {
	option.ReplaceAll("fc","");
	pBound = &TEfficiency::FeldmanCousins;
    }
    // mid-P Lancaster interval (In a later ROOT Version!)
    if(option.Contains("midp")) {
	option.ReplaceAll("midp","");
	//pBound = &TEfficiency::MidPInterval;
    }

    //bayesian with prior
    if(option.Contains("b(")) {
	Double_t a = 0;
	Double_t b = 0;
	sscanf(strstr(option.Data(),"b("),"b(%lf,%lf)",&a,&b);
	if(a > 0)
	    alpha = a;
	else
	    Warning("Divide", "given shape parameter for alpha %.2lf is invalid",a);
	if(b > 0)
	    beta = b;
	else
	    Warning("Divide","given shape parameter for beta %.2lf is invalid",b);
	option.ReplaceAll("b(","");
	bIsBayesian = true;
    }

    // use posterior mode
    Bool_t usePosteriorMode = false;
    if(bIsBayesian && option.Contains("mode") ) {
	usePosteriorMode = true;
	option.ReplaceAll("mode","");
    }
 
    Bool_t plot0Bins = false;
    if(option.Contains("e0") ) {
	plot0Bins = true;
	option.ReplaceAll("e0","");
    }
 
    Bool_t useShortestInterval = false;
    if (bIsBayesian && ( option.Contains("sh") || (usePosteriorMode && !option.Contains("cen") ) ) ) {
	useShortestInterval = true;
    }
 
    // interpret as Poisson ratio
    Bool_t bPoissonRatio = false;
    if(option.Contains("pois") ) {
	bPoissonRatio = true;
	option.ReplaceAll("pois","");
    }
 
    // weights works only in case of Normal approximation or Bayesian for binomial interval
    // in case of Poisson ratio we can use weights by rescaling the obtained results using the effective entries
    if ( ( bEffective && !bPoissonRatio) && !bIsBayesian && pBound != &TEfficiency::Normal ) {
	Warning("Divide","Histograms have weights: only Normal or Bayesian error calculation is supported");
	Info("Divide","Using now the Normal approximation for weighted histograms");
    }
 
    if(bPoissonRatio) {
	if(pass->GetDimension() != total->GetDimension()) {
	    Error("Divide","passed histograms are not of the same dimension");
	    return;
	}
 
	if(!TEfficiency::CheckBinning(*pass,*total)) {
	    Error("Divide","passed histograms are not consistent");
	    return;
	}
    } else {
	//check consistency of histograms, allowing weights
	if(!TEfficiency::CheckConsistency(*pass,*total,"w")) {
	    Error("Divide","passed histograms are not consistent");
	    return;
	}
    }

    //Set the graph to have a number of points equal to the number of histogram
    //bins
    Int_t nbins = pass->GetNbinsX();
    Set(nbins);

    // Ok, now set the points for each bin
    // (Note: the TH1 bin content is shifted to the right by one:
    //  bin=0 is underflow, bin=nbins+1 is overflow.)
 
    //efficiency with lower and upper boundary of confidence interval
    double eff, low, upper;
    //this keeps track of the number of points added to the graph
    int npoint=0;
    //number of total and passed events
    Double_t t = 0 , p = 0;
    Double_t tw = 0, tw2 = 0, pw = 0, pw2 = 0, wratio = 1; // for the case of weights
    //loop over all bins and fill the graph
    for (Int_t b=1; b<=nbins; ++b) {
	// default value when total =0;
	eff = 0;
	low = 0;
	upper = 0;
 
	// special case in case of weights we have to consider the sum of weights and the sum of weight squares
	if(bEffective) {
	    tw =  total->GetBinContent(b);
	    tw2 = (total->GetSumw2()->fN > 0) ? total->GetSumw2()->At(b) : tw;
	    pw =  pass->GetBinContent(b);
	    pw2 = (pass->GetSumw2()->fN > 0) ? pass->GetSumw2()->At(b) : pw;

	    if(bPoissonRatio) {
		// tw += pw;
		// tw2 += pw2;
		// compute ratio on the effective entries ( p and t)
		// special case is when (pw=0, pw2=0) in this case we cannot get the bin weight.
		// we use then the overall weight of the full histogram
		if (pw == 0 && pw2 == 0)
		    p = 0;
		else
		    p = (pw*pw)/pw2;

		if (tw == 0 && tw2 == 0)
		    t = 0;
		else
		    t = (tw*tw)/tw2;
 
		if (pw > 0 && tw > 0)
		    // this is the ratio of the two bin weights ( pw/p  / t/tw )
		    wratio = (pw*t)/(p * tw);
		else if (pw == 0 && tw > 0)
		    // case p histogram has zero  compute the weights from all the histogram
		    // weight of histogram - sumw2/sumw
		    wratio = (psumw2 * t) /(psumw * tw );
		else if (tw == 0 && pw > 0)
		    // case t histogram has zero  compute the weights from all the histogram
		    // weight of histogram - sumw2/sumw
		    wratio = (pw * tsumw) /(p * tsumw2 );
		else if (p > 0)
		    wratio = pw/p; //not sure if needed
		else {
		    // case both pw and tw are zero - we skip these bins
		    if (!plot0Bins) continue; // skip bins with total <= 0
		}

		t += p;
		//std::cout << p << "   " << t << "  " << wratio << std::endl;
	    } else if (tw <= 0 && !plot0Bins) continue; // skip bins with total <= 0
 
	    // in the case of weights have the formula only for
	    // the normal and  bayesian statistics (see below)
 
	}

	//use bin contents
	else {
	    t = int( total->GetBinContent(b) + 0.5);
	    p = int(pass->GetBinContent(b) + 0.5);
 
	    if(bPoissonRatio) t += p;
 
	    if (!t && !plot0Bins) continue; // skip bins with total = 0
	}

 
	//using bayesian statistics
	if(bIsBayesian) {
	    double aa,bb;
 
	    if ((bEffective && !bPoissonRatio) && tw2 <= 0) {
		// case of bins with zero errors
		eff = pw/tw;
		low = eff; upper = eff;
	    } else {
		if (bEffective && !bPoissonRatio) {
		    // tw/tw2 re-normalize the weights
		    double norm = tw/tw2;  // case of tw2 = 0 is treated above
		    aa =  pw * norm + alpha;
		    bb =  (tw - pw) * norm + beta;
		} else {
		    aa = double(p) + alpha;
		    bb = double(t-p) + beta;
		}
		if (usePosteriorMode)
		    eff = TEfficiency::BetaMode(aa,bb);
		else
		    eff = TEfficiency::BetaMean(aa,bb);

		if (useShortestInterval) {
		    TEfficiency::BetaShortestInterval(conf,aa,bb,low,upper);
		}
		else {
		    low = TEfficiency::BetaCentralInterval(conf,aa,bb,false);
		    upper = TEfficiency::BetaCentralInterval(conf,aa,bb,true);
		}
	    }
	}
	// case of non-bayesian statistics
	else {
	    if (bEffective && !bPoissonRatio) {

		if (tw > 0) {
 
		    eff = pw/tw;
 
		    // use normal error calculation using variance of MLE with weights (F.James 8.5.2)
		    // this is the same formula used in ROOT for TH1::Divide("B")
 
		    double variance = ( pw2 * (1. - 2 * eff) + tw2 * eff *eff ) / ( tw * tw) ;
		    double sigma = sqrt(variance);
 
		    double prob = 0.5 * (1.-conf);
		    double delta = ROOT::Math::normal_quantile_c(prob, sigma);
		    low = eff - delta;
		    upper = eff + delta;
		    if (low < 0) low = 0;
		    if (upper > 1) upper = 1.;
		}
	    } else {
		// when not using weights (all cases) or in case of  Poisson ratio with weights
		if(t)
		    eff = ((Double_t)p)/t;
 
		low = pBound(t,p,conf,false);
		upper = pBound(t,p,conf,true);
	    }
	}
	// treat as Poisson ratio
	if(bPoissonRatio)
	{
	    Double_t ratio = eff/(1 - eff);
	    // take the intervals in eff as intervals in the Poisson ratio
	    low = low/(1. - low);
	    upper = upper/(1.-upper);
	    eff = ratio;
	    if (bEffective) {
		//scale result by the ratio of the weight
		eff *= wratio;
		low *= wratio;
		upper *= wratio;
	    }
	}
	//Set the point center and its errors
	if (TMath::Finite(eff)) {
	    SetPoint(npoint,pass->GetBinCenter(b),eff);
	    SetPointEX(npoint, pass->GetBinCenter(b)-pass->GetBinLowEdge(b), pass->GetBinLowEdge(b)-pass->GetBinCenter(b)+pass->GetBinWidth(b));
            SetPointEY(npoint, 0, eff - low, upper - eff);
	    npoint++;//we have added a point to the graph
	}
    }
 
    Set(npoint);//tell the graph how many points we've really added
    if (npoint < nbins)
	Warning("Divide","Number of graph points is different than histogram bins - %d points have been skipped",nbins-npoint);
 
 
    if (bVerbose) {
	Info("Divide","made a graph with %d points from %d bins",npoint,nbins);
	Info("Divide","used confidence level: %.2lf\n",conf);
	if(bIsBayesian)
	    Info("Divide","used prior probability ~ beta(%.2lf,%.2lf)",alpha,beta);
	Print();
    }
}

////////////////////////////////////////////////////////////////////////////////
/// Compute Range

void TGraphMultiErrors::ComputeRange(Double_t& xmin, Double_t& ymin, Double_t& xmax, Double_t& ymax) const {
    TGraph::ComputeRange(xmin, ymin, xmax, ymax);

    for (Int_t i = 0; i < fNpoints; i++) {
	if (fX[i] - fExL[i] < xmin) {
	    if (gPad && gPad->GetLogx()) {
		if (fExL[i] < fX[i])
		    xmin = fX[i] - fExL[i];
		else
		    xmin = TMath::Min(xmin, fX[i] / 3.);
	    } else
		xmin = fX[i] - fExL[i];
	}

        if (fX[i] + fExH[i] > xmax)
	    xmax = fX[i] + fExH[i];

	Double_t eyLMax = 0., eyHMax = 0.;
	for (Int_t j = 0; j < fNErrorDimensions; j++) {
	    eyLMax = TMath::Max(eyLMax, fEyL[j][i]);
	    eyHMax = TMath::Max(eyHMax, fEyH[j][i]);
	}

	if (fY[i] - eyLMax < ymin) {
	    if (gPad && gPad->GetLogy()) {
		if (eyLMax < fY[i])
		    ymin = fY[i] - eyLMax;
		else
		    ymin = TMath::Min(ymin, fY[i] / 3.);
	    } else
		ymin = fY[i] - eyLMax;
	}

	if (fY[i] + eyHMax > ymax)
	    ymax = fY[i] + eyHMax;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// Copy and release.

void TGraphMultiErrors::CopyAndRelease(Double_t** newarrays, Int_t ibegin, Int_t iend, Int_t obegin) {
    CopyPoints(newarrays, ibegin, iend, obegin);
    if (newarrays) {
        delete[] fX;
	fX = newarrays[0];
	delete[] fY;
	fY = newarrays[1];

	delete[] fExL;
	fExL = newarrays[2];
	delete[] fExH;
	fExH = newarrays[3];

	for (Int_t j = 0; j < fNErrorDimensions; j++)
	    delete [] fEyL[j];
	delete [] fEyL;
	fEyL = new Double_t*[fNErrorDimensions];
	for (Int_t j = 0; j < fNErrorDimensions; j++)
	    fEyL[j] = newarrays[2*j + 4];

        for (Int_t j = 0; j < fNErrorDimensions; j++)
	    delete [] fEyH[j];
	delete [] fEyH;
	fEyH = new Double_t*[fNErrorDimensions];
	for (Int_t j = 0; j < fNErrorDimensions; j++)
            fEyH[j] = newarrays[2*j + 5];

	delete[] newarrays;
    }

    CalcYErrorSum();
}

////////////////////////////////////////////////////////////////////////////////
/// Copy errors from fE*** to arrays[***]
/// or to f*** Copy points.

Bool_t TGraphMultiErrors::CopyPoints(Double_t** arrays, Int_t ibegin, Int_t iend, Int_t obegin) {
    if (TGraph::CopyPoints(arrays, ibegin, iend, obegin)) {
	Int_t n = (iend - ibegin) * sizeof(Double_t);

	if (arrays) {
	    memmove(&arrays[2][obegin], &fExL[ibegin], n);
	    memmove(&arrays[3][obegin], &fExH[ibegin], n);

	    for (Int_t j = 0; j < fNErrorDimensions; j++) {
		memmove(&arrays[2*j + 4][obegin], &fEyL[j][ibegin], n);
		memmove(&arrays[2*j + 5][obegin], &fEyH[j][ibegin], n);
	    }
	} else {
	    memmove(&fExL[obegin], &fExL[ibegin], n);
	    memmove(&fExH[obegin], &fExH[ibegin], n);

            for (Int_t j = 0; j < fNErrorDimensions; j++) {
		memmove(&fEyL[j][obegin], &fEyL[j][ibegin], n);
		memmove(&fEyH[j][obegin], &fEyH[j][ibegin], n);
	    }
	}

	return kTRUE;
    } else
	return kFALSE;
}

////////////////////////////////////////////////////////////////////////////////
/// Copy and release.
///
/// Necessary for correct treatment of multiple y error dimensions

void TGraphMultiErrors::CopyAndReleaseY(Double_t** newarrays, Int_t ibegin, Int_t iend, Int_t obegin) {
    CopyPointsY(newarrays, ibegin, TMath::Min(iend, fNErrorDimensions), obegin);
    if (newarrays) {
	for (Int_t j = 0; j < fNErrorDimensions; j++)
	    delete [] fEyL[j];
	delete [] fEyL;
	fEyL = new Double_t*[iend - ibegin];
	for (Int_t j = 0; j < iend - ibegin; j++)
	    fEyL[j] = newarrays[2*j];

        for (Int_t j = 0; j < fNErrorDimensions; j++)
	    delete [] fEyH[j];
	delete [] fEyH;
	fEyH = new Double_t*[iend - ibegin];
	for (Int_t j = 0; j < iend - ibegin; j++)
            fEyH[j] = newarrays[2*j + 1];

	delete[] newarrays;
    }

    CalcYErrorSum();
}

////////////////////////////////////////////////////////////////////////////////
/// Copy errors from fE*** to arrays[***]
/// or to f*** Copy points.
///
/// Necessary for correct treatment of multiple y error dimensions

Bool_t TGraphMultiErrors::CopyPointsY(Double_t** arrays, Int_t ibegin, Int_t iend, Int_t obegin) {
    Int_t n = fNpoints * sizeof(Double_t);

    for (Int_t j = ibegin; j < iend; j++) {
	if (arrays) {
	    memmove(&arrays[2*j     - ibegin + obegin][0], &fEyL[j][0], n);
	    memmove(&arrays[2*j + 1 - ibegin + obegin][0], &fEyH[j][0], n);
	} else {
	    memmove(&fEyL[j - ibegin + obegin][0], &fEyL[j][0], n);
	    memmove(&fEyH[j - ibegin + obegin][0], &fEyH[j][0], n);
	}
    }

    return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Should be called from ctors after fNpoints has been set
/// Note: This function should be called only from the constructor
/// since it does not delete previously existing arrays

Bool_t TGraphMultiErrors::CtorAllocate(void) {
    if (!fNpoints || !fNErrorDimensions) {
	fExL = fExH = NULL;
	fEyL = fEyH = NULL;
	return kFALSE;
    }

    fExL = new Double_t [fMaxSize];
    fExH = new Double_t [fMaxSize];
    fEyL = new Double_t*[fNErrorDimensions];
    fEyH = new Double_t*[fNErrorDimensions];
    fEyLSum = new Double_t[fNpoints];
    fEyHSum = new Double_t[fNpoints];

    for (Int_t j = 0; j < fNErrorDimensions; j++) {
        fEyL[j] = new Double_t[fMaxSize];
        fEyH[j] = new Double_t[fMaxSize];
    }

    return kTRUE;
}

////////////////////////////////////////////////////////////////////////////////
 ///  protected function to perform the merge operation of a graph with multiple asymmetric errors

Bool_t TGraphMultiErrors::DoMerge(const TGraph* tg) {
    if (tg->GetN() == 0) return kFALSE;

    if (tg->IsA() == TGraphMultiErrors::Class()) {
        TGraphMultiErrors* tgme = (TGraphMultiErrors*) tg;

        for (Int_t i = 0 ; i < tgme->GetN(); i++) {
	    Int_t ipoint = GetN();
	    Double_t x, y;
	    tgme->GetPoint(i, x, y);
	    SetPoint(ipoint, x, y);
	    SetPointEX(ipoint, tgme->GetErrorXlow(i), tgme->GetErrorXhigh(i));
	    for (Int_t j = 0; j < tgme->GetNErrorDimensions(); j++)
		SetPointEY(ipoint, j, tgme->GetErrorYlow(i, j), tgme->GetErrorYhigh(i, j));
	}

        return kTRUE;
    } else {
	Warning("DoMerge", "Merging a %s is not compatible with a TGraphMultiErrors - Errors will be ignored", tg->IsA()->GetName());
        return TGraph::DoMerge(tg);
    }

    return kFALSE;
}

////////////////////////////////////////////////////////////////////////////////
/// Set zero values for point arrays in the range [begin, end)

void TGraphMultiErrors::FillZero(Int_t begin, Int_t end, Bool_t from_ctor) {
    if (!from_ctor)
	TGraph::FillZero(begin, end, from_ctor);

    Int_t n = (end - begin) * sizeof(Double_t);
    memset(fExL + begin, 0, n);
    memset(fExH + begin, 0, n);
    memset(fEyLSum + begin, 0, n);
    memset(fEyHSum + begin, 0, n);

    for (Int_t j = 0; j < fNErrorDimensions; j++) {
	memset(fEyL[j] + begin, 0, n);
	memset(fEyH[j] + begin, 0, n);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// Set zero values for point arrays in the range [begin, end)
///
/// Necessary for correct treatment of multiple y error dimensions

void TGraphMultiErrors::FillZeroY(Int_t begin, Int_t end, Bool_t from_ctor) {
    Int_t n = fNpoints * sizeof(Double_t);

    for (Int_t j = begin; j < end; j++) {
	memset(fEyL[j], 0, n);
	memset(fEyH[j], 0, n);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// Get x coordinate of point i

Double_t TGraphMultiErrors::GetPointX(Int_t i) const {
    if (i < 0 || i >= fNpoints || !fX)
	return -1.;

    return fX[i];
}

////////////////////////////////////////////////////////////////////////////////
/// Get y coordinate of point i

Double_t TGraphMultiErrors::GetPointY(Int_t i) const {
    if (i < 0 || i >= fNpoints || !fY)
	return -1.;

    return fY[i];
}

////////////////////////////////////////////////////////////////////////////////
/// Get error on x coordinate for point i
/// In case of asymmetric errors the mean of the square sum is returned

Double_t TGraphMultiErrors::GetErrorX(Int_t i) const {
    if (i < 0 || i >= fNpoints || (!fExL && !fExH))
	return -1.;

    Double_t exL = fExL ? fExL[i] : 0.;
    Double_t exH = fExH ? fExH[i] : 0.;
    return TMath::Sqrt((exL*exL + exH*exH) / 2.);
}

////////////////////////////////////////////////////////////////////////////////
/// Get error on y coordinate for point i
/// The multiple errors of the dimensions are summed according to fSumErrorsMode
/// In case of asymmetric errors the mean of the square sum is returned

Double_t TGraphMultiErrors::GetErrorY(Int_t i) const {
    if (i < 0 || i >= fNpoints || (!fEyL && !fEyH))
	return -1.;

    Double_t eyL = GetErrorYlow(i);
    Double_t eyH = GetErrorYhigh(i);
    return TMath::Sqrt((eyL*eyL + eyH*eyH) / 2.);
}

////////////////////////////////////////////////////////////////////////////////
/// Get error on y coordinate in dimension dim for point i
/// In case of asymmetric errors the mean of the square sum is returned

Double_t TGraphMultiErrors::GetErrorY(Int_t i, Int_t dim) const {
    if (i < 0 || i >= fNpoints || dim >= fNErrorDimensions || (!fEyL && !fEyH))
	return -1.;

    Double_t eyL = fEyL ? fEyL[dim][i] : 0.;
    Double_t eyH = fEyH ? fEyH[dim][i] : 0.;
    return TMath::Sqrt((eyL*eyL + eyH*eyH) / 2.);
}

////////////////////////////////////////////////////////////////////////////////
/// Get low error on x coordinate for point i

Double_t TGraphMultiErrors::GetErrorXlow(Int_t i) const {
    if (i < 0 || i >= fNpoints || !fExL)
	return -1.;
    else
        return fExL[i];
}

////////////////////////////////////////////////////////////////////////////////
/// Get high error on x coordinate for point i

Double_t TGraphMultiErrors::GetErrorXhigh(Int_t i) const {
    if (i < 0 || i >= fNpoints || !fExH)
	return -1.;
    else
        return fExH[i];
}

////////////////////////////////////////////////////////////////////////////////
/// Get low error on y coordinate for point i
/// The multiple errors of the dimensions are summed according to fSumErrorsMode

Double_t TGraphMultiErrors::GetErrorYlow(Int_t i) const {
    if (i < 0 || i >= fNpoints || !fEyL)
	return -1.;

    if (fSumErrorsMode == TGraphMultiErrors::kOnlyFirst)
	return fEyL[0][i];
    else if (fSumErrorsMode == TGraphMultiErrors::kSquareSum) {
	Double_t sum = 0.;
	for (Int_t j = 0; j < fNErrorDimensions; j++)
            sum += fEyL[j][i]*fEyL[j][i];
	return TMath::Sqrt(sum);
    } else if (fSumErrorsMode == TGraphMultiErrors::kSum) {
        Double_t sum = 0.;
	for (Int_t j = 0; j < fNErrorDimensions; j++)
            sum += fEyL[j][i];
	return sum;
    }

    return -1.;
}

////////////////////////////////////////////////////////////////////////////////
/// Get high error on y coordinate for point i
/// The multiple errors of the dimensions are summed according to fSumErrorsMode

Double_t TGraphMultiErrors::GetErrorYhigh(Int_t i) const {
    if (i < 0 || i >= fNpoints || !fEyH)
	return -1.;

    if (fSumErrorsMode == TGraphMultiErrors::kOnlyFirst)
	return fEyH[0][i];
    else if (fSumErrorsMode == TGraphMultiErrors::kSquareSum) {
	Double_t sum = 0.;
	for (Int_t j = 0; j < fNErrorDimensions; j++)
            sum += fEyH[j][i]*fEyH[j][i];
	return TMath::Sqrt(sum);
    } else if (fSumErrorsMode == TGraphMultiErrors::kSum) {
        Double_t sum = 0.;
	for (Int_t j = 0; j < fNErrorDimensions; j++)
            sum += fEyH[j][i];
	return sum;
    }

    return -1.;
}

////////////////////////////////////////////////////////////////////////////////
/// Get low error on y coordinate in dimension dim for point i

Double_t TGraphMultiErrors::GetErrorYlow(Int_t i, Int_t dim) const {
    if (i < 0 || i >= fNpoints || dim >= fNErrorDimensions || !fEyL)
	return -1.;
    else
        return fEyL[dim][i];
}

////////////////////////////////////////////////////////////////////////////////
/// Get high error on y coordinate in dimension dim for point i

Double_t TGraphMultiErrors::GetErrorYhigh(Int_t i, Int_t dim) const {
    if (i < 0 || i >= fNpoints || dim >= fNErrorDimensions || !fEyH)
	return -1.;
    else
        return fEyH[dim][i];
}

////////////////////////////////////////////////////////////////////////////////
/// Get AttFill pointer for specified error dimension

TAttFill* TGraphMultiErrors::GetAttFill(Int_t dim) const {
    if (dim >= 0 && dim < fNErrorDimensions)
	return (fAttFill + dim);
    else
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
/// Get AttLine pointer for specified error dimension

TAttLine* TGraphMultiErrors::GetAttLine(Int_t dim) const {
    if (dim >= 0 && dim < fNErrorDimensions)
	return (fAttLine + dim);
    else
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
/// Get Fill Color for specified error dimension (-1 = Global and x errors)

Color_t TGraphMultiErrors::GetFillColor(Int_t dim) const {
    if (dim == -1)
	return GetFillColor();
    else if (dim >= 0 && dim < fNErrorDimensions)
	return fAttFill[dim].GetFillColor();
    else
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Get Fill Style for specified error dimension (-1 = Global and x errors)

Style_t TGraphMultiErrors::GetFillStyle(Int_t dim) const {
    if (dim == -1)
	return GetFillStyle();
    else if (dim >= 0 && dim < fNErrorDimensions)
	return fAttFill[dim].GetFillStyle();
    else
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Get Line Color for specified error dimension (-1 = Global and x errors)

Color_t TGraphMultiErrors::GetLineColor(Int_t dim) const {
    if (dim == -1)
	return GetLineColor();
    else if (dim >= 0 && dim < fNErrorDimensions)
	return fAttLine[dim].GetLineColor();
    else
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Get Line Style for specified error dimension (-1 = Global and x errors)

Style_t TGraphMultiErrors::GetLineStyle(Int_t dim) const {
    if (dim == -1)
	return GetLineStyle();
    else if (dim >= 0 && dim < fNErrorDimensions)
	return fAttLine[dim].GetLineStyle();
    else
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Get Line Width for specified error dimension (-1 = Global and x errors)

Width_t TGraphMultiErrors::GetLineWidth(Int_t dim) const {
    if (dim == -1)
	return GetLineWidth();
    else if (dim >= 0 && dim < fNErrorDimensions)
	return fAttLine[dim].GetLineWidth();
    else
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Recalculates the summed y error arrays

void TGraphMultiErrors::CalcYErrorSum() {
    if (fEyLSum)
	delete [] fEyLSum;
    if (fEyHSum)
	delete [] fEyHSum;

    fEyLSum = new Double_t[fNpoints];
    fEyHSum = new Double_t[fNpoints];

    for (Int_t i = 0; i < fNpoints; i++) {
        fEyLSum[i] = GetErrorYlow(i);
        fEyHSum[i] = GetErrorYhigh(i);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// Get all low errors on y coordinates in dimension dim as an array

Double_t* TGraphMultiErrors::GetEYlow(Int_t dim) {
    if (dim >= fNErrorDimensions || !fEyL)
	return NULL;
    else
        return fEyL[dim];
}

////////////////////////////////////////////////////////////////////////////////
/// Get all high errors on y coordinates in dimension dim as an array

Double_t* TGraphMultiErrors::GetEYhigh(Int_t dim) {
    if (dim >= fNErrorDimensions || !fEyH)
	return NULL;
    else
        return fEyH[dim];
}

////////////////////////////////////////////////////////////////////////////////
/// Implementation to get information on point of graph at cursor position
/// Adapted from class TH1

char* TGraphMultiErrors::GetObjectInfo(Int_t px, Int_t py) const {
    //localize point
    Int_t ipoint = -2;
    Int_t i;
    // start with a small window (in case the mouse is very close to one point)
    for (i = 0; i < fNpoints; i++) {
	Int_t dpx = px - gPad->XtoAbsPixel(gPad->XtoPad(fX[i]));
	Int_t dpy = py - gPad->YtoAbsPixel(gPad->YtoPad(fY[i]));

	if (dpx*dpx+dpy*dpy < 25) {
	    ipoint = i;
	    break;
	}
    }

    Double_t x = gPad->PadtoX(gPad->AbsPixeltoX(px));
    Double_t y = gPad->PadtoY(gPad->AbsPixeltoY(py));

    if (ipoint == -2)
	return Form("x=%g, y=%g", x, y);

    Double_t xval        = fX[ipoint];
    Double_t yval        = fY[ipoint];
    //Double_t xvalErr     = fEx[ipoint];
    //Double_t yvalErrStat = fEyStat[ipoint];
    //Double_t yvalErrSysL = fEySysL[ipoint];
    //Double_t yvalErrSysH = fEySysH[ipoint];

    return Form("x=%g, y=%g, point=%d, xval=%g, yval=%g", x, y, ipoint, xval, yval);
}

////////////////////////////////////////////////////////////////////////////////
/// Print graph and errors values.

void TGraphMultiErrors::Print(Option_t*) const {
    for (Int_t i = 0; i < fNpoints; i++) {
	printf("x[%d]=%g, y[%d]=%g", i, fX[i], i, fY[i]);
	if (fExL)
	    printf(", exl[%d]=%g", i, fExL[i]);
        if (fExH)
	    printf(", exh[%d]=%g", i, fExH[i]);
	if (fEyL)
	    for (Int_t j = 0; j < fNErrorDimensions; j++)
		printf(", eyl[%d][%d]=%g", j, i, fEyL[j][i]);
        if (fEyH)
	    for (Int_t j = 0; j < fNErrorDimensions; j++)
		printf(", eyh[%d][%d]=%g", j, i, fEyH[j][i]);
        printf("\n");
    }
}

////////////////////////////////////////////////////////////////////////////////
/// Save primitive as a C++ statement(s) on output stream out

void TGraphMultiErrors::SavePrimitive(std::ostream &out, Option_t* option /*= ""*/) {
    char quote = '"';
    out << "    " << std::endl;

    if (gROOT->ClassSaved(TGraphMultiErrors::Class()))
	out << "    ";
    else
	out << "    TGraphMultiErrors* ";

    out << "tgme = new TGraphMultiErrors(" << fNpoints << ", " << fNErrorDimensions << ");" << std::endl;
    out << "    tgme->SetName(" << quote << GetName() << quote << ");" << std::endl;
    out << "    tgme->SetTitle(" << quote << GetTitle() << quote << ");" << std::endl;

    SaveFillAttributes(out, "tgme", 0, 1001);
    SaveLineAttributes(out, "tgme", 1, 1, 1);
    SaveMarkerAttributes(out, "tgme", 1, 1, 1);

    for (Int_t j = 0; j < fNErrorDimensions; j++) {
        SaveFillAttributes(out, Form("tgme->GetAttFill(%d)", j), 0, 1001);
	SaveLineAttributes(out, Form("tgme->GetAttLine(%d)", j), 1, 1, 1);
    }

    for (Int_t i = 0; i < fNpoints; i++) {
	out << "    tgme->SetPoint(" << i << ", " << fX[i] << ", " << fY[i] << ");" << std::endl;
	out << "    tgme->SetPointEX(" << i << ", " << fExL[i] << ", " << fExH[i] << ");" << std::endl;

	for (Int_t j = 0; j < fNErrorDimensions; j++)
            out << "    tgme->SetPointEY(" << i << ", " << j << ", " << fEyL[j][i] << ", " << fEyH[j][i] << ");" << std::endl;
    }

    static Int_t frameNumber = 0;
    if (fHistogram) {
	frameNumber++;
	TString hname = fHistogram->GetName();
	hname += frameNumber;
	fHistogram->SetName(Form("Graph_%s", hname.Data()));
	fHistogram->SavePrimitive(out, "nodraw");
	out << "    tgme->SetHistogram(" << fHistogram->GetName() << ");" << std::endl;
	out << "    " << std::endl;
    }

    // save list of functions
    TIter next(fFunctions);
    TObject *obj;
    while ((obj = next())) {
	obj->SavePrimitive(out, "nodraw");
	if (obj->InheritsFrom("TPaveStats")) {
	    out << "    tgme->GetListOfFunctions()->Add(ptstats);" << std::endl;
	    out << "    ptstats->SetParent(tgme->GetListOfFunctions());" << std::endl;
	} else
	    out << "    tgme->GetListOfFunctions()->Add(" << obj->GetName() << ");" << std::endl;
    }

    const char *l = strstr(option, "multigraph");
    if (l)
	out << "    multigraph->Add(tgme, " << quote << l + 10 << quote << ");" << std::endl;
    else
	out << "    tgme->Draw(" << quote << option << quote << ");" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
/// Set x coordinate of point i

void TGraphMultiErrors::SetPointX(Int_t i, Double_t x) {
    if (i < 0)
	return;

    if (i >= fNpoints) {
	// re-allocate the object
	TGraphMultiErrors::SetPoint(i, x, 0.);
    } else
        fX[i] = x;
}

////////////////////////////////////////////////////////////////////////////////
/// Set y coordinate of point i

void TGraphMultiErrors::SetPointY(Int_t i, Double_t y) {
    if (i < 0)
	return;

    if (i >= fNpoints) {
	// re-allocate the object
	TGraphMultiErrors::SetPoint(i, 0., y);
    } else
        fY[i] = y;
}

////////////////////////////////////////////////////////////////////////////////
/// Set ex and ey values for point pointed by the mouse.
///
/// Up to 3 y error dimensions possible.

void TGraphMultiErrors::SetPointError(Double_t exL, Double_t exH, Double_t eyL1, Double_t eyH1, Double_t eyL2, Double_t eyH2, Double_t eyL3, Double_t eyH3) {
    Int_t px = gPad->GetEventX();
    Int_t py = gPad->GetEventY();

    //localize point to be deleted
    Int_t ipoint = -2;
    Int_t i;
    // start with a small window (in case the mouse is very close to one point)
    for (i = 0; i < fNpoints; i++) {
	Int_t dpx = px - gPad->XtoAbsPixel(gPad->XtoPad(fX[i]));
	Int_t dpy = py - gPad->YtoAbsPixel(gPad->YtoPad(fY[i]));

	if (dpx*dpx+dpy*dpy < 25) {
	    ipoint = i;
	    break;
	}
    }

    if (ipoint == -2)
	return;

    SetPointEX(ipoint, exL, exH);

    if (fNErrorDimensions > 0)
	SetPointEY(ipoint, 0, eyL1, eyH1);
    if (fNErrorDimensions > 1)
	SetPointEY(ipoint, 1, eyL2, eyH2);
    if (fNErrorDimensions > 2)
	SetPointEY(ipoint, 2, eyL3, eyH3);
    gPad->Modified();
}

////////////////////////////////////////////////////////////////////////////////
/// Set ex and ey values for point number i.

void TGraphMultiErrors::SetPointError(Int_t i, Double_t exL, Double_t exH, Double_t* eyL, Double_t* eyH) {
    SetPointEX(i, exL, exH);
    SetPointEY(i, eyL, eyH);
}

////////////////////////////////////////////////////////////////////////////////
/// Set ex values for point number i.

void TGraphMultiErrors::SetPointEX(Int_t i, Double_t exL, Double_t exH) {
    SetPointEXL(i, exL);
    SetPointEXH(i, exH);
}

////////////////////////////////////////////////////////////////////////////////
/// Set exL value for point number i.

void TGraphMultiErrors::SetPointEXL(Int_t i, Double_t exL) {
    if (i < 0)
	return;

    if (i >= fNpoints) {
	// re-allocate the object
	TGraphMultiErrors::SetPoint(i, 0., 0.);
    }

    fExL[i] = exL;
}

////////////////////////////////////////////////////////////////////////////////
/// Set exH value for point number i.

void TGraphMultiErrors::SetPointEXH(Int_t i, Double_t exH) {
    if (i < 0)
	return;

    if (i >= fNpoints) {
	// re-allocate the object
	TGraphMultiErrors::SetPoint(i, 0., 0.);
    }

    fExH[i] = exH;
}

////////////////////////////////////////////////////////////////////////////////
/// Set ey values for point number i.

void TGraphMultiErrors::SetPointEY(Int_t i, Double_t* eyL, Double_t* eyH) {
    SetPointEYL(i, eyL);
    SetPointEYH(i, eyH);
}

////////////////////////////////////////////////////////////////////////////////
/// Set eyL values for point number i.

void TGraphMultiErrors::SetPointEYL(Int_t i, Double_t* eyL) {
    for (Int_t j = 0; j < fNErrorDimensions; j++)
        SetPointEYL(i, j, eyL[j]);
}

////////////////////////////////////////////////////////////////////////////////
/// Set eyH values for point number i.

void TGraphMultiErrors::SetPointEYH(Int_t i, Double_t* eyH) {
    for (Int_t j = 0; j < fNErrorDimensions; j++)
        SetPointEYH(i, j, eyH[j]);
}

////////////////////////////////////////////////////////////////////////////////
/// Set ey values in dimension dim for point number i.

void TGraphMultiErrors::SetPointEY(Int_t i, Int_t dim, Double_t eyL, Double_t eyH) {
    SetPointEYL(i, dim, eyL);
    SetPointEYH(i, dim, eyH);
}

////////////////////////////////////////////////////////////////////////////////
/// Set eyL value in dimension dim for point number i.

void TGraphMultiErrors::SetPointEYL(Int_t i, Int_t dim, Double_t eyL) {
    if (i < 0 || dim < 0)
	return;

    if (i >= fNpoints)
        // re-allocate the object
	TGraphMultiErrors::SetPoint(i, 0., 0.); 

    if (dim >= fNErrorDimensions)
        SetNErrorDimensions(dim + 1);

    fEyL[dim][i] = eyL;
    fEyLSum[i] = GetErrorYlow(i);
}

////////////////////////////////////////////////////////////////////////////////
/// Set eyH value in dimension dim for point number i.

void TGraphMultiErrors::SetPointEYH(Int_t i, Int_t dim, Double_t eyH) {
    if (i < 0 || dim < 0)
	return;

    if (i >= fNpoints)
	// re-allocate the object
	TGraphMultiErrors::SetPoint(i, 0., 0.);

    if (dim >= fNErrorDimensions)
        SetNErrorDimensions(dim + 1);

    fEyH[dim][i] = eyH;
    fEyHSum[i] = GetErrorYhigh(i);
}

////////////////////////////////////////////////////////////////////////////////
/// Set ey values in dimension dim.

void TGraphMultiErrors::SetDimensionEY(Int_t dim, Double_t* eyL, Double_t* eyH) {
    SetDimensionEYL(dim, eyL);
    SetDimensionEYH(dim, eyH);
}

////////////////////////////////////////////////////////////////////////////////
/// Set eyL values in dimension dim.

void TGraphMultiErrors::SetDimensionEYL(Int_t dim, Double_t* eyL) {
    for (Int_t i = 0; i < fNpoints; i++)
        SetPointEYL(i, dim, eyL[i]);
}

////////////////////////////////////////////////////////////////////////////////
/// Set eyH values in dimension dim.

void TGraphMultiErrors::SetDimensionEYH(Int_t dim, Double_t* eyH) {
    for (Int_t i = 0; i < fNpoints; i++)
        SetPointEYH(i, dim, eyH[i]);
}

////////////////////////////////////////////////////////////////////////////////
/// Update amount of y error dimensions and reallocate

void TGraphMultiErrors::SetNErrorDimensions(Int_t dim) {
    if (dim < 0) dim = 0;
    if (dim == fNErrorDimensions) return;

    Double_t** ps = AllocateArrays(2*dim, fNpoints);
    CopyAndReleaseY(ps, 0, dim, 0);
    if (dim > fNErrorDimensions)
	FillZeroY(fNErrorDimensions, dim, kFALSE);

    TAttFill* newAttFill = new TAttFill[dim];
    TAttLine* newAttLine = new TAttLine[dim];

    for (Int_t j = 0; j < TMath::Min(fNErrorDimensions, dim); j++) {
        fAttFill[j].Copy(newAttFill[j]);
	fAttLine[j].Copy(newAttLine[j]);
    }

    delete [] fAttFill;
    delete [] fAttLine;

    fAttFill = newAttFill;
    fAttLine = newAttLine;

    fNErrorDimensions = dim;
}

////////////////////////////////////////////////////////////////////////////////
/// Set TAttFill parameters of error dimension dim by copying from another TAttFill (-1 = Global and x errors)

void TGraphMultiErrors::SetAttFill(Int_t dim, TAttFill* taf) {
    if (dim == -1)
	taf->TAttFill::Copy(*this);
    else if (dim >= 0 && dim < fNErrorDimensions)
	taf->TAttFill::Copy(fAttFill[dim]);
}

////////////////////////////////////////////////////////////////////////////////
/// Set TAttLine parameters of error dimension dim by copying from another TAttLine (-1 = Global and x errors)

void TGraphMultiErrors::SetAttLine(Int_t dim, TAttLine* taf) {
    if (dim == -1)
	taf->TAttLine::Copy(*this);
    else if (dim >= 0 && dim < fNErrorDimensions)
	taf->TAttLine::Copy(fAttLine[dim]);
}

////////////////////////////////////////////////////////////////////////////////
/// Set Fill Color of error dimension dim (-1 = Global and x errors)

void TGraphMultiErrors::SetFillColor(Int_t dim, Color_t fcolor) {
    if (dim == -1)
	SetFillColor(fcolor);
    else if (dim >= 0 && dim < fNErrorDimensions)
        fAttFill[dim].SetFillColor(fcolor);
}

////////////////////////////////////////////////////////////////////////////////
/// Set Fill Color and Alpha of error dimension dim (-1 = Global and x errors)

void TGraphMultiErrors::SetFillColorAlpha(Int_t dim, Color_t fcolor, Float_t falpha) {
    if (dim == -1)
        SetFillColorAlpha(fcolor, falpha);
    else if (dim >= 0 && dim < fNErrorDimensions)
        fAttFill[dim].SetFillColorAlpha(fcolor, falpha);
}

////////////////////////////////////////////////////////////////////////////////
/// Set Fill Style of error dimension dim (-1 = Global and x errors)

void TGraphMultiErrors::SetFillStyle(Int_t dim, Style_t fstyle) {
    if (dim == -1)
        SetFillStyle(fstyle);
    else if (dim >= 0 && dim < fNErrorDimensions)
        fAttFill[dim].SetFillStyle(fstyle);
}

////////////////////////////////////////////////////////////////////////////////
/// Set Line Color of error dimension dim (-1 = Global and x errors)

void TGraphMultiErrors::SetLineColor(Int_t dim, Color_t lcolor) {
    if (dim == -1)
        SetLineColor(lcolor);
    else if (dim >= 0 && dim < fNErrorDimensions)
        fAttLine[dim].SetLineColor(lcolor);
}

////////////////////////////////////////////////////////////////////////////////
/// Set Line Color and Alpha of error dimension dim (-1 = Global and x errors)

void TGraphMultiErrors::SetLineColorAlpha(Int_t dim, Color_t lcolor, Float_t lalpha) {
    if (dim == -1)
        SetLineColorAlpha(lcolor, lalpha);
    else if (dim >= 0 && dim < fNErrorDimensions)
        fAttLine[dim].SetLineColorAlpha(lcolor, lalpha);
}

////////////////////////////////////////////////////////////////////////////////
/// Set Line Style of error dimension dim (-1 = Global and x errors)

void TGraphMultiErrors::SetLineStyle(Int_t dim, Style_t lstyle) {
    if (dim == -1)
        SetLineStyle(lstyle);
    else if (dim >= 0 && dim < fNErrorDimensions)
        fAttLine[dim].SetLineStyle(lstyle);
}

////////////////////////////////////////////////////////////////////////////////
/// Set Line Width of error dimension dim (-1 = Global and x errors)

void TGraphMultiErrors::SetLineWidth(Int_t dim, Width_t lwidth) {
    if (dim == -1)
        SetLineWidth(lwidth);
    else if (dim >= 0 && dim < fNErrorDimensions)
        fAttLine[dim].SetLineWidth(lwidth);
}

////////////////////////////////////////////////////////////////////////////////
/// Stream an object of class TGraphMultiErrors.

void TGraphMultiErrors::Streamer(TBuffer &R__b) {
   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TGraph::Streamer(R__b);
      R__b >> fNErrorDimensions;

      delete [] fExL;
      fExL = new Double_t[fNpoints];
      R__b.ReadFastArray(fExL,fNpoints);

      delete [] fExH;
      fExH = new Double_t[fNpoints];
      R__b.ReadFastArray(fExH,fNpoints);

      delete [] fEyL;
      fEyL = new Double_t*[fNErrorDimensions];
      for (Int_t i = 0; i < fNErrorDimensions; i++) {
	  fEyL[i] = new Double_t[fNpoints];
          R__b.ReadFastArray(fEyL[i],fNpoints);
      }

      delete [] fEyH;
      fEyH = new Double_t*[fNErrorDimensions];
      for (Int_t i = 0; i < fNErrorDimensions; i++) {
	  fEyH[i] = new Double_t[fNpoints];
          R__b.ReadFastArray(fEyH[i],fNpoints);
      }

      delete [] fEyLSum;
      fEyLSum = new Double_t[fNpoints];
      R__b.ReadFastArray(fEyLSum,fNpoints);

      delete [] fEyHSum;
      fEyHSum = new Double_t[fNpoints];
      R__b.ReadFastArray(fEyHSum,fNpoints);

      R__b >> fSumErrorsMode;

      delete [] fAttFill;
      fAttFill = new TAttFill[fNErrorDimensions];
      R__b.ReadFastArray(fAttFill, TAttFill::Class(), fNErrorDimensions);

      delete [] fAttLine;
      fAttLine = new TAttLine[fNErrorDimensions];
      R__b.ReadFastArray(fAttLine, TAttLine::Class(), fNErrorDimensions);

      R__b.CheckByteCount(R__s, R__c, TGraphMultiErrors::IsA());
   } else {
      R__c = R__b.WriteVersion(TGraphMultiErrors::IsA(), kTRUE);
      TGraph::Streamer(R__b);
      R__b << fNErrorDimensions;

      R__b.WriteFastArray(fExL,fNpoints);
      R__b.WriteFastArray(fExH,fNpoints);

      for (Int_t i = 0; i < fNErrorDimensions; i++)
	  R__b.WriteFastArray(fEyL[i],fNpoints);

      for (Int_t i = 0; i < fNErrorDimensions; i++)
	  R__b.WriteFastArray(fEyH[i],fNpoints);

      R__b.WriteFastArray(fEyLSum,fNpoints);
      R__b.WriteFastArray(fEyHSum,fNpoints);

      R__b << fSumErrorsMode;

      R__b.WriteFastArray(fAttFill, TAttFill::Class(), fNErrorDimensions);
      R__b.WriteFastArray(fAttLine, TAttLine::Class(), fNErrorDimensions);

      R__b.SetByteCount(R__c, kTRUE);
   }
}

////////////////////////////////////////////////////////////////////////////////
/// Swap points.

void TGraphMultiErrors::SwapPoints(Int_t pos1, Int_t pos2) {
    SwapValues(fExL, pos1, pos2);
    SwapValues(fExH, pos1, pos2);

    for (Int_t j = 0; j <= fNErrorDimensions; j++) {
	SwapValues(fEyL[j], pos1, pos2);
	SwapValues(fEyH[j], pos1, pos2);
    }

    TGraph::SwapPoints(pos1, pos2);
}

////////////////////////////////////////////////////////////////////////////////
/// Implementation similar to TGraph::Paint and TGraphPainter::PaintHelper
///
/// Subject to be removed if class becomes part of ROOT

void TGraphMultiErrors::Paint(Option_t* opt) {
    TString tsOpt = opt;
    tsOpt.ToLower();

    if (tsOpt.CountChar(';') > fNErrorDimensions)
        Warning("Paint", "More option parts than possible!");

    Bool_t pfc = tsOpt.Contains("pfc");
    Bool_t plc = tsOpt.Contains("plc");
    Bool_t pmc = tsOpt.Contains("pmc");

    if (pfc || plc || pmc) {
	Int_t col = gPad->NextPaletteColor();

	if (pfc)
	    SetFillColor(col);

	if (plc)
	    SetLineColor(col);

	if (pmc)
	    SetMarkerColor(col);

        tsOpt.ReplaceAll("pfc", "");
        tsOpt.ReplaceAll("plc", "");
        tsOpt.ReplaceAll("pmc", "");
    }

    Bool_t rx = tsOpt.Contains("rx");
    Bool_t ry = tsOpt.Contains("ry");

    if (rx || ry)
	PaintReverse(tsOpt.Data());
    else {
        TGraphMultiErrors::PaintGraphMultiErrors(this, tsOpt.Data());

	// Paint the fit parameters if needed.
	if (fFunctions) {
	    if (fFunctions->Last()) {
		if (fFunctions->Last()->InheritsFrom(TF1::Class())) {
		    TGraphPainter* painter = (TGraphPainter*) TVirtualGraphPainter::GetPainter();

		    if (painter)
			painter->PaintStats(this, (TF1*) fFunctions->Last());
		}
	    }
	}
    }
}

////////////////////////////////////////////////////////////////////////////////
/// Implementation of TGraphPainter::PaintReverse
///
/// Subject to be removed if class becomes part of ROOT

void TGraphMultiErrors::PaintReverse(Option_t* opt) {
    TString tsOpt = opt;
    tsOpt.ToLower();
    TH1F* theHist = (TH1F*) GetHistogram();
 
    Bool_t lrx = tsOpt.Contains("rx");
    Bool_t lry = tsOpt.Contains("ry");
 
    Double_t LOX = theHist->GetXaxis()->GetLabelOffset();
    Double_t TLX = theHist->GetXaxis()->GetTickLength();
    Double_t LOY = theHist->GetYaxis()->GetLabelOffset();
    Double_t TLY = theHist->GetYaxis()->GetTickLength();
    Int_t XACOL  = theHist->GetXaxis()->GetAxisColor();
    Int_t YACOL  = theHist->GetYaxis()->GetAxisColor();
 
    if (tsOpt.Contains("a")) {
       if (lrx) {
          theHist->GetXaxis()->SetTickLength(0.);
          theHist->GetXaxis()->SetLabelOffset(999.);
          theHist->GetXaxis()->SetAxisColor(gPad->GetFrameFillColor());
       }

       if (lry) {
          theHist->GetYaxis()->SetTickLength(0.);
          theHist->GetYaxis()->SetLabelOffset(999.);
          theHist->GetYaxis()->SetAxisColor(gPad->GetFrameFillColor());
       }

       theHist->Paint("0");
       tsOpt.ReplaceAll("a", "");
    }
 
    Int_t     N  = GetN();
    Double_t *X  = GetX();
    Double_t *Y  = GetY();
    Double_t XA1 = GetXaxis()->GetXmin();
    Double_t XA2 = GetXaxis()->GetXmax();
    Double_t YA1 = GetYaxis()->GetXmin();
    Double_t YA2 = GetYaxis()->GetXmax();
    Double_t dX  = XA1 + XA2;
    Double_t dY  = YA1 + YA2;
    std::vector<Double_t> newX(N);
    std::vector<Double_t> newY(N);
 
    if (lrx) {
       tsOpt.ReplaceAll("rx", "");
 
       Double_t GL = 0.;
       theHist->GetXaxis()->SetTickLength(0.);
       theHist->GetXaxis()->SetLabelOffset(999.);
 
       // Redraw the new X axis
       gPad->Update();
       TString optax = "-SDH";

       if (gPad->GetGridx()) {
          GL = (YA2-YA1)/(gPad->GetY2() - gPad->GetY1());
          optax.Append("W");
       }

       TGaxis *theNewAxis = new TGaxis(gPad->GetUxmax(),
                                       gPad->GetUymin(),
                                       gPad->GetUxmin(),
                                       gPad->GetUymin(),
                                       GetXaxis()->GetXmin(),
                                       GetXaxis()->GetXmax(),
                                       theHist->GetNdivisions("X"),
                                       optax.Data(), -GL);
       theNewAxis->SetLabelFont(GetXaxis()->GetLabelFont());
       theNewAxis->SetLabelSize(GetXaxis()->GetLabelSize());
       theNewAxis->SetLabelColor(GetXaxis()->GetLabelColor());
       theNewAxis->SetTickLength(TLX);
       theNewAxis->SetLabelOffset(LOX - GetXaxis()->GetLabelSize());
       theNewAxis->Paint();
 
       // Reverse X coordinates
       for (Int_t i = 0; i < N; i++)
	   newX[i] = dX - X[i];
    } else {
	for (Int_t i = 0; i < N; i++)
	    newX[i] = X[i];
    }
 
    if (lry) {
       tsOpt.ReplaceAll("ry", "");
       Double_t GL = 0.;
 
       // Redraw the new Y axis
       gPad->Update();
       TString optax = "-SDH";
 
       if (gPad->GetGridy()) {
          GL = (XA2-XA1)/(gPad->GetX2() - gPad->GetX1());
          optax.Append("W");
       }

       TGaxis *theNewAxis = new TGaxis(gPad->GetUxmin(),
                                    gPad->GetUymax(),
                                    gPad->GetUxmin(),
                                    gPad->GetUymin(),
                                    GetYaxis()->GetXmin(),
                                    GetYaxis()->GetXmax(),
                                    theHist->GetNdivisions("Y"),
                                    optax.Data(), GL);
       theNewAxis->SetLabelFont(GetYaxis()->GetLabelFont());
       theNewAxis->SetLabelSize(GetYaxis()->GetLabelSize());
       theNewAxis->SetLabelColor(GetYaxis()->GetLabelColor());
       theNewAxis->SetTickLength(-TLY);
       theNewAxis->SetLabelOffset(LOY - TLY);
       theNewAxis->Paint();
 
       // Reverse Y coordinates
       for (Int_t i = 0; i < N; i++)
	   newY[i] = dY - Y[i];
    } else {
	for (Int_t i = 0; i < N; i++)
	    newY[i] = Y[i];
    }
 
    // Create the new reversed graph
    TGraphMultiErrors* theNewGraph = (TGraphMultiErrors*) Clone();

    for (Int_t i=0; i<N; i++)
	theNewGraph->SetPoint(i, newX[i], newY[i]);

    theNewGraph->SetMarkerStyle(GetMarkerStyle());
    theNewGraph->SetMarkerColor(GetMarkerColor());
    theNewGraph->SetLineStyle(GetLineStyle());
    theNewGraph->SetLineColor(GetLineColor());
 
    theNewGraph->Paint(tsOpt.Data());
 
    theHist->GetXaxis()->SetLabelOffset(LOX);
    theHist->GetXaxis()->SetTickLength(TLX);
    theHist->GetYaxis()->SetLabelOffset(LOY);
    theHist->GetYaxis()->SetTickLength(TLY);
    theHist->GetXaxis()->SetAxisColor(XACOL);
    theHist->GetYaxis()->SetAxisColor(YACOL);
}

////////////////////////////////////////////////////////////////////////////////
/// Implementation similar to TGraphPainter::PaintGraphAsymmErrors
///
/// Subject to be moved to class TGraphPainter if class becomes part of ROOT
///
/// To be able to define different drawing options for the multiple error dimensions
/// the option string can consist of multiple blocks separated by semicolons.
/// The painting method separates the options in multiple options for each
/// y error dimension and one for basic painting and the x errors.
///
/// In case there are <= NErrorDimensions blocks given, the first block is used for
/// basic painting and for the first dimension of y errors. Y error dimensions without
/// an individual block are painted with "".
/// Tn case there are NErrorDimensions + 1 given, the first block is used only for
/// basic painting. The remaining blocks are distributed over the y error dimensions
/// In case there are > NErrorDimensions + 1 blocks given an error is returned.
///
/// All drawing options of TGraphAsymmErrors are implemented.
/// For explanation of the drawing options see TGraphPainter::PaintGraphAsymmErrors
/// Additionally one can specify x0 or y0 to skip points with x = 0 or y = 0
/// The Draw option s=%f can be used to multiply the corresponding x errors with %f
/// This is useful in combination with e.g. option 2 if the boxes are supposed to have
/// only half the width of the bin, in this case the option would be s=0.5
/// Per default the Fill and Line Styles of the Graph are being used for all error
/// dimensions. To use the specific ones add the draw option s to the first block.

void TGraphMultiErrors::PaintGraphMultiErrors(TGraphMultiErrors* tg, Option_t* opt) {
    Int_t NErrorDimensions = tg->GetNErrorDimensions();

    TString tsOpt = opt;
    tsOpt.ToLower();

    TString* options = new TString[NErrorDimensions + 1];
    Int_t filled = 0;

    if (tsOpt.CountChar(';') < NErrorDimensions) {
	options[0] = tsOpt.Contains(";") ? tsOpt(0, tsOpt.First(';')) : tsOpt.Copy();
	filled++;
    }

    Ssiz_t firstSemicolon;
    while ((firstSemicolon = tsOpt.First(';')) != kNPOS && filled <= NErrorDimensions) {
	options[filled] = tsOpt(0, firstSemicolon);
	tsOpt = tsOpt(firstSemicolon + 1, tsOpt.Length());
	filled++;
    }

    if (filled <= NErrorDimensions) {
	options[filled] = tsOpt.Copy();
	filled++;
    }

    for (Int_t i = filled; i <= NErrorDimensions; i++)
        options[i] = "";


    TGraphPainter* painter = (TGraphPainter*) TVirtualGraphPainter::GetPainter();

    if (!painter)
	return;


    Double_t*  xline = NULL;
    Double_t** yline = new Double_t*[NErrorDimensions];
    Int_t if1 = 0;
    Int_t if2 = 0;
    Double_t xb[4], yb[4];

    const Int_t kBASEMARKER = 8;
    Double_t s2x, s2y, symbolsize, sbase;
    Double_t x, y, xl1, xl2, xr1, xr2, yup1, yup2, ylow1, ylow2, tx, ty;
    static Float_t cxx[15] = {1., 1., 0.6, 0.6, 1., 1., 0.6, 0.5, 1., 0.6, 0.6, 1., 0.6, 1., 1.};
    static Float_t cyy[15] = {1., 1., 1. , 1. , 1., 1., 1. , 1. , 1., 0.5, 0.6, 1., 1. , 1., 1.};
    Int_t theNpoints = tg->GetN();
    Double_t*  theX   = tg->GetX();
    Double_t*  theY   = tg->GetY();
    Double_t*  theExL = tg->GetEXlow();
    Double_t*  theExH = tg->GetEXhigh();
    Double_t** theEyL = new Double_t*[NErrorDimensions];
    Double_t** theEyH = new Double_t*[NErrorDimensions];

    for (Int_t j = 0; j < NErrorDimensions; j++) {
        theEyL[j] = tg->GetEYlow(j);
	theEyH[j] = tg->GetEYhigh(j);
    }

    if (!theX || !theY || !theExL || !theExH || !theEyL || !theEyH)
        return;

    Bool_t*   DrawErrors = new Bool_t  [NErrorDimensions];
    Bool_t    AnyErrors  = kFALSE;
    Bool_t    NoErrorsX  = kTRUE;
    Bool_t    Option0X   = kFALSE;
    Bool_t    DrawMarker = kFALSE;
    Bool_t*   Braticks   = new Bool_t  [NErrorDimensions];
    Bool_t*   Brackets   = new Bool_t  [NErrorDimensions];
    Bool_t*   EndLines   = new Bool_t  [NErrorDimensions];
    Char_t**  ArrowOpt   = new Char_t* [NErrorDimensions];
    Bool_t*   Option5    = new Bool_t  [NErrorDimensions];
    Bool_t*   Option4    = new Bool_t  [NErrorDimensions];
    Bool_t*   Option3    = new Bool_t  [NErrorDimensions];
    Bool_t    AnyOption3 = kFALSE;
    Bool_t*   Option2    = new Bool_t  [NErrorDimensions];
    Bool_t*   Option0    = new Bool_t  [NErrorDimensions];
    Bool_t    AnyOption0 = kFALSE;
    Double_t* Scale      = new Double_t[NErrorDimensions];

    for (Int_t j = 0; j < NErrorDimensions; j++) {
        if (options[j + 1].Contains("s=")) {
	    sscanf(strstr(options[j + 1].Data(), "s="), "s=%lf", &Scale[j]);
            options[j + 1].ReplaceAll(options[j + 1](TRegexp("s=*[0-9]\\.*[0-9]")), "");
	} else
	    Scale[j] = 1.;

	DrawErrors[j] = !options[j + 1].Contains("x");
	AnyErrors    |=  DrawErrors[j];
        Braticks[j]   =  options[j + 1].Contains("[]");
	Brackets[j]   =  options[j + 1].Contains("||") || Braticks[j];
	EndLines[j]   = !options[j + 1].Contains("z");

	if      (options[j + 1].Contains("|>")) ArrowOpt[j] = (Char_t*) "|>";
	else if (options[j + 1].Contains(">"))  ArrowOpt[j] = (Char_t*) ">";
        else                                    ArrowOpt[j] = NULL;

        Option5[j]    = options[j + 1].Contains("5");
        Option4[j]    = options[j + 1].Contains("4");
	Option3[j]    = options[j + 1].Contains("3") || Option4[j];
        AnyOption3   |= Option3[j];
	Option2[j]    = options[j + 1].Contains("2") || Option5[j];
	Option0[j]    = options[j + 1].Contains("0");
	AnyOption0   |= Option0[j];

        NoErrorsX    &=  (Option3[j] || Option2[j]);
        Option0X     |= !(Option3[j] || Option2[j]) && Option0[j];
        DrawMarker   |= !(Brackets[j] || Option3[j] || Option2[j]);
    }

    Bool_t Draw0PointsX = !options[0].Contains("x0") && (gPad->GetLogx() == 0);
    Bool_t Draw0PointsY = !options[0].Contains("y0") && (gPad->GetLogy() == 0);
    options[0].ReplaceAll("x0", "");
    options[0].ReplaceAll("y0", "");

    Bool_t DrawErrorsX  = !options[0].Contains("x");
    Bool_t BraticksX    =  options[0].Contains("[]");
    Bool_t BracketsX    =  options[0].Contains("||") || BraticksX;
    Bool_t EndLinesX    = !options[0].Contains("z");

    Char_t* ArrowOptX = NULL;
    if      (options[0].Contains("|>")) ArrowOptX = (Char_t*) "|>";
    else if (options[0].Contains(">"))  ArrowOptX = (Char_t*) ">";

    Double_t ScaleX = 1.;
    if (options[0].Contains("s=")) {
	sscanf(strstr(options[0].Data(), "s="), "s=%lf", &ScaleX);
        options[0].ReplaceAll(options[0](TRegexp("s=*[0-9]\\.*[0-9]")), "");
    }

    if (!AnyErrors && !DrawErrorsX) {
	painter->PaintGraphSimple(tg, options[0].Data());
        return;
    }

    Bool_t DrawAxis         = options[0].Contains("a");
    Bool_t IndividualStyles = options[0].Contains("s");

    if (DrawAxis)
        painter->PaintGraphSimple(tg, options[0].Data());

    Int_t NPointsInside = AnyOption0 ? theNpoints : 0;

    for (Int_t i = 0; i < theNpoints && !AnyOption0; i++) {
	x = gPad->XtoPad(theX[i]);
	y = gPad->YtoPad(theY[i]);

	if ((x >= gPad->GetUxmin()) && (x <= gPad->GetUxmax()) && (y >= gPad->GetUymin()) && (y <= gPad->GetUymax()) && (Draw0PointsX || theX[i] != 0.) && (Draw0PointsY || theY[i] != 0.))
	    NPointsInside++;
    }

    if (AnyOption3) {
	xline = new Double_t[2*NPointsInside];

	if (!xline) {
	    //Error("Paint", "too many points, out of memory");
	    return;
	}

        if1 = 1;
	if2 = 2*NPointsInside;
    }

    for (Int_t j = 0; j < NErrorDimensions; j++) {
	if (Option3[j] && DrawErrors[j]) {
	    yline[j] = new Double_t[2*NPointsInside];

	    if (!yline[j]) {
		//Error("Paint", "too many points, out of memory");
		return;
	    }
	}
    }

    tg->TAttLine::Modify();

    TArrow arrow;
    arrow.SetLineWidth(tg->GetLineWidth());
    arrow.SetLineColor(tg->GetLineColor());
    arrow.SetFillColor(tg->GetFillColor());

    TBox box;
    Double_t x1b, y1b, x2b, y2b;
    box.SetLineWidth(tg->GetLineWidth());
    box.SetLineColor(tg->GetLineColor());
    box.SetFillColor(tg->GetFillColor());
    box.SetFillStyle(tg->GetFillStyle());
 
    symbolsize  = tg->GetMarkerSize();
    sbase       = symbolsize * kBASEMARKER;
    Int_t mark  = tg->GetMarkerStyle();
    Double_t cx = 0.;
    Double_t cy = 0.;

    if (mark >= 20 && mark <= 34) {
       cx = cxx[mark - 20];
       cy = cyy[mark - 20];
    }
 
    // Define the offset of the error bars due to the symbol size
    s2x =  gPad->PixeltoX(Int_t(0.5 * sbase)) - gPad->PixeltoX(0);
    s2y = -gPad->PixeltoY(Int_t(0.5 * sbase)) + gPad->PixeltoY(0);
    Int_t dxend = Int_t(gStyle->GetEndErrorSize());
    tx  =  gPad->PixeltoX(dxend) - gPad->PixeltoX(0);
    ty  = -gPad->PixeltoY(dxend) + gPad->PixeltoY(0);
    Float_t asize = 0.6 * symbolsize * kBASEMARKER / gPad->GetWh();
 
    gPad->SetBit(TGraph::kClipFrame, tg->TestBit(TGraph::kClipFrame));

    for (Int_t i = 0; i < theNpoints; i++) {
	x = gPad->XtoPad(theX[i]);
	y = gPad->YtoPad(theY[i]);

        Bool_t isOutside = (x < gPad->GetUxmin()) || (x > gPad->GetUxmax()) || (y < gPad->GetUymin()) || (y > gPad->GetUymax());

        if ((isOutside && !AnyOption0) || (!Draw0PointsX && theX[i] == 0.) || (!Draw0PointsY && theY[i] == 0.))
	    continue;

	if (AnyOption3) {
	    if (isOutside) {
                if (x < gPad->GetUxmin()) x = gPad->GetUxmin();
		if (x > gPad->GetUxmax()) x = gPad->GetUxmax();
		if (y < gPad->GetUymin()) y = gPad->GetUymin();
		if (y > gPad->GetUymax()) y = gPad->GetUymax();
	    }

            xline[if1 - 1] = x;
	    xline[if2 - 1] = x;

            if1++;
	    if2--;
	}

	for (Int_t j = 0; j < NErrorDimensions; j++) {
	    if (!DrawErrors[j])
                continue;

	    //  draw the error rectangles
	    if (Option2[j] && (!isOutside || Option0[j])) {
		if (IndividualStyles) {
                    box.SetLineWidth(tg->GetLineWidth(j));
		    box.SetLineColor(tg->GetLineColor(j));
		    box.SetFillColor(tg->GetFillColor(j));
		    box.SetFillStyle(tg->GetFillStyle(j));
		}

		x1b = gPad->XtoPad(theX[i] - Scale[j] * theExL[i]);
		y1b = gPad->YtoPad(theY[i] - theEyL[j][i]);
		x2b = gPad->XtoPad(theX[i] + Scale[j] * theExH[i]);
		y2b = gPad->YtoPad(theY[i] + theEyH[j][i]);
		if (x1b < gPad->GetUxmin()) x1b = gPad->GetUxmin();
		if (x1b > gPad->GetUxmax()) x1b = gPad->GetUxmax();
		if (y1b < gPad->GetUymin()) y1b = gPad->GetUymin();
		if (y1b > gPad->GetUymax()) y1b = gPad->GetUymax();
		if (x2b < gPad->GetUxmin()) x2b = gPad->GetUxmin();
		if (x2b > gPad->GetUxmax()) x2b = gPad->GetUxmax();
		if (y2b < gPad->GetUymin()) y2b = gPad->GetUymin();
		if (y2b > gPad->GetUymax()) y2b = gPad->GetUymax();
		if (Option5[j]) box.PaintBox(x1b, y1b, x2b, y2b, "l");
		else            box.PaintBox(x1b, y1b, x2b, y2b);
	    }

            //  keep points for fill area drawing
	    if (Option3[j]) {
		if (!isOutside || Option0[j]) {
		    yline[j][if1 - 2] = gPad->YtoPad(theY[i] + theEyH[j][i]);
		    yline[j][if2]     = gPad->YtoPad(theY[i] - theEyL[j][i]);
		} else {
		    yline[j][if1 - 2] = gPad->GetUymin();
		    yline[j][if2]     = gPad->GetUymin();
		}
	    }

	    if (IndividualStyles) {
                tg->GetAttLine(j)->Modify();

		arrow.SetLineWidth(tg->GetLineWidth(j));
		arrow.SetLineColor(tg->GetLineColor(j));
		arrow.SetFillColor(tg->GetFillColor(j));
	    }

            ylow1 = y - s2y*cy;
	    ylow2 = gPad->YtoPad(theY[i] - theEyL[j][i]);
	    if (ylow2 < gPad->GetUymin()) ylow2 = gPad->GetUymin();
	    if (ylow2 < ylow1 && DrawErrors[j] && !Option2[j] && !Option3[j] && (!isOutside || Option0[j])) {
		if (ArrowOpt[j])
		    arrow.PaintArrow(x, ylow1, x, ylow2, asize, ArrowOpt[j]);
		else {
		    if (!Brackets[j])
			gPad->PaintLine(x, ylow1, x, ylow2);
		    if (EndLines[j]) {
			if (Braticks[j]) {
			    xb[0] = x - tx; yb[0] = ylow2 + ty;
			    xb[1] = x - tx; yb[1] = ylow2;
			    xb[2] = x + tx; yb[2] = ylow2;
			    xb[3] = x + tx; yb[3] = ylow2 + ty;
			    gPad->PaintPolyLine(4, xb, yb);
			} else
			    gPad->PaintLine(x - tx, ylow2, x + tx, ylow2);
		    }
		}
	    }

            yup1 = y + s2y*cy;
	    yup2 = gPad->YtoPad(theY[i] + theEyH[j][i]);
	    if (yup2 > gPad->GetUymax()) yup2 = gPad->GetUymax();
	    if (yup2 > yup1 && DrawErrors[j] && !Option2[j] && !Option3[j] && (!isOutside || Option0[j])) {
		if (ArrowOpt[j])
		    arrow.PaintArrow(x, yup1, x, yup2, asize, ArrowOpt[j]);
		else {
		    if (!Brackets[j])
			gPad->PaintLine(x, yup1, x, yup2);
		    if (EndLines[j]) {
			if (Braticks[j]) {
			    xb[0] = x - tx; yb[0] = yup2 - ty;
			    xb[1] = x - tx; yb[1] = yup2;
			    xb[2] = x + tx; yb[2] = yup2;
			    xb[3] = x + tx; yb[3] = yup2 - ty;
			    gPad->PaintPolyLine(4, xb, yb);
			} else
			    gPad->PaintLine(x - tx, yup2, x + tx, yup2);
		    }
		}
	    }
	}

	if (DrawErrorsX) {
            if (IndividualStyles) {
                tg->TAttLine::Modify();

		arrow.SetLineWidth(tg->GetLineWidth());
		arrow.SetLineColor(tg->GetLineColor());
		arrow.SetFillColor(tg->GetFillColor());
	    }

	    xl1 = x - s2x*cx;
	    xl2 = gPad->XtoPad(theX[i] - ScaleX * theExL[i]);
	    if (xl1 > xl2 && !NoErrorsX && (!isOutside || Option0X)) {
		if (ArrowOptX)
		    arrow.PaintArrow(xl1, y, xl2, y, asize, ArrowOptX);
		else {
		    if (!BracketsX)
			gPad->PaintLine(xl1, y, xl2, y);
		    if (EndLinesX) {
			if (BraticksX) {
			    xb[0] = xl2 + tx; yb[0] = y - ty;
			    xb[1] = xl2;      yb[1] = y - ty;
			    xb[2] = xl2;      yb[2] = y + ty;
			    xb[3] = xl2 + tx; yb[3] = y + ty;
			    gPad->PaintPolyLine(4, xb, yb);
			} else
			    gPad->PaintLine(xl2, y - ty, xl2, y + ty);
		    }
		}
	    }

	    xr1 = x + s2x*cx;
	    xr2 = gPad->XtoPad(theX[i] + ScaleX * theExH[i]);
	    if (xr1 < xr2 && !NoErrorsX && (!isOutside || Option0X)) {
		if (ArrowOptX)
		    arrow.PaintArrow(xr1, y, xr2, y, asize, ArrowOptX);
		else {
		    if (!BracketsX)
			gPad->PaintLine(xr1, y, xr2, y);
		    if (EndLinesX) {
			if (BraticksX) {
			    xb[0] = xr2 - tx; yb[0] = y - ty;
			    xb[1] = xr2;      yb[1] = y - ty;
			    xb[2] = xr2;      yb[2] = y + ty;
			    xb[3] = xr2 - tx; yb[3] = y + ty;
			    gPad->PaintPolyLine(4, xb, yb);
			} else
			    gPad->PaintLine(xr2, y - ty, xr2, y + ty);
		    }
		}
	    }
	}
    }

    if (DrawMarker && !DrawAxis)
	painter->PaintGraphSimple(tg, options[0].Data());
    gPad->ResetBit(TGraph::kClipFrame);

    TGraph* tgDummy = new TGraph();
    tg->TAttFill::Copy(*tgDummy);
    tg->TAttLine::Copy(*tgDummy);
    tg->TAttMarker::Copy(*tgDummy);

    for (Int_t j = 0; j < NErrorDimensions; j++) {
	if (Option3[j] && DrawErrors[j]) {
	    if (IndividualStyles) {
                tg->GetAttFill(j)->Copy(*tgDummy);
		tg->GetAttLine(j)->Copy(*tgDummy);
	    }

	    Int_t logx = gPad->GetLogx();
	    Int_t logy = gPad->GetLogy();
	    gPad->SetLogx(0);
	    gPad->SetLogy(0);
	    if (Option4[j]) painter->PaintGraph(tgDummy, 2*NPointsInside, xline, yline[j], "FC");
	    else            painter->PaintGraph(tgDummy, 2*NPointsInside, xline, yline[j], "F");
	    gPad->SetLogx(logx);
	    gPad->SetLogy(logy);
	    delete [] yline[j];
	}
    }

    if (AnyOption3) {
        delete [] xline;
	delete [] yline;
    }
}
