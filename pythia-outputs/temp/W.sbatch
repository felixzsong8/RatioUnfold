#!/bin/bash

#SBATCH --job-name=W-1     # job name, "OMP_run"
#SBATCH -t 3-0:00              # time limit: (D-HH:MM) 
#SBATCH --output=outfiles/W-1.out     # file to collect standard output
#SBATCH --error=outfiles/W-1.err      # file to collect standard errors
#SBATCH --nodelist=p1cmp045

source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh

./MyPythia8Simul MyPythia8Simul.cmnd -outroot dataW-1 > outW-1.txt


  for (int i = 0; i <= ScndError->GetNbinsX(); i++) {
    float n1 = ScndError->GetBinContent(i);
    //float n2 = LeadJetPtReco_LQ_raw->GetBinContent(i);

    float err1 = (n1 > 0) ? (1.0 / sqrt(n1)) : 0; 
    //float err2 = (n2 > 0) ? (1.0 / sqrt(n2)) : 0; 

    float combinedRelativeError = err1 * 100;  
    ScndError->SetBinContent(i, combinedRelativeError);
  }