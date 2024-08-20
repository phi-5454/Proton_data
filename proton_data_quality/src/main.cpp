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
#include <TTree.h>
#include <iostream>
#include <string>

void run_analysis(std::vector<const char *> files) {
  ROOT::EnableImplicitMT(); // Tell ROOT you want to go parallel
  TApplication app("app", nullptr, nullptr);

  TChain nf("tree");

  for (auto &s : files) {
    nf.Add(TString(s));
  }
  // nf.Add("/home/younes/totemdata/combined/TOTEM20.root");
  //  nf.Add("/home/younes/totemdata/combined/TOTEM21.root");
  // nf.Add("/home/younes/totemdata/combined/TOTEM22.root");
  // nf.Add("/home/younes/totemdata/combined/TOTEM23.root");

  // nf.Add("/home/younes/totemdata/combined/TOTEM40.root");
  // nf.Add("/home/younes/totemdata/combined/TOTEM41.root");
  // nf.Add("/home/younes/totemdata/combined/TOTEM42.root");
  // nf.Add("/home/younes/totemdata/combined/TOTEM43.root");

  //  TFile pf("../TOTEM20p.root");

  // auto ntuples = nf.Get<TTree>("tree");
  //  ntuples->BuildIndex("Run", "EventNum");

  // auto protons = pf.Get<TTree>("tree");

  // ntuples->AddFriend(protons, "proton_tree");
  // ntuples->Print("all");

  // ntuples->Draw("EventNum:tree_prot_EventNum");
  // ntuples->Draw("Run:tree_prot_Run");
  // ntuples->Draw("ThxR:pr_px_b");
  // ntuples->Draw("ThyR:pr_py_b");

  // ntuples->ls();

  // TTree ntuples("TOTEM20.root");

  ROOT::RDataFrame d(nf); // Interface to TTree and
                          // TChain

  auto filt_px = d.Filter("pr_ptx_sigma_a < 0.0005 && pr_ptx_sigma_b < 0.0005");

  auto histo1 =
      d.Histo1D({"histName", "Proton a x momenta", 64u, -2., 2.}, "pr_px_a");
  auto histo2 = filt_px.Histo1D(
      {"histName", "Proton x momenta, filtered", 64u, -4., 4.}, "pr_px_a");
  auto histo3 = d.Histo1D("pr_ptx_sigma_a");
  auto d1 =
      d.Define("px_sum", "pr_ptx_a + pr_ptx_b")
          .Define("py_sum", "pr_pty_a + pr_pty_b")
          .Define("pt_a", "sqrt(pr_ptx_a * pr_ptx_a + pr_pty_a * pr_pty_a)")
          .Define("pt_b", "sqrt(pr_ptx_b * pr_ptx_b + pr_pty_b * pr_pty_b)");
  //.Define("pt_sum", "pt_a + pt_b");

  auto d3 = d1.Filter(
      " px_sum < 0.2 && px_sum > -0.2 && py_sum < 0.2 && py_sum > -0.2");

  auto histo4 = d3.Histo1D(
      {"histName", "Elastic proton x momentum", 64u, -2., 2.}, "pr_px_a");
  auto histo5 = d3.Histo1D("pr_py_a");
  auto histo6 = d.Histo1D({"histName", "xPV", 64u, -0., 0.2}, "xPV");
  auto histo7 = d.Histo2D({"histName", "dxy vs phi", 64u, -4, 4, 64u, -4, 4},
                          "trk_dxy", "trk_phi");

  auto ga = d.Graph("Run", "tree_prot_Run");
  auto gb = d.Graph("EventNum", "tree_prot_EventNum");

  auto cs = new TCanvas("cs", "cs");
  cs->Divide(4, 2);
  cs->cd(1);
  histo1->Draw(); // Event loop is run here, upon first access to a result
  cs->cd(2);
  histo6->Draw(); // Event loop is run here, upon first access to a result
  cs->cd(3);
  histo3->Draw(); // Event loop is run here, upon first access to a result
  cs->cd(4);
  histo4->Draw(); // Event loop is run here, upon first access to a result
  cs->cd(5);
  histo7->Draw(); // Event loop is run here, upon first access to a result
  cs->cd(7);
  ga->Draw(); // Event loop is run here, upon first access to a result
  cs->cd(8);
  gb->Draw(); // Event loop is run here, upon first access to a result
  cs->SaveAs("hist1.png");

  constexpr float PR_MASS = 0.938;

  auto g1 = d.Graph("ThxL", "pr_px_a");
  auto g2 = d.Graph("ThxR", "pr_px_b");
  auto g3 = d.Graph("ThyL", "pr_py_a");
  auto g4 = d.Graph("ThyR", "pr_py_b");

  auto histo8 =
      d.Histo2D({"histName", "posx_a vs posx_b", 64u, -8, 8, 64u, -8, 8},
                "pr_posx_a", "pr_posx_b");
  auto histo9 =
      d.Histo2D({"histName", "posy_a vs posy_b", 64u, -8, 8, 64u, -8, 8},
                "pr_posy_a", "pr_posy_b");

  auto cs2 = new TCanvas("cs2", "cs2");
  cs2->Divide(3, 2);
  cs2->cd(1);
  g1->Draw("AP");
  cs2->cd(2);
  g2->Draw("AP");
  cs2->cd(3);
  g3->Draw("AP");
  cs2->cd(4);
  g4->Draw("AP");
  cs2->cd(5);
  histo8->Draw();
  cs2->cd(6);
  histo9->Draw();

  cs2->SaveAs("hist2.png");

  auto histo10 =
      d1.Histo1D({"histName", "Proton x momentum sum", 64u, -2., 2.}, "px_sum");
  auto histo11 =
      d1.Histo1D({"histName", "Proton y momentum sum", 64u, -2., 2.}, "py_sum");

  auto histo12 = d3.Histo1D(
      {"histName", "Elastic proton x momentum sum", 64u, -2., 2.}, "px_sum");
  auto histo13 = d3.Histo1D(
      {"histName", "Elastic proton y momentum sum", 64u, -2., 2.}, "py_sum");
  auto histo14 = d1.Histo1D({"histName", "pt_a", 64u, 0., 2.}, "pt_a");
  auto histo15 = d1.Histo1D({"histName", "pt_b", 64u, 0., 2.}, "pt_b");
  auto histo16 = d1.Histo1D({"histName", "pt_sum", 64u, -2., 2.}, "pt_b");

  auto cs3 = new TCanvas("cs3", "cs3");
  cs3->Divide(3, 2);
  cs3->cd(1);
  histo10->Draw();
  cs3->cd(2);
  histo11->Draw();
  cs3->cd(3);
  histo12->Draw();
  cs3->cd(4);
  histo13->Draw();
  cs3->cd(5);
  histo14->Draw();
  cs3->cd(6);
  histo15->Draw();
  // cs3->cd(7);
  // histo16->Draw();
  cs3->SaveAs("hist3.png");

  app.Run();
}

int main() {

  // nf.Add("/home/younes/totemdata/combined/TOTEM20.root");
  //  nf.Add("/home/younes/totemdata/combined/TOTEM21.root");
  // nf.Add("/home/younes/totemdata/combined/TOTEM22.root");
  // nf.Add("/home/younes/totemdata/combined/TOTEM23.root");

  // nf.Add("/home/younes/totemdata/combined/TOTEM40.root");
  // nf.Add("/home/younes/totemdata/combined/TOTEM41.root");
  // nf.Add("/home/younes/totemdata/combined/TOTEM42.root");
  // nf.Add("/home/younes/totemdata/combined/TOTEM43.root");
  auto files = std::vector{
      //"/home/younes/totemdata/combined/TOTEM20.root",
      "/home/younes/totemdata/combined/TOTEM21.root",
      "/home/younes/totemdata/combined/TOTEM22.root",
      "/home/younes/totemdata/combined/TOTEM23.root"
      //"/home/younes/totemdata/combined/TOTEM40.root",
      //"/home/younes/totemdata/combined/TOTEM41.root",
      //"/home/younes/totemdata/combined/TOTEM42.root",
      //"/home/younes/totemdata/combined/TOTEM43.root"
  };
  run_analysis(files);
  return 0;
}
