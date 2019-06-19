#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTreeReader.h"
#include "DataModel/DataVector.h"
#include "Vertex_v1.h"
using namespace std;

vector<string> _ttbar_hlt_list = {
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000211.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000212.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000213.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000214.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000215.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000216.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000217.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000218.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000219.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000220.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000221.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000222.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000223.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000224.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000225.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000226.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000227.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000228.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000229.pool.root.1",
    "/scratch/users/flosterzo/datasets/mc16_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.AOD.e3698_s2997_r8903_r8906/AOD.10226638._000230.pool.root.1"
};


vector<string> _Zprime_hlt_list = {
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000121.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000122.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000123.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000124.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000125.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000126.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000127.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000128.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000129.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000130.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000131.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000132.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000133.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000134.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000135.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000136.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000137.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000138.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000139.pool.root.1",
    "/scratch/users/flosterzo/input_test/mc16_13TeV.427080.Pythia8EvtGen_A14NNPDF23LO_flatpT_Zprime.merge.AOD.e5362_s2997_r8903_r8906/AOD.10226627._000140.pool.root.1"
};


void fill_graph(const int& events_to_record, int& events_recorded, TFile& data_file, string vertex_name) {
    string tree_name = "CollectionTree";
    TTreeReader tree_reader(tree_name.c_str(), &data_file);
    //TTreeReaderValue< vector<int> > coneID_vector_reader(tree_reader, coneID_name.c_str());
    TTreeReaderValue<  DataVector<xAOD::Vertex_v1>  > vertex_vector_reader(tree_reader, vertex_name.c_str());

    while ( tree_reader.Next() ) {
        DataVector<xAOD::Vertex_v1> vertex_vector = *vertex_vector_reader;
        for (size_t vector_index = 0; vector_index < vertex_vector.size(); vector_index++) {
            //xAOD::Vertex_v1 vertex = vertex_vector[vector_index];
            const xAOD::Vertex_v1* vertex = vertex_vector.get(vector_index);
            //float x = vertex->x();
            //float y = vertex->y();
            //float z = vertex->z();
            //cout << x << " " << y << " " << z << endl;
            
            cout << vertex->index() << " ";
            SG::auxid_set_t vertex_ids = vertex->getAuxIDs();
            cout << vertex_ids.size() << endl;
            for (const size_t id : vertex_ids) {
                cout << "      " << id << endl;
            }
        }
        cout << "Completed Event " << events_recorded++ << endl;
        if (events_recorded >= events_to_record) break;
    }
}


void make_graph( vector<string>& aod_list, string vertex_name ) {
    const int events_to_record = 1;
    int events_recorded = 0;
    for ( string aod_name : aod_list ) {
        cout << "Reading " << aod_name << endl << endl;
        TFile aod_file( aod_name.c_str(), "read" );
        fill_graph(events_to_record, events_recorded, aod_file, vertex_name);
        if (events_recorded >= events_to_record) break;
    }
}


int main() {
    make_graph(_ttbar_hlt_list, "HLT_xAOD__VertexContainer_xPrimVx");
}
