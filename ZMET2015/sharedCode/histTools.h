#include "TH1.h"
#include "TCanvas.h"
#include <map>

#ifndef HISTTOOLS_H
#define HISTTOOLS_H

void fillUnderOverFlow(TH1F * &h1, float value, float weight);
void fillUnderOverFlow(TH1D * &h1, double value, float weight);
void saveHist(const std::string filename, const std::string pat="*");
void drawCMSLatex( TCanvas * &canvas, float luminosity );
void drawCMSLatex( TCanvas * &canvas, float luminosity, float cmsleftmargin, float lumileftmargin );
void drawSRLatex( TCanvas * &canvas, std::string signalregion, float cmsleftmargin, float lumileftmargin );
void updateoverflow( TH1F * &hist, float xmax );
void getBackground( TH1F* &backgroundhist, std::string iter, std::string bgfileprefix, std::string variable, std::string leptype, std::string selection );
void renormalizebins( TH1F * &hist );
float err_binomial(float A, float B, float errA, float errB);


class histmap
{
public:

  histmap();
  ~histmap();
  TH1F * & gethist( std::string name );
  void addhisttolist( std::string name, TH1F * hist );
  void normalizebins();
  void updateoverflowbins( float xmax );
  void scaleall( float scale );
  void rebinall( int rebin );
  void scalealltounity();
  void setlinewidthall( float linewidth );
  void setfillstyleforstack();
  void setfillcolors();
  void setlinecolors();
  
private:

  std::map<std::string, TH1F*> hist_list;

};

#endif
