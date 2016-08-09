
HH Ana
==============
It includes dataMC, systematic uncertain, and some SF checking.
--------------------
**step1**<br>
using makeAna.sh to make btagging efficiency<br>
**step2**<br>
using makeAna2.sh to fill histogram and dataMCplots.C to draw them<br>

**warning**<br>
Don't use cmsenv because bagCailbrtion is deprecated<br>
cp 700_1.root data.root: This step below is used to give a input as MC to let data run while it won't effect any result of data.
```
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/makeAna.sh
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/makeAna.csh
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/makeAna2.sh
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/makeAna2.csh
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/dataMCplots.C
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/HH4bBtagEffBase_80.C
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/HH4bBtagMakeEffBase_80.C
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/HH4bBtagMakeEff_80.C
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/HHbbbbBtagEff.C
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/standalone_LumiReWeighting.cc
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/standalone_LumiReWeighting.h
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/untuplizer.h
wget https://raw.githubusercontent.com/chingweich/HHbbbbAnalyzer/master/80x_v3/setNCUStyle.C

wget https://twiki.cern.ch/twiki/pub/CMS/BtagRecommendation80X/subjet_CSVv2_ichep.csv
wget https://raw.githubusercontent.com/cms-sw/cmssw/CMSSW_8_0_X/CondTools/BTau/test/BTagCalibrationStandalone.cpp
wget https://raw.githubusercontent.com/cms-sw/cmssw/CMSSW_8_0_X/CondTools/BTau/test/BTagCalibrationStandalone.h

mkdir btagEffSource
mkdir sf
bash
source /afs/cern.ch/sw/lcg/external/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh
source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.06.06/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh

chmod u+x *sh

./makeAna.sh
cd btagEffSource
cp 700_1.root data.root
cd ..
./makeAna2.sh

mkdir dataMC
cd dataMC
mkdir 0b
mkdir 1b
mkdir 2b
mkdir all

cd ..
root -l dataMCplots.C++
```