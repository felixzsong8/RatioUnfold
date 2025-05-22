# PYTHIA configuration file.
--prefix=/cluster/tufts/beaucheminlab/cpazos01/generator/pythia8307
--with-fastjet3=/cluster/tufts/beaucheminlab/cpazos01/generator/fastjet-install
--with-hepmc2=/cluster/tufts/beaucheminlab/cpazos01/generator/HepMC-2.06.09
--with-lhapdf6=/cluster/tufts/beaucheminlab/cpazos01/generator/LHAPDF-6.2.3-install
--with-root=/cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt

# Install directory prefixes.
PREFIX_BIN=/cluster/tufts/beaucheminlab/cpazos01/generator/pythia8307/bin
PREFIX_INCLUDE=/cluster/tufts/beaucheminlab/cpazos01/generator/pythia8307/include
PREFIX_LIB=/cluster/tufts/beaucheminlab/cpazos01/generator/pythia8307/lib
PREFIX_SHARE=/cluster/tufts/beaucheminlab/cpazos01/generator/pythia8307/share/Pythia8

# Compilation flags (see ./configure --help for further documentation).
CXX=g++
CXX_COMMON=-O2 -std=c++11 -pedantic -W -Wall -Wshadow -fPIC
CXX_SHARED=-shared
CXX_SONAME=-Wl,-soname,
LIB_SUFFIX=.so

EVTGEN_USE=false
EVTGEN_CONFIG=
EVTGEN_BIN=
EVTGEN_INCLUDE=
EVTGEN_LIB=

FASTJET3_USE=true
FASTJET3_CONFIG=fastjet-config
FASTJET3_BIN=/cluster/tufts/beaucheminlab/cpazos01/generator/fastjet-install/bin/
FASTJET3_INCLUDE=-I/cluster/tufts/beaucheminlab/cpazos01/generator/fastjet-install/include
FASTJET3_LIB=-L/cluster/tufts/beaucheminlab/cpazos01/generator/fastjet-install/lib -Wl,-rpath,/cluster/tufts/beaucheminlab/cpazos01/generator/fastjet-install/lib -lfastjet

HEPMC2_USE=true
HEPMC2_CONFIG=
HEPMC2_BIN=/cluster/tufts/beaucheminlab/cpazos01/generator/HepMC-2.06.09/
HEPMC2_INCLUDE=-I/cluster/tufts/beaucheminlab/cpazos01/generator/HepMC-2.06.09/include
HEPMC2_LIB=-L/cluster/tufts/beaucheminlab/cpazos01/generator/HepMC-2.06.09/lib -Wl,-rpath,/cluster/tufts/beaucheminlab/cpazos01/generator/HepMC-2.06.09/lib -lHepMC

HEPMC3_USE=false
HEPMC3_CONFIG=
HEPMC3_BIN=
HEPMC3_INCLUDE=
HEPMC3_LIB=

LHAPDF5_USE=false
LHAPDF5_CONFIG=
LHAPDF5_BIN=
LHAPDF5_INCLUDE=
LHAPDF5_LIB=

LHAPDF6_USE=true
LHAPDF6_CONFIG=lhapdf-config
LHAPDF6_BIN=/cluster/tufts/beaucheminlab/cpazos01/generator/LHAPDF-6.2.3-install/bin/
LHAPDF6_INCLUDE=-I/cluster/tufts/beaucheminlab/cpazos01/generator/LHAPDF-6.2.3-install/include
LHAPDF6_LIB=-L/cluster/tufts/beaucheminlab/cpazos01/generator/LHAPDF-6.2.3-install/lib -Wl,-rpath,/cluster/tufts/beaucheminlab/cpazos01/generator/LHAPDF-6.2.3-install/lib -lLHAPDF


POWHEG_USE=false
POWHEG_CONFIG=
POWHEG_BIN=
POWHEG_INCLUDE=
POWHEG_LIB=

RIVET_USE=false
RIVET_CONFIG=
RIVET_BIN=
RIVET_INCLUDE=
RIVET_LIB=

ROOT_USE=true
ROOT_CONFIG=root-config
ROOT_BIN=/cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/bin/
ROOT_INCLUDE=-I/cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/include:/cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/include/ROOT
ROOT_LIB=-L/cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/lib -Wl,-rpath,/cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/lib -lCore

YODA_USE=false
YODA_CONFIG=
YODA_BIN=
YODA_INCLUDE=
YODA_LIB=

GZIP_USE=false
GZIP_CONFIG=
GZIP_BIN=
GZIP_INCLUDE=
GZIP_LIB=

PYTHON_USE=false
PYTHON_CONFIG=
PYTHON_BIN=
PYTHON_INCLUDE=
PYTHON_LIB=

MG5MES_USE=false
MG5MES_CONFIG=
MG5MES_BIN=
MG5MES_INCLUDE=
MG5MES_LIB=

OPENMP_USE=false
OPENMP_CONFIG=
OPENMP_BIN=
OPENMP_INCLUDE=
OPENMP_LIB=
