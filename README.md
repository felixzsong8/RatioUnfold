# RatioUnfold

The purpose of this code is to:
- simulate proton-proton collisions and their outputs
- Take these datasets, process them, and read out their raw input
- Take two datasets, in our case either values from W+jets and Z+jets processes or two values from W+jets process, and take the double ratio as a correction factor
- Do a matrix and SVD unfolding
- Do cDDPM unfolding
- Plotting results
# Abstract

Unfolding is a critical computational technique in experimental physics, as it gives insight into the true characteristics of data that have been altered through measurement. In the context of high-energy particle collisions, fundamental particle phenomenology is modeled by probability density functions (pdf) for various underlying physical quantities such as the momentum and energy of final-state particles, which are testing aspects of the Standard Model of Particle physics, the theory that describes particles at the smallest distance ever probed by human means. In particular interest to the Large Hadron Collider (LHC), the premier high-energy physics facility in the world, is uncovering the theory of the strong interaction, which is responsible for the process of proton collision, several fundamental processes, and production of final-state particles. However, to observe probability functions predicted by QCD and measurable effects, it is necessary to use detectors that can distort these pdfs and quantities through subtle interactions. Unfolding techniques allow us to use models of these detector effects by simulating the complex instrumentation used for detection to ultimately make inference about underlying pdfs that could be compared to theoretical predictions. To construct unfolding methods of significant interest for testing the theory of QCD at hadron collider is the measurement of ratio observables as they’re significantly more precise than absolute measurements by exploiting positive correlations between systematic uncertainties to mitigate them. Subsequently, the ratios are sensitive to differences in any given QCD effects between processes because of the correlation between processes. They are therefore ideal for fine-tuning modeling issues that are difficult to study in an absolute cross-section measurement. The problem with ratio measurements is that we do not know how to unfold them because there is no event migration between bins of an observable ratio. Unfolding would then have to be done separately between the numerator and the denominator, which breaks some of the correlations that are exploited in ratio measurements. A bin-by-bin correction to a ratio would assume that there is no correlation between bins of an observable, which is not accurate. The Tufts ATLAS group has recently developed an object-based event-by-event unfolding algorithm using Conditional Denoising Diffusion Probabilistic Models (cDDPM)(Pazos et al.). The objective of this project is to use this algorithm to demonstrate that the ratio of observables can be unfolded, and by comparing standard methods with our diffusion model unfolding, we show the upsides of our method. 


# Code Instructions

First step is to login into Tufts Cluster server:
- You need to have the Tufts VPN, setup through any VPN app, I used Cisco Anyconnect
- Connect with vpn.tufts.edu/duo
- Login into the cluster through terminal with ssh [username]@login.cluster.tufts.edu (my username was fsong02). You will need access approval from Prof. Beauchemin
- Copy the AnalysisFramework folder in the lab dir and then go to your dir - something like this - cd /cluster/tufts/beaucheminlab/fsong02/AnalysisFramework

The next step is to begin generating data:
- Go into the run-pythia folder and then MyPythia8Simul.cmnd file
- This is where you set the parameters of your simulation data. Look at the comments from lines 77-94, 119-131, and 135-144 about what lines should be in and which should be commented out.
- Load the neccesary resources to run the simulations in the following two lines
- srun --pty -p largemem --time=0-12:00:00 bash
- source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh
- Note that these sometimes change, and if they don't work, either ask me or look online.
- Now create an SBatch file to run your simulations in parellel, so that you can split up large datasets into smaller ones. I did my best to comment, but again ask any questions if you have.
- Ensure the node you select is open by typing sinfo into the terminal. In my experience, mix works the best. 
- Type sbatch W1.sbatch or whatever the name of the sbatch file is to run it.
- You should then be able to see if it you write squeue -u [username]
- These files will then be saved as .root files to the pythia-outputs folder

Analysis of Datasets:
- To transform the data into more understandable quantities, cd into analyze-pythia folder and look at MyAnalysis.C
- I created a temp folder in the pythia-outputs folder because the analysis file reads through all root files in the pythia-output folder, so keep any data you've taken in the temp that you don't want read. If you read 10 W+jets files, then it will all compile into a single analysis file.
- Run root -x -l -q MyAnalysis.C to create the file
- Note, to get the secondary ratios, change lines 635-692 accordingly.

For method 1 (Bin-by-bin):
- Go into analyze-pythia folder
- Run "root -x -l -q PlotMacro.C" for the representaiton for one process
- Run "root -x -l -q MacroRatio.C" for the ratios of two different datasets

For method 2 (Matrix and SVD):
- Go into RooUnfold and Run root -x -l -q Unfold_matrix1.C
- Some of the names are awkward, so feel free to change them, but as of now: W and Z are for leadjetpt when n>0 and W1 is leadjetpt when n>1 and W2 is for scndjetpt when n>1

For method 3 (cDDPM):
- Before you actually unfold data, you need to first process the data into text files, which is completed in the match-and-clean folder
- run Root -x -l -q MatchAndClean.C, which takes all files in pythia-output and transforms into root files
- Then run python root-to-texts-[item].py depending on what you want to transform. This changes items in the root file to text
- Then run python data-normalize-[jets].py which scales all values from -1 to 1, which allow the DDPM to process them
- Now, go into the cddpm-unfolder-master and access GPU by running in terminal "srun --pty -p gpu --time=0-12:00:00 --gres=gpu:a100:1 bash" (This step may take time if they are already taken, best to do it when servers are less busy)
- Now go into a anaconda env with "module load anaconda" and "conda create -n "myenv"
- Now go into configs.py file and configure the title according to the data that you want to process and change unfold size to the number of jets. The range for normalization should be the same as you set in the data-normalize file
- then run "python train.py", "python unfold.py", and "python plot.py" for final resutls. These should take some time to run.
- Using plot_all.py takes the data that I manually moved from the other methods and compares to the cDDPM method.




















