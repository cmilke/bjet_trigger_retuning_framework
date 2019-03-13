#include <iostream>
#include "TFile.h"
#include "TDirectory.h"
#include "TDirectoryFile.h"
using std::cout;
using std::endl;
using std::cerr;

void calibMod() {
  cout<<"Usage: "<<endl;
  cout<<"\t"<<"removeGUID(filename)"<<endl;
  cout<<"\t"<<"removeTagger(filename,tagger)"<<endl;
  cout<<"\t"<<"removeJetColl(filename,tagger,jetcollection)"<<endl;
  cout<<"\t"<<"copyJetColl(filename,tagger,sourcecollection,targetcollection)"<<endl;
  return;
}

void removeGUID(TString filename) {

  TFile *file = TFile::Open(filename,"update");
  if (!file) {
    cerr<<"The file given doesn't exist, filename= "<<filename<<endl;
    exit(1);
  }
  cout<<"Removing fileGUID."<<endl;

  file->Delete("fileGUID;1");
  file->Write();

  cout<<"Done."<<endl;
  return;
}

void removeTagger(TString filename, TString taggername) {

  TFile *file = TFile::Open(filename,"update");
  if (!file) {
    cerr<<"The file given doesn't exist, filename= "<<filename<<endl;
    exit(1);
  }

  cout<<"Removing tagger: "<<taggername<<endl;

  file->rmdir(taggername);
  file->Write();

  cout<<"Done."<<endl;  
  return;
}

void removeJetColl(TString filename, TString taggername, TString jetcollname) {

  TFile *file = TFile::Open(filename,"update");
  if (!file) {
    cerr<<"The file given doesn't exist, filename= "<<filename<<endl;
    exit(1);
  }

  TDirectoryFile * tagger = (TDirectoryFile*)file->Get(taggername);
  if (!tagger) {
    cerr<<"The tagger given doesn't exist in the file, taggername= "<<taggername<<endl;
    exit(1);
  }

  cout<<"Removing jet collection: "<<taggername<<"/"<<jetcollname<<endl;

  tagger->rmdir(jetcollname);
  tagger->Write();
  file->Write();

  cout<<"Done."<<endl;
  return;
}

void copyJetColl(TString filename, TString taggername, TString jetcollname, TString targetjetcoll) {

  TFile *file = TFile::Open(filename,"update");
  if (!file) {
    cerr<<"The file given doesn't exist, filename= "<<filename<<endl;
    exit(1);
  }
  
  TDirectoryFile * tagger = (TDirectoryFile*)file->Get(taggername);
  if (!tagger) {
    cerr<<"The tagger given doesn't exist in the file, taggername= "<<taggername<<endl;
    exit(1);
  }

  TDirectoryFile* jetcoll = (TDirectoryFile*) tagger->Get(jetcollname);
  if (!jetcoll) {
    cerr<<"The jet collection given doesn't exist in the file, jetcollname= "<<jetcollname<<endl;
    exit(1);
  }

  TDirectoryFile* targetcoll = (TDirectoryFile*)jetcoll->Clone(targetjetcoll);

  cout<<"Copying jet collection: "<<taggername<<"/"<<jetcollname<<" to "<<taggername<<"/"<<targetjetcoll<<endl;

  tagger->WriteTObject(targetcoll,targetjetcoll);
  tagger->Write();
  file->Write();

  cout<<"Done."<<endl;
  return;
}

