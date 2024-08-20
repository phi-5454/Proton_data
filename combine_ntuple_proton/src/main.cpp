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
#include <cstddef>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

  // ROOT::EnableImplicitMT();
  ROOT::EnableThreadSafety();
  // TApplication app("app", nullptr, nullptr);
  if (argc != 4) {
    std::cerr << "Mismatch in argument count" << std::endl;
    std::cerr << argc << ", should be 3." << std::endl;
    return -1;
  }
  for (int i = 0; i < argc; ++i) {
    std::cout << "Argument " << i << ": \"" << argv[i] << "\"" << std::endl;
  }
  auto ntuple_src = argv[1];
  auto proton_src = argv[2];
  // Where to write pruned files
  auto tgt = argv[3];

  std::cerr << "," << proton_src << ", " << ntuple_src << ", " << tgt << "\n";

  TFile *ntf = new TFile(ntuple_src);
  TFile *pf = new TFile(proton_src);

  // TTree *ntuples = (TTree *)ntf->Get("analysis/tree");
  TTree *ntuples = (TTree *)ntf->Get("tree");
  TTree *protons = (TTree *)pf->Get("tree");

  // ind.
  auto prot_ind = protons->BuildIndex("Run", "EventNum");
  auto ntuple_ind = ntuples->BuildIndex("Run", "EventNum");
  // auto evt_ind = ntuples->BuildIndex("event");

  ntuples->GetIndex();

  ROOT::RDataFrame prot_df(*protons);
  ROOT::RDataFrame ntuple_df(*ntuples);
  // df.Histo1D("pr_px_a");

  auto prot_filter = [&ntuples](unsigned int run, unsigned long long event) {
    // std::cerr << "a";
    if (ntuples->GetEntryWithIndex(run, event) <= 0) {
      return false;
    }
    return true;
  };

  auto ntuple_filter = [&protons](unsigned int run, unsigned long long event) {
    // std::cerr << "b";
    if (protons->GetEntryWithIndex(run, event) <= 0) {
      return false;
    }
    return true;
  };

  auto prot_ff = prot_df.Filter(prot_filter, {"Run", "EventNum"});
  auto ntuple_ff = ntuple_df.Filter(ntuple_filter, {"Run", "EventNum"});

  // Join the two!

  // Extract the TTrees from the RDataFrame
  prot_ff.Snapshot("tree_prot", "memfile.root");
  TFile memFile("memfile.root");
  TTree *protons_filtered = (TTree *)memFile.Get("tree_prot");

  ntuple_ff.Snapshot("tree", "memfile2.root");
  TFile memFile_n("memfile2.root");
  TTree *ntuples_filtered = (TTree *)memFile_n.Get("tree");

  // Rebuild indices? Maybe help them sync?
  auto prot_ind_1 = protons_filtered->BuildIndex("Run", "EventNum");
  auto ntuple_ind_1 = ntuples_filtered->BuildIndex("Run", "EventNum");

  std::cout << (size_t)protons_filtered << "\n";
  std::cout << (size_t)ntuples_filtered << "\n";

  ntuples_filtered->AddFriend(protons_filtered);
  ntuples_filtered->ls();

  ROOT::RDataFrame joint_df(*ntuples_filtered);
  joint_df.Snapshot("tree", tgt);

  // prot_ff.Snapshot("tree", "../testout.root");

  std::cout << prot_ff.GetNRuns();

  // ntuples->AddFriend(protons, "imporved_protons");
  // auto out = ROOT::RDataFrame(*ntuples);

  memFile_n.Close();
  memFile.Close();

  ntf->Close();
  pf->Close();
  // app.Run();
  return 0;
}
