#include "TApplication.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include <ROOT/RDataFrame.hxx>
#include <THStack.h>
#include <TROOT.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  // ROOT::EnableImplicitMT(); // Tell ROOT you want to go parallel

  // TApplication app("app", nullptr, nullptr);
  if (argc != 4) {
    std::cerr << "Mismatch in argument count" << std::endl;
    std::cerr << argc << ", should be 4." << std::endl;
    return -1;
  }

  auto ntuple_src = argv[1];
  auto proton_src = argv[2];
  // Where to write pruned files
  auto tgt = argv[3];

  std::cerr << "Protons: " <<  proton_src << ", ntuples: " << ntuple_src << ", target: " << tgt <<  "\n";

  TFile *ntf = new TFile(ntuple_src);
  TFile *pf = new TFile(proton_src);

  // TTree *ntuples = (TTree *)ntf->Get("analysis/tree");
  TTree *ntuples = (TTree *)ntf->Get("tree");
  TTree *protons = (TTree *)pf->Get("tree");

  // ind.
  auto run_ind = ntuples->BuildIndex("Run", "EventNum");
  // auto evt_ind = ntuples->BuildIndex("event");

  ntuples->GetIndex();

  ROOT::RDataFrame df(*protons);
  // df.Histo1D("pr_px_a");

  auto filter = [&ntuples](unsigned int run, unsigned long long event) {
    if (ntuples->GetEntryWithIndex(run, event) <= 0) {
      return false;
    }
    //std::cout << "Yes " << event << "\n";
    return true;
  };

  auto ff = df.Filter(filter, {"Run", "EventNum"});

  ff.Snapshot("tree", tgt);

  std::cout << ff.GetNRuns();

  // ntuples->AddFriend(protons, "imporved_protons");
  // auto out = ROOT::RDataFrame(*ntuples);


  ntf->Close();
  pf->Close();
  // app.Run();
  return 0;
}
