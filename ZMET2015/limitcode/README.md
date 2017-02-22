# Running and Drawing Limits for ZMET analysis

## Check out and compile Higgs Combine Tool (must be done once)

Make sure to do this from a clean environment, i.e. don't source any other setup scripts first.

``` bash
source setupLimits.sh
```

## Run the limits

Edit the file `doLimits.sh` to specify the scan you're running and the datacard location.
The limits are relatively fast to run (30-60 minutes for the longer scans) but best to run in a screen session.

From this directory, with a clean environment:
``` bash
screen
source /code/osgcode/cmssoft/cmsset_default.sh
cd CMSSW_7_4_7/src
cmsenv
cd ../..
source doLimits.sh
```

## Plot the results

The output of the command above will be a file with the limits stored as r-values, like `r-values_T5ZZ.root`.
To plot them in the standard CMS style, use the relevant script from this directory, i.e.
``` bash
root -b -q makeLimitHist_T5ZZ.C
```

## Making covariance matrix

Follow the descriptions on this twiki, in particular for "Control regions NOT included in datacard":

https://twiki.cern.ch/twiki/bin/view/CMS/SimplifiedLikelihood#Producing_covariance_for_recasti

Make sure you have an up-to-date version of the combine tool, as stated there.  We make one covariance matrix for all the strong regions, and one covariance matrix for all of the electroweak regions.
