/**
 * @file      tests/Combiner.C
 * @copyright Christian Holm Christensen
 * @brief     Part of the GraphSysErr test suite
 */
ifndef __CINT__
# include <TF1.h>
# include <TList.h>
# include <TLine.h>
# include <TH1.h>
# include <TMath.h>
# include <TClonesArray.h>
# include <TCanvas.h>
#else
class TF1;
class TClonesArray;
class TLine;
class TCanvas;
#endif
// From http://www.slac.stanford.edu/~barlow/java/

struct Combiner : public TObject
{
  /**
   * An experimental observation 
   */
  struct Observation : public TObject 
  {
    /** Value @f$ x_i@f$ */
    Double_t fX;
    /** Low error @f$ \sigma_i^-@f$ */
    Double_t fEl;
    /** High error @f$ \sigma_i^+@f$ */
    Double_t fEh;
    /** 
     * Create a single obersvation 
     * 
     * @param x  Value @f$ x_i@f$
     * @param el Low error @f$ \sigma_i^-@f$ on @f$ x_i@f$ 
     * @param eh High error @f$ \sigma_i^+@f$ on @f$ x_i@f$ 
     */
    Observation(Double_t x=0, Double_t el=0, Double_t eh=0)
      : fX(x), fEl(el), fEh(eh)
    {    
    }
    /** 
     * Virtual destructor 
     */
    virtual ~Observation() {}
    /** 
     * Calculate 
     * 
     * @f[ 
     *   s_i = \sigma_i^+ \sigma_i^- / (\sigma_i^+ + \sigma_i^-)
     * @f]
     * 
     * 
     * @return @f$ s_i@f$
     */
    Double_t S() const { return 2 * fEl * fEh / (fEl + fEh); }
    /** 
     * Calculate 
     * 
     * @f[ 
     *   s_i' = (\sigma_i^+ - \sigma_i^-) / (\sigma_i^+ + \sigma_i^-)
     * @f]
     * 
     * 
     * @return @f$ s_i'@f$
     */
    Double_t Sprime() const { return (fEh - fEl) / (fEh + fEh);  }
    /** 
     * Calculate 
     * 
     * @f[ 
     *   V_i = \sigma_i^+ \sigma_i^-
     * @f]
     * 
     * 
     * @return @f$ V_i@f$
     */
    Double_t V() const  { return fEl * fEh; }
    /** 
     * Calculate 
     * 
     * @f[ 
     *   V_i' = \sigma_i^+ - \sigma_i^-
     * @f]
     * 
     * 
     * @return @f$ V_i'@f$
     */
    Double_t Vprime() const { return fEh - fEl;  }
    /** 
     * Lower bound 
     * 
     * @return @f$ x_i - 3\sigma_i^+@f$ 
     */
    virtual Double_t Low() const { return fX - 3 * fEl; }
    /** 
     * Upper bound 
     * 
     * @return @f$ x_i + 3\sigma_i^+@f$ 
     */
    virtual Double_t High() const { return fX + 3 * fEh; }
    /** 
     * Print to standard output 
     *
     * @param option Not used 
     */
    virtual void Print(Option_t* option="") const
    {
      Printf("%7.5f  -%7.5f +%7.5f", fX, fEl, fEh);
    }
    ClassDef(Observation,1); // An experimental observation 
  };
  
  /**
   * The final result 
   */
  struct Result : public Observation
  {
    /** The final @f$\chi^2 @f$ */
    Double_t fChi2;
    /** Lower bound to use */
    Double_t fLower;
    /** Upper bound to use */
    Double_t fUpper;
    /** 
     * The final result 
     * 
     * @param x     Best estimate of @f$ x@f$ 
     * @param el    Best estimate of @f$ \sigma^-@f$ 
     * @param eh    Best estimate of @f$ \sigma^+@f$ 
     * @param chi2  @f$\chi^2@f$ of best estimate 
     * @param low   The lower bound of the source data
     * @param high  The upper bound of the source data
     */
    Result(Double_t x=0, Double_t el=0, Double_t eh=0,
	   Double_t chi2=0, Double_t low=0, Double_t high=0)
      : Observation(x, el, eh),
	fChi2(chi2),
	fLower(low),
	fUpper(high)
    {}
    /** 
     * Lower bound 
     * 
     * @return @f$ x_i - 3\sigma_i^+@f$ 
     */
    Double_t Low() const { return fLower; }
    /** 
     * Upper bound 
     * 
     * @return @f$ x_i + 3\sigma_i^+@f$ 
     */
    Double_t High() const { return fUpper; }
    /** 
     * Print to standard output 
     *
     * @param option Not used 
     */
    virtual void Print(Option_t* option="") const
    {
      Printf("%7.3f  -%7.5f +%7.5f  %5.2f", fX, fEl, fEh, fChi2);
    }
    ClassDef(Result,1); // Final result 
  };
  /** 
   * Difference 
   */
  struct Diff : public Result
  {
    Diff(const Result& r, const Result& e)
      : Result(e.fX    - r.fX,
	       e.fEl   - r.fEl,
	       e.fEh   - r.fEh,
	       e.fChi2 - r.fChi2,
	       r.Low(),  r.High())
    {
    }
    virtual void Print(Option_t* option="") const
    {
      Printf("%+7.3f  %+8.5f %+8.5f  %+5.2f", fX, fEl, fEh, fChi2);
    }
    ClassDef(Diff,1); // Result result 
  };
    
  typedef Double_t (*Wrapper_t)(Double_t*,Double_t*);
  TClonesArray fData;
  Result*      fResult;
  /** 
   * Constructor 
   */
  Combiner() : fData("Combiner::Observation") { fData.SetOwner(); }
  /** 
   * Clear the list 
   *
   * @param option Not used 
   */      
  /** 
   * Virtual destructor 
   */
  virtual ~Combiner() { fData.Clear(); if (fResult) delete fResult; }
  /** 
   * @{ 
   * @name The data store 
   */
  /** 
   * Clear the internal data 
   * 
   * @param option Not used
   */
  void Clear(Option_t* option="")
  {
    fData.Clear();
    if (fResult) delete fResult;
    fResult = 0;
  }
  /** 
   * Add an obervation 
   * 
   * @param r Observation
   */
  void Add(const Observation& r)
  {
    Add(r.fX,r.fEl,r.fEh);
  }
  /** 
   * Add an observation 
   * 
   * @param x  @f$ x_i@f$ 
   * @param el @f$ \sigma_i^-@f$  
   * @param eh @f$ \sigma_i^+@f$
   */
  void Add(Double_t x, Double_t el, Double_t eh)
  {
    new (fData[fData.GetEntries()]) Observation(x,el,eh);
  }
  /** 
   * Print content of the list 
   * 
   * @param option not used
   */
  void Print(Option_t* option="") const
  {
    TIter next(&fData);
    Observation* r = 0;
    while ((r = static_cast<Observation*>(next())))
      r->Print(option);
  }
  /* @} */
  
  /** 
   * Calculate the weight 
   *
   * @param r Observation
   * 
   * @return @f$ W@f$ 
   */
  virtual Double_t W(const Observation& r) const = 0;
  /** 
   * Calculate the weight based on a guess of best @f$ x'@f$ 
   * 
   * @param guess Current guess @f$ x'@f$ 
   * @param r  	  Observation
   * 
   * @return @f$ W(x')@f$ 
   */
  virtual Double_t StepW(Double_t guess, const Observation& r) const = 0;
  /** 
   * Calculate the bias. 
   * 
   * @return @f$\delta(x')@f$ 
   */
  virtual Double_t StepOffset(Double_t guess, const Observation& r) const = 0;
  /** 
   * Calculate the contribution variance to the @f$\chi^2@f$ with
   * the guess @f$x'@f$. 
   *
   * @return @f$ v(x')@f$ 
   */
  virtual Double_t VarTerm(Double_t guess, const Observation& r) const = 0;
  /** 
   * Calculate the contribution variance to the @f$\chi^2@f$ with
   * the guess @f$ x'@f$. 
   *
   * @f[
   *   t_i(x') = (x' - x_i)^2 / v_i(x')
   * @f]
   *
   * where @f$ v_i(x')@f$ is the term variance
   *
   * @param guess @f$ x'@f$  
   * @param r     Obersvation 
   *
   * @return @f$ t(x')@f$ 
   */
  Double_t ChiTerm(Double_t guess, const Observation& r) const
  {
    Double_t var = VarTerm(guess, r);
    if (var <= 0) return -1000;

    return TMath::Power(guess - r.fX, 2) / var;
  }
  /** 
   * Calculate the @f$ \chi^2(x')@f$ where @f$ x'@f$ is current guess
   * at the observation.  
   * 
   * @param guess   Current guess @f$ x'@f$ 
   * @param chi2    Optional old @f$ \chi^2@f$ from best @f$ x@f$ value 
   * 
   * @return @f$ \chi^2(x')@f$
   */
  Double_t F(Double_t          guess,
	     Double_t          chi2) const
  {
    Double_t s = -chi2;

    TIter next(&fData);
    Observation* r = 0;
    while ((r = static_cast<Observation*>(next())))
      s += ChiTerm(guess, *r);
    return s;
  }
  /** 
   * Try to find best error 
   * 
   * @param nIter Number of iterations 
   * @param sign  Direction (-1 is low, +1 is high)
   * @param best  Current best @f$ x@f$ value 
   * @param chi2  @f$ \chi^2@f$ of current best @f$ x@f$ value 
   * @param s     Summed weights in the direction 
   * 
   * @return The error in the chosen direction
   */
  Double_t E(UShort_t        nIter,
	     Int_t           sign,
	     Double_t        best,
	     Double_t        chi2,
	     Double_t        s)
  {
    // Step size 
    Double_t delta = 0.1 * sign * s;

    // Iterations 
    for (UShort_t i = 0; i < nIter; i++) {
      // Calculate chi^2 with current guess 
      Double_t got = F(best + sign * s, chi2);

      if (TMath::Abs(got-1) < 1e-7)
	// We're close to 1 so get out
	break;

      // The next guess' chi^2 value e
      Double_t guess = F(best + sign * s + delta, chi2);

      // Where to search next 
      if ((got - 1) * (guess - 1) > 0) {
	if ((got - 1) / (guess - 1) < 1)
	  delta = -delta;
	else
	  s += sign * delta;
	continue;
      }

      // Update error value and decrease step size 
      s     += sign * delta * (1 - got) / (guess - got);
      delta /= 2;
    }
    return s;
  }
  /** 
   * Find best estimate of @f$ x@f$ 
   * 
   * @param nIter   Number of iterations 
   * @param lowest  Lower bound 
   * @param highest Upper bound 
   * 
   * @return  @f$ x@f$ 
   */
  Double_t X(UShort_t      nIter,
	     Double_t      lowest,
	     Double_t      highest)
  {
    // Starting values 
    Double_t x    = (highest+lowest)/2;
    Double_t oldX = -1e33;

    // Do the iterations 
    for (UShort_t i = 0; i < nIter; i++) {
      Double_t sum    = 0;
      Double_t sumw   = 0;
      Double_t offset = 0;

      // Loop over observations
      TIter next(&fData);
      Observation* r = 0;
      while ((r = static_cast<Observation*>(next()))) {
	Double_t w =  StepW(x, *r);
	offset   += StepOffset(x,  *r);

	sum  += r->fX * w;
	sumw += w;
      }
      x = (sum - offset) / sumw;

      if (TMath::Abs(x - oldX) < (highest-lowest) * 1e-6) break;
      oldX = x;
    }
    return x;
  }
  /** 
   * Do the calculation 
   * 
   * @param nIter How many iterations to do. 
   * 
   * @return The best estimate of @f$ x@f$ and associated errors 
   */
  Result* Calculate(UShort_t nIter=50)
  {
    Double_t lowest  = +1e33;
    Double_t highest = -1e33;
    Double_t sumLow  = 0;
    Double_t sumHigh = 0;

    // Find boundaries and sum weights
    TIter next(&fData);
    Observation* r = 0;
    while ((r = static_cast<Observation*>(next()))) {
      lowest  = TMath::Min(r->Low(),  lowest);
      highest = TMath::Max(r->High(), highest);
      sumLow  = 1./TMath::Power(r->fEl, 2);
      sumHigh = 1./TMath::Power(r->fEh, 2);
    }
    // Summed weights 
    Double_t sLow  = 1. / TMath::Sqrt(sumLow);
    Double_t sHigh = 1. / TMath::Sqrt(sumHigh);
    
    // Now do the calculations
    Double_t bestX    = X(nIter, lowest, highest);
    Double_t bestChi2 = F(bestX, 0);
    Double_t bestLow  = E(nIter,-1,bestX,bestChi2,sLow);
    Double_t bestHigh = E(nIter,+1,bestX,bestChi2,sHigh);

    fResult = new Result(bestX, bestLow, bestHigh, bestChi2, lowest, highest);
    return fResult;
  }
  /** 
   * Return function pointer to wrapper
   * 
   * @return Function pointer
   */
  virtual Wrapper_t Wrapper() const = 0;

  /** 
   * Make a function that represents to Log-likehood for a given
   * observation.
   * 
   * @param r Observation 
   * @param j Serial number 
   * 
   * @return Pointer to newly allocated function object
   */
  TF1* MakeF(const Observation& r, Int_t j) const
  {
    TF1* f = new TF1(Form("f%02d", j), Wrapper(), r.Low(), r.High(), 3);
    f->SetParNames("x", "#sigma^{-}", "#sigma^{+}");
    f->SetParameters(r.fX, r.fEl, r.fEh);
    f->SetLineStyle((j%3)+2);
    f->SetLineColor(kBlack);
    f->SetLineWidth(2);
    return f;
  }
  /** 
   * Make a line that represents the best found errors
   * 
   * @param f Log-likelyhood function to make it from 
   * 
   * @return 
   */
  TLine* MakeL(TF1* f) const
  {
    Double_t m = f->GetParameter(0);
    TLine* l = new TLine(m-f->GetParameter(1), 1,
			 m+f->GetParameter(2), 1);
    l->SetLineColor(f->GetLineColor());
    l->SetLineStyle(f->GetLineStyle());
    l->SetLineWidth(f->GetLineWidth());
    return l;
  }
  void Draw(Option_t* option="")
  {
    if (!fResult) return;
    
    TList fs; fs.SetOwner(false);
    Int_t j = 0;
    TIter next(&fData);
    Observation* r = 0;
    while ((r = static_cast<Observation*>(next()))) {
      TF1* f = MakeF(*r, j);
      f->SetRange(fResult->Low(), fResult->High());
      fs.Add(f, j == 0 ? "" : "same");
      fs.Add(MakeL(f));
      j++;
    }
    TF1* fr = MakeF(*fResult, j);
    fr->SetLineColor(kRed+2);
    fr->SetLineStyle(1);
    fs.Add(fr);
    fs.Add(MakeL(fr));
    TIter nextD(&fs);
    TObject* o = 0;
    j = 0;
    while((o = nextD())) { o->Draw(j == 0 ? "" : "same"); j++; }
    // fs.Draw();
    static_cast<TF1*>(fs.First())->GetHistogram()
      ->GetYaxis()->SetRangeUser(-.1, 5.1);
  }
  ClassDef(Combiner,1); // Combine systematics 
};


/**
 * A combiner that uses a linear @f$\sigma@f$ approximation 
 */
struct LinearSigmaCombiner : public Combiner
{
  /** 
   * Calculate the weight 
   * 
   * @f[ 
   *   w = 1/2 (s + x s')^3 / s
   * @f]
   *
   * @param r Observation
   * 
   * @return @f$ W@f$ 
   */
  Double_t W(const Observation& r) const
  {
    Double_t s = r.S();
    return .5 * TMath::Power(s + r.fX * r.Sprime(), 3) / s;
  }
  /** 
   * Calculate the weight based on a guess of best @f$ x'@f$ 
   * 
   * @f[ 
   *   w(x') = s / [s + s' (x' - x)]^3
   * @f]
   *
   * @param guess Current guess @f$ x'@f$ 
   * @param r	  Observation
   * 
   * @return @f$ W(x')@f$ 
   */
  Double_t StepW(Double_t guess, const Observation& r) const
  {
    Double_t s = r.S();
    return s / TMath::Power(s+r.Sprime()*(guess - r.fX),3);
  }
  /** 
   * Calculate the bias. 
   * 
   * @return 0
   */
  Double_t StepOffset(Double_t, const Observation&) const
  {
    return 0;
  }
  /** 
   * Calculate the contribution variance to the @f$\chi^2@f$ with
   * the guess @f$x'@f$. 
   *
   * @f[
   *   v(x') = [s + s' (x' - x)]^2
   * @f]
   * 
   * @param guess Current guess @f$ x'@f$ 
   * @param r	  Observation
   * 
   * @return @f$ v(x')@f$ 
   */
  Double_t VarTerm(Double_t guess, const Observation& r) const
  {
    return TMath::Power(r.S() + r.Sprime() * (guess - r.fX),2);
  }
  /** 
   * Return the likely-hood function value at @f$ x'@f$:
   *
   * @f[
   *   L(x') = \left[(x'-x) / (s + s'(x'-x))\right]^2
   * @f] 
   * 
   * where 
   * @f[
   *   s = 2\sigma^+\sigma^-/(\sigma^++\sigma^-)
   * @f]
   * @f[
   *   s' = (\sigma^+-\sigma^-)/(\sigma^++\sigma^-)
   * @f]
   * 
   * @param guess @f$ x'@f$ 
   * @param x     @f$ x@f$  
   * @param el    @f$ \sigma^-@f$  
   * @param eh    @f$ \sigma^+@f$  
   * 
   * @return 
   */
  static Double_t L(Double_t guess, Double_t x, Double_t el, Double_t eh)
  {
    Double_t d  = (guess-x);
    Double_t s  = 2 * el * eh / (el + eh);
    Double_t sp = (eh - el) / (eh + eh);
    return TMath::Power(d / (s+sp*d), 2);
  }
  /** 
   * Wrap likely-hood function for ROOT 
   * 
   * @param xp Pointer to independent variables 
   * @param pp Pointer to parameters 
   * 
   * @return Likely-hood function evaluate at @a xp
   */
  static Double_t WrapL(Double_t* xp, Double_t* pp)
  {
    return L(xp[0], pp[0], pp[1], pp[2]);
  }
  /** 
   * Return function pointer to wrapper
   * 
   * @return Function pointer
   */
  Wrapper_t Wrapper() const { return WrapL; }
  ClassDef(LinearSigmaCombiner,1); // Sigma combiner 
};

/**
 * A combiner that uses a linear variance approximation 
 */
struct LinearVarianceCombiner : public Combiner
{
  /** 
   * Calculate the weight 
   * 
   * @f[
   *   w = (V + x V')^2 / (2 V + x V')
   * @f] 
   *
   * @param r Observation
   * 
   * @return @f$ W@f$ 
   */
  Double_t W(const Observation& r) const
  {
    Double_t v  = r.V();
    Double_t vp = r.Vprime();
    return TMath::Power(v + r.fX * vp, 2) / (2 * v + r.fX * vp);
  }
  /** 
   * Calculate the weight based on a guess of best @f$ x'@f$ 
   * 
   * @f[
   *   W(x') = v / [V + V' (x' - x)]^2
   * @f] 
   *
   * @param guess Current guess @f$ x'@f$ 
   * @param r  	  Observation
   * 
   * @return @f$ W(x')@f$ 
   */
  Double_t StepW(Double_t guess, const Observation& r) const
  {
    Double_t v = r.V();
    return v / TMath::Power(v+r.Vprime()*(guess - r.fX), 2);
  }
  /** 
   * Calculate the bias. 
   * 
   * @f[
   *   \delta(x') = 1/2 V' [(x'-x) / (V + V'(x' - x))]^2
   * @f] 
   * 
   * @param guess Current guess @f$ x'@f$ 
   * @param r	  Observation
   * 
   * @return @f$\delta(x')@f$ 
   */
  Double_t StepOffset(Double_t guess, const Observation& r) const
  {
    Double_t vp = r.Vprime();
    return 0.5 * vp * TMath::Power((guess-r.fX)/(r.V()+vp*(guess-r.fX)),2);
  }
  /** 
   * Calculate the contribution variance to the @f$\chi^2@f$ with
   * the guess @f$x'@f$. 
   *
   * @f[ 
   *   V(x') = V + V' (x' - x)
   * @f] 
   * 
   * @param guess Current guess @f$ x'@f$ 
   * @param r	  Observation
   * 
   * @return @f$ v(x')@f$ 
   */
  Double_t VarTerm(Double_t guess, const Observation& r) const
  {
    return r.V() + r.Vprime() * (guess - r.fX);
  }
  /** 
   * Return the likely-hood function value at @f$ x'@f$:
   *
   * @f[
   *   L(x') = (x'-x)^2 / (V + V'(x'-x))
   * @f] 
   * 
   * where 
   * @f[
   *   v = \sigma^\sigma^-\quad v' = \sigma^+-\sigma^-
   * @f]
   * 
   * @param guess @f$ x'@f$ 
   * @param x     @f$ x@f$  
   * @param el    @f$ \sigma^-@f$  
   * @param eh    @f$ \sigma^+@f$  
   * 
   * @return 
   */
  static Double_t L(Double_t guess, Double_t x, Double_t el, Double_t eh)
  {
    Double_t d  = (guess-x);
    Double_t v  = eh * el;
    Double_t vp = eh - el;
    return TMath::Power(d,2) / (v+vp*d);
  }
  /** 
   * Wrap likely-hood function for ROOT 
   * 
   * @param xp Pointer to independent variables 
   * @param pp Pointer to parameters 
   * 
   * @return Likely-hood function evaluate at @a xp
   */
  static Double_t WrapL(Double_t* xp, Double_t* pp)
  {
    return L(xp[0], pp[0], pp[1], pp[2]);
  }
  /** 
   * Return function pointer to wrapper
   * 
   * @return Function pointer
   */
  Wrapper_t Wrapper() const { return WrapL;  }
  ClassDef(LinearVarianceCombiner,1); // Variance combiner 
};

void PrintTest(const char* type, 
	       Combiner::Observation& r,
	       Combiner::Observation& e,
	       Combiner::Observation& d)
{
  Printf("%-15s:  %7s  %8s %8s  %5s", type, "x", "-sigma", "+sigma", "chi2");
  printf("  %14s ", "Result:");     r.Print();
  printf("  %14s ", "Expected:");   e.Print();
  printf("  %14s ", "Difference:"); d.Print();
}
  
TCanvas* RunTest(Combiner::Observation&   o1,
		 Combiner::Observation&   o2,
		 Combiner::Result         s,
		 Combiner::Result         v)
{
  TCanvas* c = new TCanvas("c","c",800,1000);
  c->SetTopMargin(0.01);
  c->SetRightMargin(0.01);
  c->Divide(1,2,0,0);
  
  LinearSigmaCombiner sc;
  sc.Add(o1);
  sc.Add(o2);
  Combiner::Result* sf = sc.Calculate();
  Combiner::Diff    sd(*sf, s);
  sc.Print();
  PrintTest("Linear sigma", *sf, s, sd);
  c->cd(1); sc.Draw();
    
  LinearVarianceCombiner sv;
  sv.Add(o1);
  sv.Add(o2);
  Combiner::Result* vf = sv.Calculate();
  Combiner::Diff    vd(*vf, v);
  sv.Print();
  PrintTest("Linear variance", *vf, v, vd);
  c->cd(2); sv.Draw();

  return c;
}

	     
void Test1()
{
  Combiner::Observation o1(4,       1.682,   2.346);
  Combiner::Observation o2(5,       1.912,   2.581);
  Combiner::Result      s (4.49901, 1.33301, 1.66701, 0.115, 0, 11);
  Combiner::Result      v (4.50001, 1.33701, 1.66901, 0.113, 0, 11);

  TCanvas* c = RunTest(o1, o2, s, v);
  c->SetName("Test1");
  c->SetTitle("Test1");
}

void Test2()
{
  Combiner::Observation o1(6.32064, 0.567382, 0.379042);
  Combiner::Observation o2(6.15549, 0.159504, 0.170811);
  Combiner::Result      s (6.2,     0.2,      0.2,    1, 0, 11);

  TCanvas* c = RunTest(o1, o2, s, s);
  c->SetName("Test2");
  c->SetTitle("Test2");
}
void Test3()
{
  Combiner::Observation o1(6.20449, 0.451232,	0.495192);
  Combiner::Observation o2(6.16188, 0.165785,	0.176712);
  Combiner::Result      s (6.18,    0.3,        0.3 ,   1, 0, 11);

  TCanvas* c = RunTest(o1, o2, s, s);
  c->SetName("Test3");
  c->SetTitle("Test3");  
}
void TestAll()
{
  Test1();
  Test2();
  Test3();
}
#if 0
int
main()
{
  Test1();

  return 0;
}

#endif
